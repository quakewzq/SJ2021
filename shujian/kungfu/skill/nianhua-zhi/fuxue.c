// fuxue.c 拈花指 「拈花拂穴
// by hunthu //99.01.03
#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;
        if( !target ) target = offensive_target(me);

        if( !target
         ||!target->is_character()
         ||!me->is_fighting(target))
           return notify_fail("牵制攻击只能对战斗中的对手使用。\n");

        if((int)me->query_con() < 25)
           return notify_fail("你根骨不够,不能使用这一绝技!\n");

        if((int)me->query_skill("yijin-jing",1) < 120)
           return notify_fail("你易筋经的功力不够不能使用拈花拂穴!\n");

        if((int)me->query_skill("nianhua-zhi",1) < 120)
           return notify_fail("你的指法修为不够,目前还不能使用拈花拂穴绝技!\n");
        if (me->query_skill_prepared("finger") != "nianhua-zhi"
        || me->query_skill_mapped("finger") != "nianhua-zhi" )
                return notify_fail("你必须用拈花指才能出此奇功。 \n");

       

        if((int)me->query("max_neili")<1000)
           return notify_fail("你的内力修为尚欠火候。\n");  

        if((int)me->query("neili") < 300)
           return notify_fail("你内力现在不够, 不能使用拈花拂穴! \n");

        if( target->is_busy() )
           return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧ⅵ\n");
        
        msg = HIY "$N面露慈祥微笑，手指轻轻弹出，似乎在弹落花朵上的朝露，生怕弹损花瓣一般，\n"+
                  "指力若有若无,轻柔之及。一股阴柔的内力罩住了$n的全身要穴, 使$n动弹不得。\n";
        me->start_perform(6,"拂穴");    
        if(random(me->query("combat_exp")) > (int)target->query("combat_exp") / 2 ){
           msg +=  HIG"结果$p被$P拂中要穴! \n" NOR;
           target->start_busy( random((int)me->query_skill("nianhua-zhi",1) / 30 + 2));
           if (random(me->query_skill("nianhua-zhi",1))>=150)
           target->apply_condition("fx_busy", random(me->query_skill("finger")/20) + 1 + target->query_condition("fx_busy"));
           me->add("neili",-300);
           me->add("jingli",-100);
        }
        else {
           msg += HIM"可是$p早有警觉，跳了开去，$P一指落空狼狈的招架着。\n" NOR;
           me->add("neili",-100);
           me->add("jingli",-50);
        me->start_busy(random(2)+2);
        }
        message_vision(msg, me, target);
        return 1;
}
