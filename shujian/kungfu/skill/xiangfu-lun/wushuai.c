// wushuai.c 天人五衰
// Rewrite By lsxk@hsbbs 2007/5/16

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name(){ return HIY"天人五衰"NOR; }

int perform(object me,object target)
{
    object weapon;
    int i,j,lev,jiali;
    
    if( !target ) target = offensive_target(me);
     
    if( !userp(me) && userp(target) )
                return notify_fail("「天人五衰」只能由玩家使用。\n");

    if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("「天人五衰」只能对战斗中的对手使用。\n");

    

    if( (int)me->query_skill("longxiang-boruo", 1) < 150 )
                return notify_fail("你的龙象波若功等级不够，无法使用「天人五衰」！\n");

    if( (int)me->query_skill("xiangfu-lun", 1) < 160 ) 
                return notify_fail("你的金刚降伏轮还未练成，无法使用「天人五衰」！\n");

    if((int)me->query_skill("hammer", 1) < 160 )
                return notify_fail("你的基本锤法不够娴熟，不能使用「天人五衰」！\n");

    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "hammer"
        || me->query_skill_mapped("hammer") != "xiangfu-lun")
                return notify_fail("你必须使用锤法，才能使出「天人五衰」!\n");
                
   if((int)me->query_str() < 40)
           return notify_fail("你的膂力还不够强劲，使不出「天人五衰」绝技。\n");

   

   if((int)me->query("max_neili") < 3000 )
           return notify_fail("你内力修为尚浅，使不出「天人五衰」。\n");  

   if( (int)me->query("neili") < 600 )
           return notify_fail("你现在真气太弱，使不出「天人五衰」。\n");

        message_vision(HIY"\n只听“呜-呜-”之声大作，$N将手中法轮旋转掷出，使出「天人五衰」绝技，奋力掷出！\n"NOR, me,target);

    lev = (int)me->query_skill("xiangfu-lun",1)/4;

    if( me->query_temp("xs/longxiang") ) {
           message_vision(MAG"$N更把龙象内劲附于兵刃之上，"+weapon->query("name")+MAG"通体流淌着异样的紫色光芒！\n\n"NOR, me,target);
           lev *= 2;
           if(!userp(target)) target->start_busy(2);
       }

    me->start_perform(5,"「天人五衰」");
    me->add("neili", -300);
    me->set_temp("xfl/wushuai", 1);
        jiali = ((int)me->query("str",1)/2 + (int)me->query("con",1))/2 + random((int)me->query("jiali")/20 );
        me->add_temp("apply/damage",  lev);
me->add_temp("apply/attack", lev);
        me->add_temp("apply/strength", jiali);
        for (i=0;i<5;i++){
          j = i;
          if (i<1) j = 1;
          if (i>1) j = 3;
          COMBAT_D->do_attack(me, target, me->query_temp("weapon"),j);
          me->add("neili", -200);
          }

        me->add_temp("apply/damage",  -lev);
        me->add_temp("apply/strength", -jiali);
me->add_temp("apply/attack", -lev);

    me->delete_temp("xfl/wushuai");
    target->add_busy(1);
    return 1;
}


