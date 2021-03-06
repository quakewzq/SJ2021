// qixingplus.c for murong-jianfa
// by keinxin@SJ2 2003.2
// 七剑转七星

#include <ansi.h>

inherit F_SSERVER;
int perform(object me,object target)
{
    object weapon;
    int i=me->query_skill("murong-jianfa",1);
    int d=me->query_skill("shenyuan-gong",1);
    
    if( !target ) target = offensive_target(me);
     
    if( !target || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("七剑转七星只能对战斗中的对手使用。\n");

    /*if((int)me->query("qixingquest")<1)
                return notify_fail("你还没有领悟剑转七星的真正要决！\n");
	*/
    
    if( (int)me->query_skill("shenyuan-gong", 1) < 100 )
                return notify_fail("你的神元功火候不到，不能使用七剑转七星！\n");
    if( (int)me->query_skill("murong-jianfa", 1) < 100 )
                return notify_fail("你的慕容剑法还没有精进，不能使用七剑转七星！\n");
    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "murong-jianfa")
                return notify_fail("你手里没有剑，无法使用七剑转七星！\n");
    
    if(me->query_temp("qixing_1") > 0)
                return notify_fail("你刚使用过七剑转七星！\n");
                
    if((int)me->query("max_neili") < 1000 )
                return notify_fail("你的内力修为不够，不能使用七剑转七星！\n");
    if((int)me->query("neili") < 500 )
                return notify_fail("你现在真气不足，不能使用七剑转七星！\n");
    if((int)me->query("jingli") < 300 )
                return notify_fail("你现在精力不足，不能使用七剑转七星！\n");

    if((int)me->query_skill("sword", 1) < 100 )
                return notify_fail("你的基本剑法不够娴熟，不能在剑招中使用七剑转七星。\n");
                
    message_vision(HIB"\n$N忽然剑锋再转，只见七朵"+HIG+"剑花"+HIB+"依次绽开，分别袭向$n的七大要穴！\n"NOR,me,target);
    me->receive_damage("neili", 50);
    me->receive_damage("jingli", 50);
    me->add_temp("apply/attack", i/2);
    me->add_temp("apply/damage", i/3);    
    me->add_temp("apply/dodge", d/2);
    me->add_temp("qixing1",1);
    me->add_temp("qixing_1",1);

    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
me->delete_temp("qixing1");
me->add_temp("qixing2",1);


    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
 
me->delete_temp("qixing2");
me->add_temp("qixing3",1);   


    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

me->delete_temp("qixing3");
me->add_temp("qixing4",1);    


    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
  
me->delete_temp("qixing4");
me->add_temp("qixing5",1);    

  
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
 
me->delete_temp("qixing5");
me->add_temp("qixing6",1);
  
 
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
  
me->delete_temp("qixing6");
me->add_temp("qixing7",1);              


    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
    me->add_temp("apply/attack", -i/2);
    me->add_temp("apply/damage", -i/3);        
    me->add_temp("apply/dodge", -d/2);  

me->delete_temp("qixing7");         
    message_vision(WHT"\n$N祭完七星，收剑挺立场中，一代王者风范凛然而出！仿佛毫不在意$n的存在。\n"NOR,me,target); 
    call_out("check_xu", 30, me);
me->start_busy(3);    
    return 1;
}


int check_xu(object me)
{    
       me->delete_temp("qixing_1");     //判断动作
}     
