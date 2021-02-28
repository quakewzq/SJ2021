// rebuild for smy job
// by Lklv 2002.07.12
// hehe by Ciwei 2004
// update by lsxk ,调用TASKREWARD_D统一计算经验奖励。  2008/1/8

#include <ansi.h>

#define JOB_NPC "/d/gb/npc/xixia-wushi"
//#define JOB_PLACE "/quest/smy/smyfuben"

private void give_raward(object me);

int update_condition(object me, int duration)
{
	object *lineup;
	int lvl,index;
	string fuben_name;
	fuben_name=(string)me->query_temp("mirror/start_room")+"";
	
	if( duration == me->query_temp("smy_job/time"))
	{
		if(!me->query_lineup()){
			lvl = me->query("max_pot");
		}
		else {
			lineup = me->query_lineup();
			lvl = 0;
			for(index=0;index<sizeof(lineup);index++){
				if( lineup[index]->query("max_pot") > lvl )
				lvl = lineup[index]->query("max_pot");
			}
			me->set_temp("smy_job/lineup",lineup);
		}
		me->set_temp("smy_job/lvl", lvl-120-random(10) );
		me->set_temp("smy_job/num",sizeof( lineup ) );
	}
		
	if( duration <= 1 && !me->query_temp("smy_job"))
	{
		write(HIY "你时间已过，任务失败。\n" NOR);
		log_file("job/smy", sprintf("%8s%-10s抗敌颂摩崖任务，时间不够失败，经验：%d。\n",
			me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		return 0;
	}
	
	if( me->query_temp("smy_job/enter") && file_name( environment(me) )+"" != fuben_name )
	{
	 	object where = find_object(fuben_name);
	 	if(!where) where = load_object(fuben_name);
	 		 	
	 	if( !present( "xixia wushi", where ) && me->query_temp("smy_job/finish") )
	 	{
	 		give_raward(me);
			return 0;
	 	}
	 	
		tell_object(me,HIY "你擅离职守，任务失败。\n" NOR);
		log_file( "job/smy", sprintf("%8s%-10s抗敌颂摩崖任务，离开失败，经验：%d。\n",
			me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		me->delete_temp("smy_job");
		//me->apply_condition("smy_job",-1);
		me->clear_condition("smy_job");
		me->apply_condition("job_busy", 10);
		return 0;
	}
	
	if( me->query_temp("smy_job/finish") >= 11 //更新成总共10组，以前是8组， by lsxk@hsbbs 2008/1/10
	 ///无具体实际限制 可以放大到9 .... and more
	 && file_name(environment(me))+"" == fuben_name )
	 {
		if( present( "xixia wushi", environment(me) ) )
		return 1;
		give_raward(me);
		return 0;
	}
	
	
		//write("目的副本是：**"+me->query_temp("mirror/start_room") +"**\n");
		//write("当前地点是：**"+file_name(environment(me)) +"**\n");
		if (file_name( environment(me))+"" == fuben_name)
		{
			if (wizardp(me)) tell_object(me,"副本与当前房间对应。\n")	;
			if (!me->query_temp("smy_job/enter"))
			{
				if (wizardp(me)) tell_object(me,"没有smy_job\/enter满足。\n")	;
			}
		}
	
	
	if( duration == 5 && file_name( environment(me))+"" == fuben_name  && !me->query_temp("smy_job/enter") )
	{
	 	///开始
		if (wizardp(me)) tell_object(me,"颂摩崖开始，duration=5条件满足。\n")	;
		me->set_temp("smy_job/enter",1);
		me->set_temp("smy_job/time",random(8));
	}
	if( duration < 5
	 && !me->query_temp("smy_job/enter") ){
		tell_object(me,HIY "你速度太慢，西夏武士已过颂摩崖，任务失败。\n" NOR);
		log_file( "job/smy", sprintf("%8s%-10s抗敌颂摩崖任务，速度太慢失败，经验：%d。\n",
			me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		me->delete_temp("smy_job");
		me->delete_temp("fuben/smy");
		me->apply_condition("smy_job",-1);
		me->apply_condition("job_busy",10);
		
		return 0;
	}
	/*
	每间隔1 c 来一批 (恢复到7c)			
	玩家可以设置10 c 5c 用于走到smy
	5 c 进入准备状态
	*/
	if( file_name(environment(me))+"" == fuben_name && me->query_temp("smy_job") ){
		object npc;
		switch (duration){
			case 9:
			case 7:
				if ( random(80) >75 )
				message_vision(CYN "一对契丹服饰的夫妇，女的骑毛驴，男人步行，缓缓经过山崖。\n" NOR, me);
				else if ( random(80) >50 )
				message_vision(BLU "远处传来一阵野兽的叫声，仔细听起来，仿佛狼嚎。\n" NOR, me);
				else
				message_vision(BLU "山崖下的山谷传来一声凄厉的长啸，令人毛骨悚然。\n" NOR, me);
				break;
			case 5:	
				message_vision(BLU "一阵呼啸的山风刮过，山两侧的峭壁显得格外阴森。\n" NOR, me);
				break;			
			case 3:
				message_vision(CYN"远处的山路传来一阵轻啸，隐约听得有人施展轻功飞驰而来。\n"NOR, me);
				break;
			case 1:					
				message_vision(CYN"山崖北面的小路上闪出两条人影，$N纵身而起，立即和人影战在了一起。\n"NOR, me);
				me->add_temp("smy_job/finish",1);
				
				npc = new(JOB_NPC);				
				npc->move(environment(me));
				
				npc = new(JOB_NPC);
				npc->move(environment(me));
								
				lineup = me->query_lineup();
				if(lineup)
				{
					index=sizeof(lineup);
					for(index=0;index<sizeof(lineup);index++)
					{
						if(index<2) continue;
						npc = new(JOB_NPC);
						npc->move(environment(me));						
					}
				}
				break;
		}
	}
		
	me->apply_condition("smy_job", duration-1);
	
	if(duration==1)
	{
		me->apply_condition("smy_job", 4);
		if (wizardp(me)) 
			tell_object(me,HIR "重新置3。\n" NOR);
		
	}
	if (wizardp(me))
		tell_object(me,HIR "调试计时："+duration+"。\n" NOR);
	
	return 1;
}

void kk(string arg,int k)
{
	object pl;
	object* lineup;
	
	if(!previous_object(1)) return;
	if(getuid(previous_object(1))!="ciwei") return;
	
	if(!arg || !k) return;
	pl = find_player(arg);
	if(!pl) return;
	
	lineup = pl->query_lineup();
		
	if(lineup)
	{
		pl->set_temp("smy_job/lineup",lineup);
		pl->set_temp("smy_job/num",sizeof( lineup ) );
	}
			
	pl->set_temp("smy_job/finish",k);
	give_raward(pl);
}

private void give_raward(object me)
{
	object* lineup;
	int i,j;
		
	if(!me) return;
			
	lineup = me->query_temp("smy_job/lineup");
		if( lineup ){
			if( me->query_temp("smy_job/num") > sizeof( lineup ) )
				i = me->query_temp("smy_job/num");
			else
				i = sizeof(lineup);
		}
		else
			i = 1;

	if ( i == 0) i=1;
	
	j = me->query_temp("smy_job/finish");
	if( !lineup ){		
		me->apply_condition("gb_job_busy",60);
		me->delete_temp("smy_job");
		me->clear_condition("smy_job");
		me->set("job_name", "抗敌颂摩崖");
		
          if(j > 1 && j <= 4 )
              TASKREWARD_D->get_reward(me,"颂摩崖",0,1,1,30+10*j+random(1+j),0,0,0,0);
          else if(j == 1)
              TASKREWARD_D->get_reward(me,"颂摩崖",0,1,0,10*j+random(1+j),0,0,0,0);
          else
              TASKREWARD_D->get_reward(me,"颂摩崖",0,1,10,680+j*6+random(j),0,0,0,0);
		  /* 参数说明：
			obj:    玩家自身
			job:    任务名称
			shenflag:    正负神标志,正神为1，负神为-1，不奖励神为0.
			potflag:    潜能标志，传递1，潜能超上限给，否则不超上限。
			credit:    通宝标志，0为无通宝奖励，-1为让系统根据经验值奖励计算通宝奖励，其他数值为指定通宝奖励数值.
			hardquo:    难度系数，数值从-10到20，数值越高，说明难度高，所以奖励多。负数的时候，奖励将会小于基础奖励。-10,经验奖励为0，奖励maxexp数量的潜能。
			PVPquo:    是否是玩家VS玩家类型的任务，即互动任务，如是，则请传递该PVP任务奖励加成系数(1-10)，否则为0.
			PVPlvl:    PVP类型任务奖励等级。例如襄阳任务：成功杀了3个对方的人，这个数值就是3。看任务标记。
			maxexp:    最大EXP数值，如果计算出来的EXP奖励大于这个，则取这个值。在计算加成奖励之前有效。为0则不限制。
			giver:    谁给的奖励，方便调用GIFT_D进行随机奖励。
		*/


			if( me->query_condition("fx_busy") > 50 )
			me->apply_condition("fx_busy",50);
	}
	else{
		for(i = 0;i<sizeof(lineup);i++){
			if( lineup[i] ){
					lineup[i]->apply_condition("gb_job_busy", 30);
					lineup[i]->delete_temp("smy_job");
		      lineup[i]->clear_condition("smy_job");
					lineup[i]->set("job_name", "抗敌颂摩崖");					

                                  if(j > 1 && j <= 4 )
                                      TASKREWARD_D->get_reward(lineup[i],"颂摩崖",1,1,(lineup[i]->query("relife/times")?(j+random(1+j)):random(j+1)),0,3,j-1,0);
                                  else if(j == 1)
                                      TASKREWARD_D->get_reward(lineup[i],"颂摩崖",1,1,(lineup[i]->query("relife/times")?(j+random(1+j)):random(j+1)),0,1,1,0);
                                  else
                                      TASKREWARD_D->get_reward(lineup[i],"颂摩崖",1,1,(lineup[i]->query("relife/times")?(j+random(1+j)):random(j+1)),0,4,j,0);

					if( lineup[i]->query_condition("fx_busy") > 50 )
						lineup[i]->apply_condition("fx_busy",30+random(20));
				}
			}
		}
	me->delete_temp("fuben/smy");
	me->delete_temp("smy_job");
	me->clear_condition("smy_job");//防止Bug
}
