/**********************************************************************************
//
//      roomleased.c
//      Created by mychat 31/04/2004
//      保留我的签名情况下 free of use.
//      当然更欢迎修改、优化等。
//
//      Email & MSN: codemake@163.com
//      文件位于/adm/deamons下
// 		处理出租房间的进程
//      change it to db by Ciwei@SJ
***********************************************************************************/

inherit F_SAVE;

#include <ansi.h>
//#include <roomlease.h>
#include <mudlib.h>

#define MSG_CMDS "/cmds/std/msg"
#define DB_NAME "lease"
//下一次投标开始的时间间隔
#define NEXT_BID		300
//刷新时间
#define MYLOG_TIME		60
/*因为当机而另外补偿玩家 嘿嘿 保留意见为100000 公测期为0 */
#define PAY_FOR_CRASH           100000

int strtoint(string arg);
int givemoney(string valuserid,int money,string valreason);
int sum_by_discount(int ival,int idiscount);
string get_myregions(string str);

string longtime(int t);
string shorttime(int t);
string Ctime(string ts);
string chinese_time(int total);
string money_str(int amount);

void init_statistic();
void do_statistic();
void check_lease();
void check_bid();
void write_log();
void change_dp(string valbidname);
void pay_for_crash();
void set_all_name(int type);

nosave int ilaststatistic;
int iifstop;
int livetime;
int iifpublicrepay=0;

string query(string arg)
{
	if (arg == "channel_id")
		return "韦氏商会";
}

int start_lease()
{
	if(!iifstop) return 0;
	livetime = time();
	//if(!dbquery("REPLACE mud_var SET name='leasetime',value='"+time()+"'")) return 0;
	call_out("do_statistic", 2);
	iifstop=0;
	set_all_name(iifstop);
	return 1;
}

void create()
{
	seteuid(getuid());

	iifstop=0;
	restore();
	iifpublicrepay=0;
	init_statistic();
	set_all_name(iifstop);
}

string query_save_file()
{
	return DATA_DIR+"lease";
}

void remove()
{
	save();
	set_all_name(1);
}

void pay_for_crash()
{
	int t;
	
	if(iifstop==1) return;
		
	t = time() - livetime;
	//系统有两分钟以上没响应
	if(t>MYLOG_TIME*2)
	{
		mixed ret;
		dbquery("update "+DB_NAME+" set endtime=endtime+'"+t+"',bidendtime=bidendtime+'"+t+"' where leaser!='*' AND U_Site='"+INTERMUD_MUD_NAME+"'");
		log_file("leaselog",sprintf("系统可能当过机，自动补偿每个在租商店有效期%d。",t));
		ret = dbquery("select leaser,originshortname,roomwhere,endtime from "+DB_NAME+" where leaser!='*' AND U_Site='"+INTERMUD_MUD_NAME+"'");
		if(!ret || sizeof(ret)<1) return;
		for(int i=0;i<sizeof(ret);i++)
			givemoney(ret[i][0],PAY_FOR_CRASH,HIY"对于您对【"+get_myregions(ret[i][2])+ret[i][1]+"】的租期有可能受到系统当机的影响，\n"
				+"有效期已经自动延长到"
				+longtime(ret[i][3])
				+"；\n并且为了表示歉意，系统已经自动在您的钱庄存款上增加了"
				+money_str(PAY_FOR_CRASH)
				+"，请查收\n"NOR);
	}
}

void init_statistic()
{
	ilaststatistic=time();
	pay_for_crash();//检查是否当过机
	call_out("do_statistic", MYLOG_TIME);
}

void do_statistic()
{
	write_log();
	//检查租期是否到了
	check_lease();
	//检查投标是否结束，该转为租期了
	check_bid();
	//dbquery("REPLACE mud_var SET name='leasetime',value='"+time()+"'");
	livetime = time();
	remove_call_out("do_statistic");
	if(!iifstop)
		call_out("do_statistic", MYLOG_TIME);
}

void stop_lease()
{
	iifstop=1;
	set_all_name(iifstop);
	remove_call_out("do_statistic");
}

mixed leasedb(string sql)
{
	mixed ret = dbquery(sql);	
	if(!ret){
		error("roomlease db error!");
		return 0;
	}
	return ret;	
}

int query_ifhavebidname(string valindex)
{
	mixed ret = leasedb("select U_id from "+DB_NAME+" where U_id='"+valindex+"'");
	if(!ret) return 0;
	if(sizeof(ret)<=0) return 0;
	if(sizeof(ret)>1){
		error("db error!");
		return 0;
	}
	return 1;
	//return 	( !undefinedp(roomwhere[valindex]) );
}

