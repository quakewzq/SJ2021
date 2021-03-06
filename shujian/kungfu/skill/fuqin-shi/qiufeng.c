// qiufeng.c 秋风抚琴式
// Created by snowman@SJ 08/03/2001

#include <ansi.h>

inherit F_SSERVER;

int is_pfm() { return 1;}

#define PFM_NAME 	"秋风抚琴式"

string perform_name(){ return YEL+PFM_NAME+NOR; }

int perform(object me, object target)
{
      	if( !target ) target = offensive_target(me);
     
      	if( !target 
      	|| !me->is_fighting(target) 
      	|| !living(target)
      	|| environment(target) != environment(me) )
      		return notify_fail("「"PFM_NAME + "」只能在战斗中对对手使用。\n");      

	if( target->is_busy() )
      		return notify_fail("对方已经自顾不暇了，不必使用「" + PFM_NAME + "」吧？\n");
      		
      	if( (int)me->query_skill("fuqin-shi",1) < 100 )
      		return notify_fail("你的抚琴式不够娴熟，不能使用「" + PFM_NAME + "」！\n");
      
      	if( (int)me->query_skill("whip",1) < 100 )
      		return notify_fail("你的基本鞭法等级不够，不能使用「" + PFM_NAME + "」！\n");  
      
      	if( (int)me->query_skill("sancheng-gong", 1) < 80 )
      		return notify_fail("你的三乘功法等级不够，不能使用「" + PFM_NAME + "」！\n");

      	if( (int)me->query("max_neili") < 800 )
      		return notify_fail("你的内力太弱，不能使用「" + PFM_NAME + "」！\n");
      
      	if( (int)me->query("neili") < 300 )
      		return notify_fail("你的内力太少了，无法使用出「" + PFM_NAME + "」！\n");   
                                                                                 
      	if( me->query_skill_mapped("force") != "sancheng-gong")
      		return notify_fail("你现在的内功无法支持使用「" + PFM_NAME + "」进行攻击。\n");

	return (int)call_other( this_object(), "main", me, target);
}

int main(object me, object target)
{
	object weapon;
	string msg, dodge_skill;
	int ap, dp;
	
	if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) || !living(target) 
        || me->query("neili") < 400 || me->query("jingli") < 100 
        || environment(target) != environment(me) )
                return notify_fail("你目前无法使用「" + PFM_NAME + "！\n");   
                
        weapon = me->query_temp("weapon");
        if (!weapon || weapon->query("skill_type") != "whip"
       	|| me->query_skill_mapped("whip") != "fuqin-shi")
      		return notify_fail("你手里没有鞭，无法使用「" + PFM_NAME + "」！\n");   
      		
      	msg = YEL"\n但见秋风吹拂着峰峦，摇撼着丛林，发出声声呼啸，片片橙红的"RED"枫叶"YEL"在空中飞舞，流水、秋风、树涛相互应和着……\n\n"HIC
      	"$N迎风而立，提腕抖鞭，"+weapon->name()+HIC"飞串而出，迎着金风而入，「" + PFM_NAME + "」仿佛为飘飘红叶伴舞，直袭$n！\n"NOR;
      	
      	me->add("neili", -(200+random(100))); 
      	me->add("jingli", -50);
      	ap = me->query("combat_exp")/1000 * me->query_skill("fuqin-shi",1) * me->query_int();
       	dp = target->query("combat_exp")/1000 * target->query_skill("dodge",1) * target->query_int();
       	if (ap < 1) ap = 1;
       	if (dp < 1) dp = 1;
       	if( me->query_temp("pfm/qiushui") )
		ap += ap/2;
		
        if( random(ap + dp) > dp ){
        	target->start_busy(me->query_int()/8);
        	msg += YEL"结果$n一不留神，被卷进了这鞭影中，顿时招法错乱！\n"NOR;
        }
       	else{
                me->start_busy(1+random(2));
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
       	}
       	
        message_vision(msg, me,target);
        me->start_busy(1);
      	me->start_perform(4 , PFM_NAME);
      	return 1;
}

int help(object me)
{
	return (int)call_other(__DIR__"qiushui", "help", me);
}
