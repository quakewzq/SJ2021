// feng.c 冯铁匠
//Modified By ChinaNet
//By 2004/1/11
//任务文件：
//	feng.c	place.h	chutou.c mine.c	robber.c robber_n.c
//Modified By ChinaNet
//By 2004/1/29 
//增加随机强盗 robber.c,增加随机强盗 robber_n.c,限制放弃次数：minejob_failed,增加成功与放弃对任务的影响。增加次数查询。
//by 2004/3/12 ChinaNet

//add exp By ChinaNet in chutou.c and robber_n.c,fix address bug in place.h,Busy Time 减半。in this file.每50次增加奖励。in this file.
//by 2004/4/28

//修正格式。
//by 2004/4/30 by ChinaNet in this file and place.h

//完成随机奖励check_encour in place.h,fixed check_happy bug in place.h,added log file in this file, place.h ,robber_n.
//by 2004/5/05


inherit NPC;
inherit F_DEALER;

string ask_ylj4();
string ask_ylj5();
string ask_mine_job();
string ask_mine_quality();
string ask_mine_repair();
string ask_mine_product();
string ask_mine_cancle(); 
int ask_mine_times(); 

#include "place.h";

void create()
{
        set_name("冯铁匠", ({ "feng tiejiang", "feng"}) );
        set("gender", "男性" );
        set("age", 53);
        set("long",@long 
冯铁匠想是常年弯腰打铁，背已驼了，双眼被烟火薰的又红又细，
左腿残废，肩窝下撑著一根拐杖。
你可以向他询问有关采矿(Mine)任务的细节。	
long);
        set("combat_exp", 50000);

        set("str", 24);
        set("dex", 17);
        set("con", 28);
        set("int", 27);
        set("shen_type", 1);
        set("no_quest", 1);
        set("no_ansuan", 1);
        set("attitude", "friendly");

        set("attitude", "friendly");
        set_skill("dodge", 70);
        set_skill("hammer", 40);
        set_skill("parry", 60);
        set_skill("force", 40);
        set_temp("apply/attack", 40);
        set_temp("apply/defense", 40);
        set("vendor_goods", ({
                __DIR__"obj/hammer",
        }));
        set("inquiry", ([
                "name": "小人姓冯，村里人都叫我冯铁匠。",
                "here": "这里是小人糊口的铺子，小人就住在後边的屋子。",
                "锄头": "锄头... 抱歉，锄头已经卖光了...",
                "铁锤": "铁锤？小人做的铁锤坚固又耐用，一把只要三百文钱。",
                "铸剑": (: ask_ylj4 :),
                "师尊": (: ask_ylj5 :),
                "冯默风" : "唉～，这个名字小人已经好久没有听到过了...",
                "奇门遁甲" : "那都是小时候学的，平时没事解解闷罢了。",
                "mine":	(: ask_mine_job :),
                "job":	(: ask_mine_job :),
                "采矿":	(: ask_mine_job :),
                "矿石": (: ask_mine_quality :),
                "quality": (: ask_mine_quality :),
                "修理": (: ask_mine_repair :),
                "repair": (: ask_mine_repair :),
                "加工":	(: ask_mine_product :),
                "放弃": (: ask_mine_cancle :),
                "贡献": (: ask_mine_times :),
                "次数": (: ask_mine_times :),
        ]) );
        setup();
       	carry_object(ARMOR_D("armor/cloth"))->wear();
}

//采矿任务
void init()
{
	add_action("do_sell","sell");
	add_action("do_sell","mai");
}