string *query_keys()
{
	string* r;
	mixed ret = leasedb("select U_id from "+DB_NAME);
	for(int i=0;i<sizeof(ret);i++)
	{
		if(!r) r = ({ret[i][0]});
		else r += ({ret[i][0]});
	}
	return r;
}

mapping query_amap(string valindex)
{
	mapping amap;
	mixed ret = leasedb("select * from "+DB_NAME+" where U_id='"+valindex+"'");
	if(sizeof(ret)<=0) return 0;
	if(sizeof(ret)>1){
		error("db error!");
		return 0;
	}
	amap = ([]);
	amap["files"] = explode(ret[0][2],",");//收费地点
	//amap["roomwhere"] = explode(ret[0][2],",");
	//这里要慎重点。。
	//amap["room_bidname"] = room_bidname[valindex];
	amap["bidtype"] = ret[0][3];
	amap["minirent"] = ret[0][4];
	amap["minirentadd"] = ret[0][5];
	amap["originshortname"] = ret[0][6];
	amap["leasetime"] = ret[0][7];
	amap["minskill"] = ret[0][8];
	amap["maxskill"] = ret[0][9];
	amap["discount"] = ret[0][10];

	amap["leaser"] = ret[0][11];
	amap["leasername"] = ret[0][12];
	amap["leaser_bidmoney"] = ret[0][13];
	amap["repayamount"] = ret[0][14];
	amap["payamount"] = ret[0][15];
	amap["begintime"] = ret[0][16];
	amap["endtime"] = ret[0][17];
	amap["leasertype"] = ret[0][18];

	amap["bider"] = ret[0][19];
	amap["bidername"] = ret[0][20];
	amap["bidamount"] = ret[0][21];
	amap["bidtime"] = ret[0][22];
	amap["bidendtime"] = ret[0][23];
	amap["bidertype"] = ret[0][24];
	amap["roomwhere"] = ret[0][25];//主房间
	amap["varmoney"] = ret[0][26];//效益
	amap["settime"] = ret[0][27];//开始设置的时间
	amap["paytime"] = ret[0][28];//最后一次进帐时间
	return amap;
}

int set_room(string* filename, string valbidname, int valbidtype, int valminirent, int valminirentadd, string valoriginshortname, int valleasetime,int valminskill, int valmaxskill, int valdiscount,string roomwhere)
{
	string sql;
	mixed ret = leasedb("select leaser,bider from "+DB_NAME+" where U_id='"+valbidname+"'");
	if(!ret) return 0;
	if(sizeof(ret)>1)
	{
		error("db error!");
		return 0;
	}
	/*
	if(sizeof(ret)==1)
	{
		if(ret[0][0]!="*")
		return notify_fail("这个房间还有人在租呢\n");
		if(ret[0][1]!="*")
		return notify_fail("这个房间还有人在投标呢\n");
	}
	*/
	if(sizeof(ret)>0)
	sql = "UPDATE "+DB_NAME+" SET "	
	+"U_filename='"+implode(filename,",")+ "',"
	+"bidtype='"+valbidtype+ "',"
	+"minirent='"+valminirent+ "',"
	+"minirentadd='"+valminirentadd+ "',"
	+"originshortname='"+valoriginshortname+ "',"
	+"leasetime='"+valleasetime+ "',"
	+"minskill='"+valminskill+ "',"
	+"maxskill='"+valmaxskill+ "',"
	+"roomwhere='"+roomwhere+ "',"
	+"settime='"+time()+ "',"
	+"discount='"+valdiscount+ "'"
	+" WHERE U_id='"+valbidname+"' AND U_Site='"+INTERMUD_MUD_NAME+"'";
	else sql = "REPLACE "+DB_NAME+" SET U_id='" + valbidname + "',"
	+"U_Site='" + INTERMUD_MUD_NAME + "',"
	+"U_filename='"+implode(filename,",")+ "',"
	+"bidtype='"+valbidtype+ "',"
	+"minirent='"+valminirent+ "',"
	+"minirentadd='"+valminirentadd+ "',"
	+"originshortname='"+valoriginshortname+ "',"
	+"leasetime='"+valleasetime+ "',"
	+"minskill='"+valminskill+ "',"
	+"maxskill='"+valmaxskill+ "',"
	+"roomwhere='"+roomwhere+ "',"
	+"settime='"+time()+ "',"
	+"discount='"+valdiscount+ "'";
	if(!sizeof(ret)) sql += ",bidendtime='"+(time()+300)+"'";
	if(leasedb(sql)) return 1;
	return 0;
}

