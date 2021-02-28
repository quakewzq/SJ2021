// huashan_shengsi.c

// yingshe-shengsibo perform 鹰蛇生死搏 

//by daidai 2005-10-07



#include <ansi.h>

#include <combat.h>



inherit F_SSERVER;



void remove_effect(object me);



string perform_name(){ return HIC"鹰蛇生死搏"NOR; }



int perform(object me, object target)

{


    int exp,exp1,busy,lvl,lvl1;



      if( !target ) target = offensive_target(me);

     

      if( !target || !me->is_fighting(target) )

      return notify_fail("「鹰蛇生死搏」只能在战斗中对对手使用。\n");

         

      if( objectp(me->query_temp("weapon")) )

      return notify_fail("你必须空手使用「鹰蛇生死搏」！\n");

      

      if( (int)me->query_skill("yingshe-shengsibo",1) < 100 )

      return notify_fail("你的鹰蛇生死搏不够娴熟，不会使用「鹰蛇生死搏」！\n");
      

      if( (int)me->query_str() < 25 )

      return notify_fail("你的臂力不够强，不能使用「鹰蛇生死搏」！\n");

      

      if( (int)me->query("max_neili") < 1000 )

      return notify_fail("你的内力太弱，不能使用「鹰蛇生死搏」！\n");

      

      if( (int)me->query("neili") < 350 )

      return notify_fail("你的内力太少了，无法使用出「鹰蛇生死搏」！\n");   

                                         

      if (me->query_skill_prepared("hand") != "yingshe-shengsibo"

       && me->query_skill_prepared("claw") != "yingshe-shengsibo")

      return notify_fail("你现在无法使用「鹰蛇生死搏」进行攻击。\n");                                         

      if( me->query_temp("huashan_shengsi"))

      return notify_fail("你正在使用鹰蛇生死搏的特殊攻击「鹰蛇生死搏」！\n");



    if (target->is_busy()) return notify_fail("对方正自顾不暇，放胆攻击吧！\n");

       

      message_vision( HIC"\n$N突然扑向$n，贴身疾攻，使出华山派留传百余年的绝技——七十二路“鹰蛇生死搏”！

这鹰蛇双式齐施，苍鹰矫矢之姿，毒蛇灵动之势，于一式中同时现出，迅捷狠辣，兼而有之。\n" NOR, me, target);

      // message_vision(msg, me, target);   

  message_vision( HIR"\n$N左手成鹰爪状，擒、拿、扭、勾，一套鹰抓擒拿手使得出神入化，神乎其技。\n" NOR, me, target);                                    

    exp=me->query("combat_exp");

    exp1=target->query("combat_exp");

    lvl=me->query_skill("claw");

    lvl1=target->query_skill("dodge");

    busy=3;

    busy=busy+random(lvl)/100;

    if(busy>5) busy=5;

            if( random(exp/100*lvl)>exp1/100*lvl1/4){

        message_vision( HIW"$n一不留神被$N抓住关节要害之处，顿时全身麻木，动弹不得。\n"NOR, me, target);

    //    message_vision(msg, me, target); 

if( wizardp(me)) tell_object(me,sprintf("busy=%d\n",busy));

        me->set_temp("huashan_shengsi",1);  

        me->add("neili", -350);    

        target->start_busy(busy);

        me->start_busy(random(2));

        call_out("remove_effect", me->query_skill("yingshe-shengsibo") / 20 + 2, me);

      }

      else {

        message_vision( HIG"$n一个倒纵飞出丈外，敏捷地逃出了$N的攻击范围！\n"NOR, me, target);      

    //    message_vision(msg, me, target);                    

        me->start_busy(2);

        me->add("neili", - 100);

   me->start_perform(4,"「鹰蛇生死搏」");    }

      return 1;

}



void remove_effect(object me)

{

    if (!me) return;

    me->delete_temp("huashan_shengsi");

 tell_object(me,MAG"\n你心知这套“鹰蛇生死搏”破绽颇多，力分而弱，不能多使，便悄悄地停止了使用。"NOR);

    message_vision(CYN"\n$N一套「鹰蛇生死搏」使用完毕，长长的吸了口气。\n"NOR, me);

}