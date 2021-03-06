// qunmo.c  群魔乱舞

#include <ansi.h>

inherit F_SSERVER;

int perform(object me,object target)
{
//          object weapon = me->query_temp("weapon");
        int attack, defense;
        
        if (!target) target = offensive_target(me);
        if (!target || !me->is_fighting(target))
                return notify_fail("只能对战斗中的对手使用『群魔乱舞』。\n");                

        if (me->query_skill("kongming-quan", 1) < 70)
                return notify_fail("你的空明拳尚不纯熟还是不要乱用『群魔乱舞』。\n");        
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用『群魔乱舞』！\n");  
        if (me->query("neili") < 100)
                return notify_fail("你现在内力不足，不能使用拼命打法！\n");
        if (me->query_temp("kongming_berserk"))
                return notify_fail("你目前正在使用『群魔乱舞』！\n");      
        message_vision(HIR"\n$N突然如痴如狂，挥舞着双臂，四周笼罩着拳风。\n"NOR, me);
        me->add("neili", -80); 
        me->add("jingli", -30);      
        me->set_temp("kongming_berserk", me->query_skill("kongming-quan", 1) / 10);
        attack = me->query_temp("apply/attack");
        defense = me->query_temp("apply/defense") / 2;
        me->add_temp("apply/attack", attack);
        me->add_temp("apply/defense", -defense);
        call_out("remove_effect", 1, me, target, attack, defense);
        return 1;
}

void remove_effect(object me, object target, int attack, int defense)
{
        if (objectp(me)) {
                if (objectp(target) && me->query_temp("kongming_berserk") && me->is_fighting(target)) {
                        me->add_temp("kongming_berserk", -1);
                        call_out("remove_effect", 1, me, target, attack, defense);
                        return;
                }
                me->add_temp("apply/attack", - attack);
                me->add_temp("apply/defense", defense);
                me->delete_temp("kongming_berserk");
                tell_object(me, "你发狂般地乱打了一阵后，决定先歇一歇。\n");
        }
}