int delete_room(string valbidname)
{
	string* room;
	object r;
	mixed ret = leasedb("select U_filename,leaser,bider from "+DB_NAME+" where U_id='"+valbidname+"' AND U_Site='"+INTERMUD_MUD_NAME+"'");
	if(!ret || sizeof(ret)<1) return 0;
	if(sizeof(ret)>1)
	{
		error("db error!");
		return 0;
	}
	//////这里看下是否正在招标中 或者正在运营中
	if(sizeof(ret)==1)
	{
		if(ret[0][1]!="*")
		return notify_fail("这个房间还有人在租呢\n");
		if(ret[0][2]!="*")
		return notify_fail("这个房间还有人在投标呢\n");
		room = explode(ret[0][0],",");		
	}
	if(!leasedb("DELETE FROM "+DB_NAME+" WHERE U_id='"+valbidname+"' AND U_Site='"+INTERMUD_MUD_NAME+"'"))
		return 0;
	if(room && sizeof(room)) for(int i=0;i<sizeof(room);i++)
	{
		r = find_object(room[i]);
		if(!r) continue;
		r->back_rsname();
	}
	write("删除成功！\n");
	return 1;
}

void set_all_name(int type)
{
	object r;
	mixed ret = leasedb("select roomwhere from "+DB_NAME+" where U_Site='"+INTERMUD_MUD_NAME+"'");
	//leaser!='*' AND 
	if(!ret || !sizeof(ret)) return;
	for(int i=0;i<sizeof(ret);i++)
	{
		r = find_object(ret[i][0]);
		if(!r) continue;
		if(type) r->back_rsname();
		else r->change_rsname();
	}
}

int new_bid(object me, string valbidname,int valbidamount, int valbidertype)
{
	string valroomname;
	int valbidtype;
	mixed ret;
	
	if(iifstop==1) return 0;
	ret = leasedb("select U_filename,originshortname,bidtype,bider,bidamount,leasetime,bidendtime,roomwhere from "+DB_NAME+" where U_id='"+valbidname+"' AND U_Site='"+INTERMUD_MUD_NAME+"'");
	if(!ret) return 0;
	if(sizeof(ret)>1)
	{
		error("db error!");
		return 0;
	}
	valroomname=get_myregions(ret[0][7])+ret[0][1];
		
	me->add("balance",-valbidamount);
	valbidtype=(ret[0][2]==1)?valbidertype:2;
	if( ret[0][3]!="*" )
		givemoney(ret[0][3],ret[0][4],
			HIY"对于【"+valroomname+"】，"
			+((valbidtype==2)?"一位匿名人士":me->query("name"))
			+"出价"
			+money_str(valbidamount)
			+"比你高，你预付的定金已退回你的存款，请查收\n"NOR);
		
	if(!leasedb("UPDATE "+DB_NAME+" SET "
	+"bider='"+me->query("id")+ "',"
	+"bidername='"+me->query("name")+ "',"
	+"bidamount='"+valbidamount+ "',"
	+"bidtime='"+time()+ "',"
	+"bidertype='"+valbidtype+ "'"
	+" WHERE U_id='" + valbidname + "' AND U_Site='" + INTERMUD_MUD_NAME + "'")) return 0;

	write(HIY"你"+((valbidtype==2)?"匿名":"实名")
		+"投标成功，投标押金已经从你的银行存款中扣除\n"
		+"现在的存款余额为"
		+money_str(me->query("balance"))
		+"\n"NOR);
	
	CHANNEL_D->do_channel(this_object(),"trade",((valbidtype==2)?"一位匿名人士":me->query("name"))
		+"出价"
		+money_str(valbidamount)
		+HIY"投标【"
		+valroomname
		+"】"
		+chinese_time(ret[0][5])
		+"的租用权，目前是最高价，投标将于"
		+chinese_time(ret[0][6]-time())
		+"后结束"NOR);
	/*
	message("channel:chat", 
		HIW"\n【商铺信息】"HIY
		+((valbidtype==2)?"一位匿名人士":me->query("name"))
		+"出价"
		+money_str(valbidamount)
		+HIY"投标【"
		+valroomname
		+"】"
		+chinese_time(ret[0][5])
		+"的租用权，目前是最高价，投标将于"
		+chinese_time(ret[0][6]-time())
		+"后结束\n"NOR,
		users());
	*/
	return 1;
}

