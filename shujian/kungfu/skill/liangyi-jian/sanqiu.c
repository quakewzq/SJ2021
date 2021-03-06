// sanqiu.c (昆仑掌法) 两仪剑 perform 一日三秋
// cck 13/6/97

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        string msg;
        string msg1;


        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「一日三秋」只能在战斗中对对手使用。\n");

        if (!objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if( (int)me->query_skill("liangyi-jian", 1) < 90 )
                return notify_fail("你的两仪剑法不够娴熟，不会使用「一日三秋」。\n");

        if( (int)me->query_skill("xuantian-wuji", 1) < 60 )
                return notify_fail("你的玄天无极功等级不够，不能使用「一日三秋」。\n");

if( (int)me->query_str() < 20 )
                return notify_fail("你的膂力不够强，不能使用「一日三秋」。\n");

        if( (int)me->query("neili", 1) < 150 )
                return notify_fail("你现在内力太弱，不能使用「一日三秋」。\n");
                
        me->start_perform(1+random(3),"「一日三秋」");        

        msg = BBLU+HIC "$N突然欺身而进，以迅雷不及掩耳之势奋力向$n连续击出三剑。\n" NOR;
        msg1 = BBLU+HIY "$N长啸一声，剑锋回指。\n" NOR;

        message_vision(msg, me, target);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK);

        me->add("neili", -150);

        message_vision(msg1, me, target);

        return 1;
}
