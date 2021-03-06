// luiyun.c 流云水袖
// add by keinxin@sj2
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;

void remove_effect(object me, int aamount, int damount);

int perform(object me, object target)
{
        object weapon;  
        string msg;
        int d_count, count, qi, maxqi, skill, damage;
        
        if( !target ) target = offensive_target(me);

        if(!target||!target->is_character() || !me->is_fighting(target) )
        return notify_fail("流云水袖只能对战斗中的对手使用。\n");        

        if( (int)me->query_temp("liuyun") ) 
                return notify_fail(HIG"你已经在默运流云水袖神功了。\n");

        if( (int)me->query("neili") < 400 )
                return notify_fail("你的内力还不够高！\n");

        if( (int)me->query_skill("xuantian-wuji", 1) < 60)
                return notify_fail("你的玄天无极功的修为不够，不能使用流云水袖! \n");

        if( (int)me->query_skill("strike", 1) < 80 )
                return notify_fail("你的基本掌法还不到家，无法使用流云水袖！\n");

        if( me->query_skill_mapped("strike") != "kunlun-zhang") 
                return notify_fail("你没有激发昆仑掌，无法使用流云水袖！\n");
        
msg = HIR "$N轻喝一声使出昆仑掌中的绝学「流云水袖」，威力陡然增加，衣袖横扫敌人的面门！\n" NOR;
        
        qi = me->query("qi");
        maxqi = me->query("max_qi");
        skill = (int) (me->query_skill("xuantian-wuji",1) / 3);
        count = (int) (me->query_skill("kunlun-zhang",1) / 3);
        
//加gift的一定要按照先天gift的2-3倍来加。keinxin        
        d_count = me->query("dex")*2;
        damage = d_count*10+count+skill;
        damage *= 3;
        if (damage>3000)damage = 3000;

        if(qi > (maxqi/2))
        {       
        message_vision(msg, me, target);


                me->add_temp("apply/dexerity", d_count);
                me->add_temp("apply/damage", count);
                me->set_temp("liuyun", 1);
                me->start_busy(1);     
                me->start_call_out( (: call_other, __FILE__, "remove_effect", me, count*2, d_count :), skill/20);

                me->add("neili", -300);
        return 1;
        }
        else{
                msg = HIR "$N拼尽毕生功力使出了昆仑掌中的终极绝技「流云水袖」， 全身骨骼一阵爆响, 欲与敌人同归于尽!\n" NOR;
                message_vision(msg, me, target);

                me->receive_damage("qi", damage/2);
                me->receive_wound("qi", damage/3);
                
                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/2);
                
                if(random(me->query("combat_exp"))>random(target->query("combat_exp")/2)){                 
                     target->start_busy(random(3));
                     target->receive_damage("qi", damage);
                     target->receive_wound("qi", damage/2);
                }
                
                me->set_temp("last_damage_from", "使用「流云水袖」和"+target->name()+"同归于尽");
                target->set_temp("last_damage_from", "被"+me->name()+"使用「流云水袖」杀");

                me->start_busy(1); 
                

                    
                me->add("neili", -300);

                return 1;


        }
}

void remove_effect(object me, int aamount, int damount)
{
        int d_count, count;
        count = (int) (me->query_skill("kunlun-zhang",1) / 3);
        d_count = (int) (me->query_skill("kunlun-zhang",1) / 5);
        
        if ( (int)me->query_temp("liuyun") ) 
        {

                me->add_temp("apply/dexerity", -d_count);
                me->add_temp("apply/damage", -count);
                me->delete_temp("liuyun");
                tell_object(me, HIY "你的「流云水袖」神功运行完毕，将内力收回丹田。\n" NOR);
                me->start_busy(2);
        }
}