void check_lease()
{
	int i;	
	string valreason,valroomname,valmsg;
	int irepayamount;
	int ipayoff;	
	mixed op;		
	mixed ret = leasedb("select U_id,repayamount,discount,leaser_bidmoney,roomwhere,originshortname,begintime,endtime,payamount,leaser,leasertype,leasername from "+DB_NAME+" where leaser!='*' AND U_Site='"+INTERMUD_MUD_NAME+"'AND endtime<'"+time()+"'");
	if(!ret || !sizeof(ret)) return;
	
	if(iifstop==1) return;
	
	for(i=0;i<sizeof(ret);i++)
	{
		op = ret[i];
		irepayamount=sum_by_discount(op[1],op[2]);		
		ipayoff=(op[3]>irepayamount)?
			op[3]-irepayamount
			:irepayamount-op[3];		
		valroomname=get_myregions(op[4])+op[5];
		
		valreason=HIY"你从"
			+longtime(op[6])
			+"起租的【"
			+valroomname
			+"】已经于"
			+longtime(op[7])
			+"到期结束\n总计收入为"
			+money_str(irepayamount)
			+"，你当初投标花费为"
			+money_str(op[3])
			+"，"
			+( (op[3]>irepayamount)?"亏损":"盈利" )
			+money_str(ipayoff)+"\n";
		if(op[8]) valreason +=
			"这期间你已经提款"
			+money_str(op[8])+"，";
		if(irepayamount-op[8]) valreason +=
			"余额"
			+money_str(irepayamount-op[8])
			+"已经划到你的银行存款，";
		valreason +="请查收\n"NOR;
				
		givemoney(op[9],irepayamount-op[8],valreason);
		valmsg = ((op[10]==2)?"一位匿名人士":op[11])
			+"租的【"
			+valroomname;
					
		if( iifpublicrepay==1 )
			valmsg += "】已经到期结束，总收入为"
				+money_str(irepayamount)
				+"，"
				+( (op[3]>irepayamount)?"亏损":"盈利" )
				+money_str(ipayoff)+NOR;
				//+"\n"NOR;
		else
			valmsg += "】已经到期结束。\n"NOR;
		
		CHANNEL_D->do_channel(this_object(),"trade",valmsg );

		//message("channel:chat", valmsg, users());
		
		log_file("leaselog","【"+valroomname+"】"
			+op[11]
			+((op[10]==2)?"匿名":"实名")
			+"租的【"
			+valroomname
			+"】已经到期结束，总收入为"
			+money_str(irepayamount)
			+"，"
			+( (op[3]>irepayamount)?"亏损":"盈利" )
			+money_str(ipayoff)
			+"\n");
		
		if(!leasedb("UPDATE "+DB_NAME+" SET "
		+"leaser='*',"
		+"leasername='*',"
		+"leaser_bidmoney='"+0+ "',"
		+"repayamount='"+0+ "',"
		+"payamount='"+0+ "',"
		+"begintime='"+0+ "',"
		+"endtime='"+0+ "',"
		+"leasertype='"+1+ "'"
		+" WHERE U_id='" + op[0] + "' AND U_Site='" + INTERMUD_MUD_NAME + "'"))
			log_file("leaselog","上步数据库操作失败。");
		change_dp(op[0]);
	}
}

