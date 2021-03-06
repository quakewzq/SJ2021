// feixue.c 漫天飞雪 
// add by keinxin@sj2

#include <ansi.h>
#include <combat.h>
#include <weapon.h>

inherit F_SSERVER;

int perform(object me, object target)

{
        string msg;
        int damage, attp, defp;
        object obj;
        string w_name;
        object weapon;

        if( !target ) target = offensive_target(me);

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("开什么玩笑，没装备剑就想使「漫天飞雪」？\n");
        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「漫天飞雪」只能对战斗中的对手使用。\n");
        if ((int)me->query_skill("liangyi-jian", 1) < 60)
                return notify_fail("你的两仪剑法不够娴熟，无法使出两仪剑绝技之一的「漫天飞雪」。\n");
        if ((int)me->query_skill("xuantian-wuji", 1) < 70)
                return notify_fail("你的玄天无极功火侯太浅，无法使出「漫天飞雪」。\n"); 
        if ((int)me->query("neili",1) < 500)
                return notify_fail("你的内力不够，无法使出两仪剑中「漫天飞雪」的绝技。\n"); 


         message_vision( BBLU+HIW "$N聚气于剑，准备施展「漫天飞雪」绝技。\n"NOR, me, target );                

        me->start_perform(3+random(3),"「漫天飞雪」");                      
      
        //奖励攻击
        if( (int)me->query_skill("art", 1) > 180 ) {
              msg = HIC"$n看到剑光偏左，疾侧身右转，但只这一刹，$N的剑光刹时袭向右首！"NOR;
              COMBAT_D->do_attack(me,target, me->query_temp("weapon"),1,msg);
              msg = HIG"$n看到剑光偏右，疾侧身左转，但只这一刹，$N的剑光刹时袭向左首！"NOR;
              COMBAT_D->do_attack(me,target, me->query_temp("weapon"),1,msg);
        }
        
         message_vision( HIW "$N大喝一声，默运内力，只听“铮”的一声，天地为之一窒，但见银光点点，$N手中\n"
         + "长剑竟化为无数粹片，如漫天飞雪般向$n激射而出！\n\n"NOR, me, target );
      
        attp = me->query_skill("xuantian-wuji",1) + me->query_skill("liangyi-jian",1);

        defp = target->query_skill("dodge");

        if( random( attp ) > random( defp )/2 || target->is_busy()){
        
                message_vision( RED "$n躲闪不及，已经被飞散的碎片击中，全身血肉模糊！\n\n"NOR, me, target );
        
                damage = me->query_skill("liangyi-jian",1) + (int)me->query_skill("xuantian-wuji", 1)*2;
                damage = damage - random( target->query_skill("dodge")/3 );
                damage *= 2;
                if (damage>2500) damage = 2500;
                
                target->receive_wound("jing", random( damage/2 ));
                target->receive_damage("qi", 20 + random(damage));
                target->receive_wound("qi", 20 + damage);
                target->start_busy(3 + random(4));
                
                
                //追加攻击
                if( random( attp ) > random( defp ) || target->is_busy()) {
 
          message_vision( BBLU+HIW "$N将玄天无极发挥到及至，"HIG"五韵七弦"BBLU+HIW"剑真气激射而出，此时手中无剑亦有剑！\n\n"
         + NOR + RED"$n惨叫一声，身上已经被无形剑气穿透！\n"NOR, me, target );
 
                        damage *= 2;
                        target->receive_wound("jing", random( damage/2 ));
                        target->receive_damage("qi", 20 + random(damage));
                        target->receive_wound("qi", 20 + damage);
                        target->start_busy(2 + random(8));
                        }
            

        }

        else {

                message_vision( HIY "$p不慌不忙地晃动身形，瞬时间躲过了剑雨。\n" NOR, me, target );

        }

        me->add("neili", -300);
        
        weapon->move(environment(me));
        weapon->set("name", "断掉的"+weapon->query("name"));
        weapon->set("id", "cliped "+weapon->query("id"));
        weapon->unequip();
        weapon->set("value", 0);
        weapon->set("weapon_prop", 0);
        return 1;

}



