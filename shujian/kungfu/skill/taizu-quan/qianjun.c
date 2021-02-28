// huashan_shengsi.c

// yingshe-shengsibo perform 鹰蛇生死搏 

//by daidai 2005-10-07



#include <ansi.h>

#include <combat.h>



inherit F_SSERVER;



void remove_effect(object me);



string perform_name(){ return HIC"横扫千军"NOR; }



int perform(object me, object target)

{


    int exp,exp1,busy,lvl,lvl1;
	int attack,level,i;
	object* env;

      if( !target ) target = offensive_target(me);

     

      if( !target || !me->is_fighting(target) )

      return notify_fail("「横扫千军」只能在战斗中对对手使用。\n");

         

      if( objectp(me->query_temp("weapon")) )

      return notify_fail("你必须空手使用「横扫千军」！\n");

      

      if( (int)me->query_skill("taizu-quan",1) < 100 )

      return notify_fail("你的太祖拳不够娴熟，不会使用「横扫千军」！\n");
      

      if( (int)me->query_str() < 20 )

      return notify_fail("你的臂力不够强，不能使用「横扫千军」！\n");

      

      if( (int)me->query("max_neili") < 1000 )

      return notify_fail("你的内力太弱，不能使用「横扫千军」！\n");

      

      if( (int)me->query("neili") < 350 )

      return notify_fail("你的内力太少了，无法使用出「横扫千军」！\n");   

                                         

      if (me->query_skill_prepared("cuff") != "taizu-quan"

       && me->query_skill_prepared("parry") != "taizu-quan")

      return notify_fail("你现在无法使用「横扫千军」进行攻击。\n");                                         

      if( me->query_temp("taizu_hengsao"))

      return notify_fail("你正在使用太祖拳的特殊攻击「横扫千军」！\n");

    //if (target->is_busy()) return notify_fail("对方正自顾不暇，放胆攻击吧！\n");
    env = environment(me)?filter_array(all_inventory(environment(me)),(:$1->query("env/combat")=="pfm":)):0;

      message_vision( HIC"\n$N突然扑向$n，贴身疾攻，使出"+HIY+"太祖拳"+HIC+"在军中留传多年的绝技——『横扫千军』！
只见$N双拳起如风，击如电，前手领，后手追，两手互换一气摧。\n" NOR, me, target);
 // message_vision(msg, me, target);   

  message_vision( HIR"\n$N劲力发挥于撑、拦、斩、卡、撩、崩、塞中，「囚身似猫，抖身如虎，行似游龙，动如闪电」！\n" NOR, me, target); 
	level=me->query_skill("taizu-quan",1);
	exp=me->query("combat_exp");
    exp1=target->query("combat_exp");
    lvl=me->query_skill("cuff");
    lvl1=target->query_skill("dodge");
    if( random(exp/100*lvl)>exp1/100*lvl1/4){  

        me->set_temp("taizu_hengsao",1);  
        target->start_busy(2+random(2));
		message("wizard",sprintf( HIW "taizu-quan等级",level),env );
		if( me->query_temp("taizu_hengsao")&&living(target)&&!me->query_temp("taizu_qianjun")&&me->query("neili")>800)
		{    
			attack=level/100;
			
			if(attack>4) attack=4;
			if(attack<=1) attack=1;
			message_vision(HIY"\n紧接着$N默念口诀「审势观察细留神，逢弱直冲入中门，遇强避锋绕步锤 」，手步相连，上下相随，遇隙即攻，见空则扑，连攻"+ chinese_number(attack)+"招。\n"NOR, me,target);
			
			for(i=0;i<attack;i++)
				{
					me->add("neili", -(50+random(50)));
					if(!living(target))
						{
							break;
						}
					me->set_temp("taizu_qianjun",1);
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2+random(2));  
					me->delete_temp("taizu_qianjun");
					
				}
			
			me->delete_temp("taizu_hengsao");
		}

        call_out("remove_effect", 5, me);

      }

      else {

        message_vision( HIG"$n一个倒纵飞出丈外，敏捷地逃出了$N的攻击范围！\n"NOR, me, target);      

    //    message_vision(msg, me, target);                    

        me->start_busy(random(2));

        me->add("neili", - 50);

		me->start_perform(1+random(3),"「横扫千军」");    }

      return 1;

}



void remove_effect(object me)

{

    if (!me) return;
	if ( me->delete_temp("taizu_hengsao"))
	{
		me->delete_temp("taizu_hengsao");

		tell_object(me,MAG"\n你打出这套“横扫千军”之后，身心俱疲，不敢多使，便悄悄地停止了使用。"NOR);
	}
	message_vision(CYN"\n$N一套「横扫千军」使用完毕，长长的吸了口气。\n"NOR, me);

}