void check_bid()
{
	int i;
	mixed op;
	//int inowtime;
	string valreason,valroomname;
	mixed ret;
	
	if(iifstop==1) return;
	ret = leasedb("SELECT U_id,bider,bidendtime,leasetime,roomwhere,originshortname,leaser,bidamount,bidertype,minirent,bidername  from "+DB_NAME+" where U_Site='"+INTERMUD_MUD_NAME+"' AND bidendtime<'"+time()+"'");
	for(i=0;i<sizeof(ret);i++){
		op = ret[i];
		//bider,bidendtime,leasetime,roomwhere,originshortname,leaser,bidamount,bidertype,minirent,bidername
		//[valindex[i]]
		if( op[1]=="*" ){
			//如果到期了还没有投标者，就将时间延长			
			//op[2] = time()+op[3]+60;			
			valroomname=get_myregions(op[4])+op[5];
			
			CHANNEL_D->do_channel(this_object(),"trade","由于【"
				+valroomname
				+"】尚无人投标，将截标时间延长到"
				+shorttime(op[2])
				+"，请大家快来捞便宜货呀"NOR );
			/*
			message("channel:chat",   
				HIW"\n【商铺信息】"HIY
				+"由于【"
				+valroomname
				+"】尚无人投标，将截标时间延长到"
				+shorttime(op[2])
				+"，请大家快来捞便宜货呀\n"NOR,
				users()); */
		   	log_file("leaselog","由于【"+valroomname+"】尚无人投标，将截标时间延长到"+longtime(op[2])+"\n");
		   	if(!leasedb("UPDATE "+DB_NAME+" SET "
			+"bidendtime='"+(time()+op[3]+60)+ "'"
			+" WHERE U_id='" + op[0] + "' AND U_Site='" + INTERMUD_MUD_NAME + "'"))			
			log_file("leaselog","上步数据库操作失败。");
			continue;
		};
		//如果当前房间还有别人租用，也不能去租
		if( op[6]!="*" )
			continue;
			
		valroomname=get_myregions(op[4])+op[5];
		valreason=HIY"【"
			+valroomname
			+"】的投标中，你已经中标，中标价为："
			+money_str( op[7])
			+"，从"
			+longtime(time() )
			+"起租，到"
			+longtime(time()+op[3] )
			+"结束\n"NOR;
			
	   	log_file("leaselog","【"+valroomname+"】"
   			+op[10]
			+((op[8]==2)?"匿名":"实名")
   			+"中标，中标价为："
			+money_str(op[7])
			+"，从"
			+longtime(time())
			+"起租，到"
			+longtime(time()+op[3] )
			+"结束\n");
		
		//好了，将投标变为租
		
		if(!leasedb("UPDATE "+DB_NAME+" SET "
		+"leaser='"+op[1]+ "',"
		+"leasername='"+op[10]+ "',"
		+"leaser_bidmoney='"+op[7]+ "',"
		+"repayamount='"+0+ "',"
		+"payamount='"+0+ "',"
		+"begintime='"+time()+ "',"
		+"endtime='"+(time()+op[3])+ "',"
		+"leasertype='"+op[8]+ "',"
		+"bider='*',"
		+"bidername='*',"	
		+"bidamount='"+0+ "',"
		+"bidtime='"+(time()+NEXT_BID)+ "',"
		+"bidendtime='"+(time()+op[3]+MYLOG_TIME )+ "',"
		+"bidertype='"+1+ "'"
		+" WHERE U_id='" + op[0] + "' AND U_Site='" + INTERMUD_MUD_NAME + "'"))
			log_file("leaselog","上步数据库操作失败。");
		//下次开始投标时间应该在这次周期结束后
		//投标结束时间比房间租期到的时间多一点时间		
		givemoney(op[6],0,valreason);
		
		CHANNEL_D->do_channel(this_object(),"trade","在【"
			+valroomname
			+"】的投标中，"
			+((op[8]==2)?"一位匿名人士":op[10])
			+"中标，中标价为："
			+money_str(op[7])
			+HIY"，从"
			+shorttime(time())
			+"起租，到"
			+shorttime(time()+op[3])
			+"结束");
	/*
		message("channel:chat",   
			HIW"\n【商铺信息】"HIY
			+"在【"
			+valroomname
			+"】的投标中，"
			+((op[8]==2)?"一位匿名人士":op[10])
			+"中标，中标价为："
			+money_str(op[7])
			+HIY"，从"
			+shorttime(time())
			+"起租，到"
			+shorttime(time()+op[3])
			+"结束\n"NOR,
			users());
		*/
		CHANNEL_D->do_channel(this_object(),"trade","【"
			+valroomname
			+"】的下一次投标将于"
			+shorttime(time()+NEXT_BID)
			+"开始，底价为："
			+money_str(op[9])
			+"，请大家踊跃投标\n"NOR );
		/*
		message("channel:chat",   
			HIW"\n【商铺信息】"HIY
			+"【"
			+valroomname
			+"】的下一次投标将于"
			+shorttime(time()+NEXT_BID)
			+"开始，底价为："
			+money_str(op[9])
			+"，请大家踊跃投标\n"NOR,
			users());
		*/
		change_dp(op[0]);
	}
}

void write_log()
{
	int i;
	int inowtime;
	string valreason,valroomname;
	string valfilename;
	int irepayamount;
	int ipayoff;
	mixed op;
	mixed ret;
				
	inowtime=time();
	if( inowtime<(ilaststatistic+MYLOG_TIME) )
		return;
	ilaststatistic=inowtime;
	ret = leasedb("SELECT U_id,repayamount,discount,leaser_bidmoney,roomwhere,originshortname,leaser,begintime,endtime,payamount from "+DB_NAME+" where U_Site='"+INTERMUD_MUD_NAME+"'");
	if(!ret || sizeof(ret)<1) return;
	for(i=0;i<sizeof(ret);i++){
		op= ret[i];
		valfilename = "lease/"+op[0];
		
		irepayamount=sum_by_discount(op[1],op[2]);
		ipayoff=(op[3]>irepayamount)?
			op[3]-irepayamount
			:irepayamount-op[3];
		valroomname=get_myregions(op[4])+op[5];

		valreason=op[6]
			+"从"
			+shorttime(op[7])
			+"起租的【"
			+valroomname
			+"】结束期"
			+shorttime(op[8])
			+"\n    总计收入为"
			+money_str(irepayamount)
			+"，当初投标花费为"
			+money_str(op[3])
			+"，"
			+( (op[3]>irepayamount)?"亏损":"盈利" )
			+money_str(ipayoff)
			+"\n期间已经提款"
			+money_str(op[9])
			+"，余额"
			+money_str(irepayamount-op[9])
			+"，当前时间为:"
			+shorttime(time())
			+"\n";
	   	log_file(valfilename,valreason);
	}
}

