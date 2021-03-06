// baishui.c 白水抚琴式
// Created by snowman@SJ 08/03/2001

#include <ansi.h>

inherit F_SSERVER;

int is_pfm() { return 1;}

#define PFM_NAME 	"白水抚琴式"

string perform_name(){ return HIW+PFM_NAME+NOR; }

int perform(object me, object target)
{
      	if( !target ) target = offensive_target(me);
     
      	if( !target 
      	|| !me->is_fighting(target) 
      	|| !living(target)
      	|| environment(target) != environment(me) )
      		return notify_fail("「"PFM_NAME + "」只能在战斗中对对手使用。\n");      
      		
      	if( (int)me->query_skill("fuqin-shi",1) < 120 )
      		return notify_fail("你的抚琴式不够娴熟，不能使用「" + PFM_NAME + "」！\n");
      
      	if( (int)me->query_skill("whip",1) < 120 )
      		return notify_fail("你的基本鞭法等级不够，不能使用「" + PFM_NAME + "」！\n");  
      
      	if( (int)me->query_skill("sancheng-gong", 1) < 100 )
      		return notify_fail("你的三乘功法等级不够，不能使用「" + PFM_NAME + "」！\n");

      	if( (int)me->query("max_neili") < 1200 )
      		return notify_fail("你的内力太弱，不能使用「" + PFM_NAME + "」！\n");
      
      	if( (int)me->query("neili") < 500 )
      		return notify_fail("你的内力太少了，无法使用出「" + PFM_NAME + "」！\n");   
                                                                                 
      	if( me->query_skill_mapped("force") != "sancheng-gong")
      		return notify_fail("你现在的内功无法支持使用「" + PFM_NAME + "」进行攻击。\n");

	return (int)call_other( this_object(), "main", me, target);
}

int main(object me, object target)
{
	object weapon;
	int ap;
	
	if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) || !living(target) 
        || me->query("neili") < 400 || me->query("jingli") < 100 
        || environment(target) != environment(me) )
                return notify_fail("你目前无法使用「" + PFM_NAME + "」！\n");   
                
        weapon = me->query_temp("weapon");
        if (!weapon || weapon->query("skill_type") != "whip"
       	|| me->query_skill_mapped("whip") != "fuqin-shi")
      		return notify_fail("你手里没有鞭，无法使用「" + PFM_NAME + "」！\n");   
      		
      	message_vision(WHT"\n但见$N静静而立，如风平水静时的白水池，池中有山，山中有云，云中有水，分不清哪里是水，哪里是云；
			此时的$P，神与物游，心随景色而物化……\n\n"NOR, me,target);

      	me->add("neili", -(200+random(100))); 
      	me->add("jingli", -50);
      	ap = me->query_skill("fuqin-shi",1)/40 * me->query_int();
	
	if( me->query_temp("pfm/qiushui") )
		ap += me->query_str() + me->query_dex();
		
	me->set_temp("pfm/baishui", 1);
	me->add_temp("apply/attack", ap);
	me->add_temp("apply/damage", ap/10);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
       	me->add_temp("apply/attack", -ap);
	me->add_temp("apply/damage", -ap/10);
	
        me->start_busy(1);
      	me->start_perform(4 , PFM_NAME);
      	return 1;
}

int help(object me)
{
	return (int)call_other(__DIR__"qiushui", "help", me);
}