int do_sell(string arg)
{
	object me, ob, obj;
	int value, pot, times, failed_times, exp, mine_skill, encour;
	string msg;
	
	me = this_player();
	ob = this_object();
	times = me->query("minejob");
	failed_times = me->query("minejob_failed");
	mine_skill = me->query_skill("mining",1);
	exp = me->query("combat_exp");
	if( me)	
		if( wizardp(me)) tell_object(me, "times = " + times + ".failed_times = " + failed_times + ".mine_skill = " + mine_skill + ".exp = " + exp + ".\n");
		
	if (!arg || !(obj = present(arg, me)))
		return notify_fail("你要卖什么？\n");
	
	if (obj->query("id") != ("kuang shi"))
		return notify_fail("我是铁匠，对这个不感兴趣。\n");
	
	if (!me->query_temp("minejob/ask"))
		return notify_fail("我好象没让你去采矿石吧？\n");
		
	if (!me->query_temp("minejob/find"))
		return notify_fail("这是你自己采的吗？不要乱拿别人的东西。\n");
		
	me->set("job_name","开采矿石");	
        me->add("job_time/冯铁匠",1);
		
        value = obj->query("value")/10;
	

//	因为gold不缺，目前设置成只加pot，等darken的药品系统完成后再改回加gold。
	message_vision("$N以" + MONEY_D->price_str(value) + "的价格卖掉了一" + obj->query("unit") +
				obj->name() + "给$n。\n", me, ob);

	MONEY_D->pay_player(me, value);
	//me->clear_condition("mine_job",time);
	//me->apply_condition("mine_job",time);

	pot = me->query("potential");
        me->add("combat_exp", value/100);
	if (wizardp(me)) 
		tell_object(me,"这块矿石的价值是：" + value + "。\n");
	message_vision("$N将一" + obj->query("unit") + obj->name() + "交给$n。\n", me, ob);
        tell_object(me, "你得到了" + CHINESE_D->chinese_number(value/100) + "点实战经验。\n");
	
	if( (times % 30) == 0 && failed_times < 200)
	{
//随机奖励种类。
		encour = check_encour(me);
		msg = check_happy(me, obj, encour);
		tell_object(me,msg);
	}

        if (me->query("potential") > me->query("max_pot") * 8)
	{

                tell_object(me,"可惜很遗憾，受经验所限，你损失了"+chinese_number( value / 100 - (me->query("max_pot") * 8 - pot))+"点潜能。\n");
		me->set("potential", me->query("max_pot") * 2);
	}

	if(obj->query("level") == "hard" || obj->query("level") == "veryhard")
	log_file("job/minejob",sprintf("%s %s(%s)sell了%s级别的%s。\n",
		ctime(time())[4..19],me->name(1),capitalize(me->query("id")),obj->query("level"),obj->query("name")));
	me->delete_temp("minejob");
	destruct(obj);
	return 1;
}
string ask_mine_job()
{
	object me,obj,mine,robber;
	string place_level;
	string str,strb,strc;
	string job_type;
	int time,killer;

	me = this_player();
	place_level = "normal";
	job_type = "开采";
	killer = 0;

	if (me->query_temp("minejob/ask"))
		return "你找打是不是？还不去工作！";

	if (me->query_condition("mine_job") > 0)
		return "你刚做完开采矿石任务，再等等吧。";

	if( me->query_condition("job_busy"))
		return "你现在正忙着做其他任务呢！";

	if (me->query_con() <= 30)
		return ("你的身体恐怕难以承受这样的劳动。");

//判断地点的难易，并由此判断出矿石的质量和属性
	place_level = check_level(me);
//判断是否有抢劫。
	killer = check_killer(place_level);

	str = get_address(place_level,me);//获取地点C文件
	strb = get_place(str);		//取得地区信息
	strc = load_object(str)->query("short");
	time = random(5)+ 5;
	
//Add by ChinaNet 2004/2/10
	if (random(20) > 10 && me->query_skill("caikuang",1)>=80 )
		job_type = "抢劫";
	
	if (job_type == "开采")
	{
		me->set_temp("minejob/area",str);
		me->set_temp("minejob/areab",strb);
		me->set_temp("minejob/areac",strc);
		me->set_temp("minejob/ask",1);
		me->set_temp("minejob/level",place_level);
		me->set_temp("minejob/times",0);
		me->set_temp("minejob/type",job_type);
		me->set("job_name","开采矿石");
		me->apply_condition("job_busy",time);
		me->apply_condition("mine_job",time + 5);

		if (wizardp(me))
			tell_object(me,"获取地点是："+str+"    区域位置："+strb+"    任务难度："+place_level+"。\n");
		
        	if ( !objectp( present("chu tou", me)) ) 
        	{
                	obj = new(__DIR__"obj/chutou.c");
                	obj->set("user",me->query("id"));
                	obj->move(me);
	                message_vision("冯铁匠转身从身后拿出了一把锄头给$N。\n",me);
        	}
			
//Add by ChinaNet 2004/2/1 
//杀人
		if(place_level == "hard" || place_level == "veryhard")
		log_file("job/minejob",sprintf("%s %s(%s)开采%s级别矿石。地点文件：%s。区域：%s。\n",
			ctime(time())[4..19],me->name(1),capitalize(me->query("id")),place_level,str,strb));

		if (killer)
			{
				me->set_temp("minejob/killer",1);
				return "这位" + RANK_D->query_respect(me) + "，你现在就去" + strb + strc + "去看一看，可能会有收获。前路艰险，一切多加小心。\n";
			}
		return "这位" + RANK_D->query_respect(me) + "，你现在就去" + strb + strc + "去看一看，可能会有收获。\n";
	}
	
//add by ChinaNet 2004/2/10
//抢劫矿石
	if (job_type == "抢劫")
	{
		me->set_temp("minejob/area",str);
		me->set_temp("minejob/areab",strb);
		me->set_temp("minejob/areac",strc);
		me->set_temp("minejob/ask",1);
		me->set_temp("minejob/level",place_level);
		me->set_temp("minejob/times",0);
		me->set_temp("minejob/type",job_type);
		me->set("job_name","开采矿石");
		me->apply_condition("job_busy",time);
		me->apply_condition("mine_job",time + 10);
		
		mine = new(__DIR__"obj/mine.c");
		mine = settings_mine(place_level, mine);
		robber = new(__DIR__"obj/robber_n.c");
		robber->set_temp("target",me->query("id"));
		robber->set_temp("minejob/level",place_level);
		robber->move(load_object(str));
		robber->set("long",robber->query("long")+"他刚刚收到消息，"+me->query("name")+"("+me->query("id")+")对他携带的"+mine->query("name")+"很有兴趣。\n他紧张的此处张望，小心戒备以策万全。\n");		
		mine->add("value",random(50000)+50000);
		mine->move(robber);		
		if(place_level == "hard" || place_level == "veryhard")
		log_file("job/minejob",sprintf("%s %s(%s)抢劫%s级别矿石。地点文件：%s。区域：%s。Npc:%s(%s)\n",
			ctime(time())[4..19],me->name(1),capitalize(me->query("id")),place_level,str,strb,robber->query("name"),robber->query("id")));
		if (wizardp(me))
			tell_object(me,"获取地点是："+str+"    区域位置："+strb+"    任务难度："+place_level+"。\n");
		
		return "听闻"+robber->query("name")+"在" + strb + strc + "附近走私矿石，你去想想办法。此人狡猾凶狠，多加小心。\n";		
	}
	return "其他类型构思中。";
}