int tikuan(object me, string valbidname,int amount)
{
	int commision;
	string valroomname;
	mixed ret;	
		
	if(iifstop==1){
		write("市场已经停止作业！\n");
		return 1;
	}
	commision=amount/10;	
	if(!leasedb("UPDATE "+DB_NAME+" SET "
		+"payamount=payamount+'"+(amount+commision)+ "'"		
		+" WHERE U_id='" + valbidname + "' AND U_Site='" + INTERMUD_MUD_NAME + "'"))
	{
		write("划帐失败，可能商店已经倒闭，快联系wiz。\n");
		return 1;
	}
	
	me->add("balance",amount);
	ret = leasedb("SELECT roomwhere,originshortname,payamount from "+DB_NAME+" where U_Site='"+INTERMUD_MUD_NAME+"' AND U_id='"+valbidname+"'");
	if(!ret || sizeof(ret)!=1) return 0;	
	//payamount[valbidname]+=amount+commision;		
	valroomname=get_myregions(ret[0][0])+ret[0][1];
	write(HIY"\n你从【"
			+valroomname
			+"】的收益中预支"
			+money_str(amount)
			+"到你的银行存款,加收手续费"
			+money_str(commision)
			+"这期间你累计预支金额和手续费为"
			+money_str(ret[0][2])
			+"\n"NOR);
	return 1;
}

string getroomshort(string valroomfilename)
{
	string perstr;
	mixed ret;
	
	if(iifstop==1) return 0;
	ret = leasedb("SELECT leaser,originshortname,leasertype,leasername from "+DB_NAME+" where U_Site='"+INTERMUD_MUD_NAME+"' AND roomwhere='"+valroomfilename+"'");
	//message("wizard:ciwei",sprintf("%O\n",ret),users());
	if(!ret || sizeof(ret)<1 )
		return "*";
	perstr = "";
	if( ret[0][0] == "*" )
		return "待租的"+ret[0][1];
	if( ret[0][2] == 2 )
		return "已租的"+ret[0][1];
	return ret[0][3]+"的"+ret[0][1];
}

void add_money(string valroomfilename,int valmoneyamount)
{
	mixed ret = leasedb("SELECT U_id from "+DB_NAME+" where U_Site='"+INTERMUD_MUD_NAME+"' AND U_filename LIKE '%"+valroomfilename+"%'");
	if(!ret || sizeof(ret)<1 ) return;
	//if( undefinedp(room_bidname[valroomfilename]) )
	//	return;
	if(!leasedb("UPDATE "+DB_NAME+" SET "
		+"paytime='"+time()+ "',"
		+"repayamount=repayamount+'"+(valmoneyamount)+ "'"
		+" WHERE U_id='" + ret[0][0] + "' AND U_Site='" + INTERMUD_MUD_NAME + "'"))
		log_file("leaselog","付帐失败。");
	//repayamount[room_bidname[valroomfilename]] += valmoneyamount;
}

void change_dp(string valbidname)
{
	object obj;
	mixed ret = leasedb("SELECT roomwhere  from "+DB_NAME+" where U_Site='"+INTERMUD_MUD_NAME+"' AND U_id='"+valbidname+"'");
	if(sizeof(ret)<1) return;
	if(sizeof(ret)>1) error("db error!");
	obj = new("/clone/npc/spguanjia");
	obj->set("target", ret[0][0]);
//	obj->set("workflag", valflag);
	obj->move(ret[0][0]);
}

int sum_by_discount(int ival,int idiscount)
{
	return (ival*idiscount)/10000;
}

string get_myregions(string str)
{
	string regions;
		
	regions = TASK_D->get_regions(str);
    if( regions == "" )
    	regions = "中原";
    return regions;
}

string money_str(int amount)
{
	// returns a chinese string of `amount` of money
	string output;
		
	if(amount==0)
		return "零两白银";

	if (amount / 10000) {
		output = chinese_number(amount / 10000) + "锭黄金";
		amount %= 10000;
	}
	else
		output = "";
	if (amount / 100) {
		output = output + chinese_number(amount / 100) + "两白银";
		amount %= 100;
	}
	if (amount)
		return output + chinese_number(amount) + "文铜钱";
	return output;
}

string chinese_time(int total)
{
	int d, h, m, s;
	string tmp = "";

	if (!total)
		return "零秒";
	d = total / 86400;
	if (d) tmp += CHINESE_D->chinese_number(d) + "天";
	h = (total % 86400) / 3600;
	if (h) tmp += CHINESE_D->chinese_number(h) + "小时";
	m = (total % 3600) / 60;
	if (m) tmp += CHINESE_D->chinese_number(m) + "分";
	s = total % 60;
	if (s) tmp += CHINESE_D->chinese_number(s) + "秒";
		else if (m) tmp += "钟";
	return tmp;
}

