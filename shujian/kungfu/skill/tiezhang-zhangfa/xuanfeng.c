// by darken@SJ

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

string perform_name(){ return HBBLU"旋风快掌"NOR; }
int perform(object me, object target)
{
        int skill;
        skill = (int)me->query_skill("tiezhang-zhangfa", 1);
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「旋风快掌」只能在战斗中使用。\n");
        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「旋风快掌」！\n");   
        if( skill < 100 )
                return notify_fail("你的铁掌掌法不够娴熟，使不出「旋风快掌」。\n");
        if(me->query_skill("guiyuan-tunafa",1) < 100 )
                return notify_fail("你的归元吐呐法不够娴熟，使不出「旋风快掌」。\n");
        if(me->query_skill_mapped("strike") != "tiezhang-zhangfa" )
               return notify_fail("你现在无法使用「旋风快掌」！\n");
        if( (int)me->query("max_neili") < 500)
                return notify_fail("你现在内力太弱，使不出「旋风快掌」。\n");      
        if( (int)me->query("neili") < 300 )
                return notify_fail("你现在真气太弱，使不出「旋风快掌」。\n");
      
        message_vision(HBBLU"\n$N一提气，一声长啸，双掌猛往$n左右双肩拍去！\n"NOR,me,target);
        me->add("neili", -100);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if(me->is_fighting(target)) 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        me->start_perform(2,"「旋风快掌」");
        return 1;
}

