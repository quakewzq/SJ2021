// qianshou 千手如来
// bren

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
void remove_effect(object target, int skill);
void check_fight(object me,object target,int improve);
int perform(object me, object target)
{
        string msg;
        int skill;
        skill = (int)me->query_skill("qianye-shou", 1);                

       if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「千手如来」只能在战斗中对对手使用。\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("使用「千手如来」时双手必须空着！\n");

        if( (int)me->query_skill("qianye-shou", 1) < 100 )
                return notify_fail("你的如来千叶手不够娴熟，不会使用「千手如来」。\n");

        if( (int)me->query_skill("yijin-jing", 1) < 100 )
                return notify_fail("你的易筋经内功等级不够，不能使用「千手如来」。\n");

        if( (int)me->query_dex() < 27 )
                return notify_fail("你的身法不够强，不能使用「千手如来」。\n");

        if (me->query_skill_prepared("hand") != "qianye-shou"
        || me->query_skill_mapped("hand") != "qianye-shou")
                return notify_fail("你现在无法使用「千手如来」进行攻击。\n");
     
        if( (int)me->query("neili") < 1000 )
                return notify_fail("你现在内力太弱，不能使用「千手如来」。\n");

        if( target->query_temp("qianshou")   )
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。！\n");

// 42          me->start_perform(2,"如来千叶手")
        msg = HIY "$N双手合十互击，陡然向外一分，双掌顿时变得轻灵飘逸，灵动异常，霎时幻起漫天的掌影。\n" NOR;
        message_vision(msg, me, target);
        if (random(me->query("combat_exp")) > target->query("combat_exp")/2){
          msg = HIR "$n只觉得四周都是$N的身影，不由得慌乱起来。\n" NOR;
          message_vision(msg, me, target);
          target->add_temp("apply/attack", -skill/3);
          target->add_temp("apply/dodge", -skill/3);
          target->add_temp("apply/parry", -skill/3); 
          target->set_temp("qianshou",1);   
          me->add("neili", -400);
          me->add("jingli",-150);
          me->start_call_out( (: call_other, this_object(), "check_fight",  me, target, skill :), 1);                             
          return 1;
        }
        message_vision(HIC"$N慌乱中镇定心神，仔细看清了$n的身影。\n"NOR,target,me);
        me->start_busy(2);
        me->add("neili", -100);
        me->add("jingli", -100);
        return 1;
}

void check_fight(object me, object target, int improve) 
{ 
       object weapon;     

       if (!target) return;
       if( !me) {
          remove_effect(target,improve);
       }
       else 
       if(target->query_temp("qianshou") && !me->is_fighting(target)){
          remove_effect(target, improve);
       }
       else if( (target->query_temp("qianshou")) 
        && (!target->is_fighting() 
        || !me->is_fighting() 
        || !living(me) 
        || target->is_ghost() 
        || me->is_ghost() )){
               remove_effect(target, improve);
        }
        else if((target->query_temp("qianshou"))
         && objectp(weapon = me->query_temp("weapon"))){
                remove_effect(target, improve);
        }
        else{
//            target->apply_condition("no_perform",1);
            call_out("check_fight", 1, me, target, improve); 
            return;
        }
}

void remove_effect(object target, int skill)
{
        target->add_temp("apply/attack", skill/3);
        target->add_temp("apply/dodge", skill/3);
        target->add_temp("apply/parry", skill/3);
        target->delete_temp("qianshou");
        tell_object(target, HIB"你渐渐适应了这种变化，状态又恢复如常。\n"NOR);
}

string perform_name(){ return HIY"千手如来"NOR; }