string Cday(string ts)
{
	int d;
	sscanf(ts," %d",d);
	sscanf(ts,"%d",d);
	if(!d) return 0;
	return chinese_number(d)+"日";
}

string longtime(int t)
{
	string ts = ctime(t);
	ts = " "+ts[19..23]+"年"+ts[4..6]+Cday(ts[8..9])+ts[10..15];
	return Ctime(ts);
}

string shorttime(int t)
{
	string ts = ctime(t);
	ts = ts[4..6]+Cday(ts[8..9])+ts[10..15];
	return Ctime(ts);
}

string Ctime(string ts)
{

	ts = replace_string(ts, "Jan", "一月");
	ts = replace_string(ts, "Feb", "二月");
	ts = replace_string(ts, "Mar", "三月");
	ts = replace_string(ts, "Apr", "四月");
	ts = replace_string(ts, "May", "五月");
	ts = replace_string(ts, "Jun", "六月");
	ts = replace_string(ts, "Jul", "七月");
	ts = replace_string(ts, "Aug", "八月");
	ts = replace_string(ts, "Sep", "九月");
	ts = replace_string(ts, "Oct", "十月");
	ts = replace_string(ts, "Nov", "十一月");
	ts = replace_string(ts, "Dec", "十二月");
	return ts;
}

int strtoint(string arg)
{
	int t;
	if(!arg) return 0;
	if(sscanf(arg,"%d",t)==1) return t;
	return 0;
}


int givemoney(string valuserid,int money,string valreason)
{
	object body,ob;

	if(objectp(body = LOGIN_D->find_body(valuserid))) {
		body->add("balance",money);
		if( money!=0 )
			valreason += sprintf(HIY"现在的存款余额为%s\n"NOR,
				money_str(body->query("balance")));
		tell_object(body, valreason);
//		destruct(body);
	}else{
		ob = new(LOGIN_OB);
		ob->set("id", valuserid);
		
		if( !ob->restore() ) {destruct(ob); return 1;}
		body = LOGIN_D->make_body(ob);
		if( body->restore() ) {
			body->add("balance",money);
			if( money!=0 )
				valreason += sprintf(HIY"现在的存款余额为%s\n"NOR,
					money_str(body->query("balance")));
			//if( !body->query("leasemsg") )
			//	body->set("leasemsg","");
			valreason = sprintf(HIW"【离线期间信息】"HIY"你在离线后，于%s系统通知你\n",
				 longtime(time()))+valreason;
			//body->set( "leasemsg",
			//	((!body->query("leasemsg"))?valreason:body->query("leasemsg")+valreason) );
			MSG_CMDS->system_send(this_object(),({valuserid}),"商铺经营报告",valreason);
			//add
			body->set_temp("db_quit",1);
			body->save();
		}
		destruct(ob);
		destruct(body);
	};
	return 1;
}

string get_money_str(int coin)
{
	string output;
	
	if(!coin) return HIW"无"NOR;	
	output = MONEY_D->money_str(coin);
	while(strlen(strip(output))>10)
	{
		if(strsrch(output,"铜钱")!=-1 && strsrch(output,"白银")!=-1)
		{
			output = output[0..strsrch(output,"白银")+3];
			continue;
		}
		
		if(strsrch(output,"铜钱")!=-1 && strsrch(output,"黄金")!=-1)
		{
			output = output[0..strsrch(output,"黄金")+3];
			continue;
		}
		
		if(strsrch(output,"白银")!=-1 && strsrch(output,"黄金")!=-1)
		{
			output = output[0..strsrch(output,"黄金")+3];
			continue;
		}
		
		break;
	}
	return output;
}

