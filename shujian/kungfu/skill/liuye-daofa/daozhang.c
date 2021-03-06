// by darken@SJ

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
                return notify_fail("一刀夹双掌只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("liuye-daofa", 1) < 100 )
                return notify_fail("你的柳叶刀法功力太浅，无法使用一刀夹双掌攻击。\n");

        if( (int)me->query_skill("tiezhang-zhangfa", 1) < 100 )
                return notify_fail("你的铁掌掌法功力太浅，无法使用一刀夹双掌攻击。\n");

        if( (int)me->query("max_neili") < 1000 )
                return notify_fail("你的内力太浅，无法使用一刀夹双掌攻击。\n");

        if( (int)me->query("neili") < 400 )
                return notify_fail("你的真气不足，无法使用一刀夹双掌攻击。\n");

        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "blade"
            || me->query_skill_mapped("blade") != "liuye-daofa" || 
               me->query_skill_prepared("strike") != "tiezhang-zhangfa")
                return notify_fail("你的准备功夫不对。\n");

        me->add("neili", -200);
        me->add("jingli", -40);
        message_vision(BLU"$N呼呼呼连环三招，刀风中夹着两招铁掌掌法，迅速向$n砍去！\n" NOR,me,target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
        weapon->unequip();
        if(me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        if(me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        weapon->wield();
        me->start_perform(4,"一刀挟双掌");
        me->start_busy(1);
        return 1;
}

string perform_name(){ return BLU"掌刀"NOR; }