string ask_mine_cancle()
{
	object obj, me = this_player();
	
	if ( !me->query_temp("minejob") )
		return "你没要任务，放弃什么？\n";
//限制放弃：
	if( me->query("menejob_failed") >= 200 && random(5) == 1)
		return "就想找便宜，哪有那么多好事，快去。\n";
		
	if (obj = present("chu tou", me))
		destruct(obj);
	me->delete_temp("minejob");
        me->add("minejob_failed",1);
   me->apply_condition("mine_job",10);
	me->set("job_name","开采矿石");	
	return "既然不想做了，你走吧。\n";
}

int ask_mine_times()
{    
	object me,ob;
	int i,j;
	me = this_player(); 
	ob = this_object();
	
    i = me->query("job_time/冯铁匠");
	j = me->query("minejob_failed");
	
	if( !i )
		return notify_fail("你采过石头吗?"); 
		
	if( !j )
		message_vision("$N对着$n想了想，说道，你目前已做了" + chinese_number(i) + "次任务。\n", ob,me);
	else 
		message_vision("$N对着$n想了想，说道，你目前已做了" + chinese_number(i) + "次任务，放弃了" + chinese_number(j) + "次。\n", ob,me);
	return 1;
}

string ask_mine_quality()
{
	object me;
	me = this_player();
	return "这位" + RANK_D->query_respect(me) + "，矿石质量验证正在制作中，敬请期待。\n";
}
string ask_mine_repair()
{
	object me;
	me = this_player();
	return "这位" + RANK_D->query_respect(me) + "，修理兵器功能正在制作中，敬请期待。\n";
}

string ask_mine_product()
{
	object me;
	me = this_player();
	return "这位" + RANK_D->query_respect(me) + "，改造兵器功能正在制作中，敬请期待。\n";
}

int accept_object(object me, object ob)
{
        object sword;
        if (ob->query("id") =="mowen xuantie") {
            if(me->query_temp("ylj/step4")) {
            	me->delete_temp("ylj/step4");
            	me->set_temp("ylj/step5", 1 );
                say("冯铁匠说道：啊？！墨纹玄铁，用此铁铸剑需要用到桃花岛铸剑的不传之密，未得师尊许可，在下......\n");
	        return 1;
              	}
	        else say("这东西我要来没用。\n");
        }
        else if (ob->query("id") == "ling pai") {
             if(me->query_temp("ylj/stepend") && environment(this_object())->query("short") == "铁匠铺" ) {
                sword = unew(BINGQI_D("sword/youlong-jian"));
        	if( clonep(sword) ) {
        		sword->move(me);
	        	me->delete_temp("ylj/stepend");
                	say("冯默风大喜道：在下无以为报，只有尽心铸剑以报深恩......\n");
		        return 1;
                	}
              	}
		else say("这东西我要来没用。\n");
        }
	return 0;
}

void destroy(object ob)
{
        destruct(ob);
        return;
}

string ask_ylj4()
{
        object me;
        me = this_player();
        if ( !me->query_temp("ylj/step3") )
        	return "剑在后面屋里，自己进去取吧。\n";
        me->delete_temp("ylj/step3");
        command("look "+me->query("id"));
       	me->set_temp("ylj/step4",1);
	return "这位" + RANK_D->query_respect(me) + "，是否带了铸剑的材料？\n";
}

string ask_ylj5()
{
        object me, obj;
        me = this_player();
        if ( !me->query_temp("ylj/step5") )
        	return "在下师尊的名讳，可不是说与你听的。\n";
        me->delete_temp("ylj/step5");
	obj = new(__DIR__"obj/ling");
        if( clonep(obj) ) {
        	obj->move(me);
	       	me->set_temp("ylj/step6",1);
		return "我本是桃花岛弟子，由于师尊黄药师丢失了九阴真经，一\n
怒之下把我们师兄弟的腿脚打断，逐出了师门，好久没见师尊了，不知师尊的\n
身体如何。你有时间的话，能否为我跑一趟桃花岛，我这有一块令牌是当年师\n
尊送给我的，凭此信物拜访我师傅，说默风无时无刻不在想念他老人家......\n";
       	}
       	return "在下师尊的名讳，可不是说与你听的。\n";
}