string query_list(string id)
{
	mapping leasemap;
	string *indexval, outstr,roomset,leasestr,bidstr;
	string valroomname;
	int i;
	
	indexval= query_keys();
	if(!sizeof(indexval)) return 0;
	
	roomset="";
	leasestr="";
	bidstr="";
	for(i=0;i<sizeof(indexval);i++)
	{
		leasemap=query_amap(indexval[i]);
		valroomname=get_myregions(leasemap["roomwhere"])+leasemap["originshortname"];
		//message("wizard:ciwei",sprintf("id:%s,map:%O\n",indexval[i],leasemap),users());
		roomset+=sprintf("│%-30s%|10s%|20s%|20s%|16s%|16s│\n",
			valroomname+NOR"("+indexval[i]+")",
			( (leasemap["bidtype"]==0)?RED"停止投标"NOR:((leasemap["bidtype"]==1)?BLU"实名投标"NOR:CYN"匿名投标"NOR) ),
			get_money_str(leasemap["minirent"]),
			//sprintf("%d锭"HIY+"黄金"NOR,leasemap["minirent"]/10000),
			get_money_str(leasemap["minirentadd"]),			
			//sprintf("%d锭"HIY+"黄金"NOR,leasemap["minirentadd"]/10000),
			chinese_time(leasemap["leasetime"]),
			"万分之"+CHINESE_D->chinese_number(leasemap["discount"])
			);
		if((leasemap["bidtype"]!=0 || leasemap["leasername"]!="*")&&(!id||leasemap["leaser"]==id))//屏蔽已经停止投标 而且当前无出租人
		{		
		if(leasemap["leaser"]==id)
		leasestr+=sprintf("│%-30s%|4s%|20s%|18s%|20s%|20s│\n",
			valroomname+"("+indexval[i]+")",
			((leasemap["leasertype"]==2)?RED"匿名"NOR:HIG"实名"NOR),
			get_money_str(leasemap["leaser_bidmoney"]),
			//sprintf("%d锭"HIY+"黄金"NOR,leasemap["leaser_bidmoney"]/10000),
			(leasemap["endtime"]==0)?"无":shorttime(leasemap["endtime"]),
			get_money_str(sum_by_discount(leasemap["repayamount"],leasemap["discount"])),
			//sprintf("%d锭"HIY+"黄金"NOR,sum_by_discount(leasemap["repayamount"],leasemap["discount"])/10000),
			get_money_str(leasemap["payamount"]),
			//sprintf("%d锭"HIY+"黄金"NOR,leasemap["payamount"]/10000),
		);
		else 
		leasestr+=sprintf("│%-30s%|10s%|20s%|52s│\n",
			valroomname+NOR"("+indexval[i]+")",
			( (leasemap["leasername"]=="*")?"无人":((leasemap["leasertype"]==2)?"匿名人士":leasemap["leasername"]) ),
			get_money_str(leasemap["leaser_bidmoney"]),
			//sprintf("%d锭"HIY+"黄金"NOR,leasemap["leaser_bidmoney"]/10000),
			sprintf("%+25s%2s%-25s",(leasemap["begintime"]==0)?"无":shorttime(leasemap["begintime"]),
						HIC"→"NOR,
						(leasemap["endtime"]==0)?"无":shorttime(leasemap["endtime"])
			),
			);
		}		
		//投标情况
		if((leasemap["bidtype"]!=0||leasemap["bidername"]!="*")&&(!id||leasemap["bider"]==id))//屏蔽已经停止投标 而且当前无投标人
		bidstr+=sprintf("│%-30s%|10s%|20s%|20s%|20s%|12s│\n",
			valroomname+NOR"("+indexval[i]+")",
			(leasemap["bidername"]=="*")?"无人":((leasemap["bidertype"]==2)?"匿名人士":leasemap["bidername"]),
			//sprintf("%d两"HIW+"白银"NOR,leasemap["bidamount"]/100),
			get_money_str(leasemap["bidamount"]),
			//sprintf("%d锭"HIY+"黄金"NOR,leasemap["bidamount"]/10000),
			(leasemap["bidtime"]==0)?"无":shorttime(leasemap["bidtime"]),
			(leasemap["bidendtime"]==0)?"无":shorttime(leasemap["bidendtime"]),
			leasemap["bidtype"]==0?RED"停止投标"NOR:( time()<leasemap["bidtime"]?HIY"准备投标"NOR:((leasemap["bidendtime"]>time())?HIG"正在投标"NOR:HIY"投标截止"NOR))
			);
	};
	outstr="";
	outstr+=sprintf("┌───『当前出租的店铺有%4d个』────────────────────────────────────────┐\n",sizeof(indexval));
	outstr+="│   店铺                        投标类型      最低投标价           最低加价            租期          提成比例    │\n";
	outstr+=roomset;
	if(leasestr!="")
	{
	outstr += "├───『承租情况』───────────────────────────────────────────────┤\n";
	if(id)
		outstr+="│   店铺                       类型       中标价            租期截止             收益                预支        │\n";
	else    outstr+="│   店铺                         承租人         中标价                           租        期                    │\n";
	outstr+=leasestr;
	}
	if(bidstr!="")
	{
	outstr += "├───『投标情况』───────────────────────────────────────────────┤\n";	
	outstr+="│   店铺                       最高出价人       投标价             投标时间            结束时间        投标状态  │\n";
	outstr+=bidstr;
	}
	outstr += "└────────────────────────────────────────────────────────┘\n";
	
	return outstr;	
}
