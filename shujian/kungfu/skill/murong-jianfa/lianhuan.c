// lianhuan.c for murong-jianfa
// by snowman@SJ 01/05/1999.
// modify by leontt@SJ 26/09/2000.

#include <ansi.h>

inherit F_SSERVER;
int perform(object me,object target)
{
	object weapon;
	int d=me->query_skill("murong-jianfa",1) /3+ me->query_skill("douzhuan-xingyi",1) /3 + me->query_skill("canhe-zhi",1) /3;
	int i=me->query_skill("shenyuan-gong",1)/2 + me->query_skill("murong-shenfa",1) /2;
         
 if(!userp(me)){ 
             i = i /4; 
             d= d /4;}

	if( !target ) target = offensive_target(me);

		
	         if( !target  
        || !me->is_fighting(target)
        || !objectp(target)
        || environment(target)!= environment(me))
		return notify_fail("七剑连环指只能对战斗中的对手使用。\n");

		
		

	

	if( (int)me->query_skill("shenyuan-gong", 1) < 100 )
		return notify_fail("你的内功还未练成，不能使用七剑连环指！\n");

	if( (int)me->query_skill("murong-jianfa", 1) < 100 )
		return notify_fail("你的剑法还未练成，不能使用七剑连环指！\n");

	if(!objectp(weapon = me->query_temp("weapon"))
	|| weapon->query("skill_type") != "sword"
	|| me->query_skill_mapped("sword") != "murong-jianfa")
		return notify_fail("你手里没有剑，无法使用七剑连环指！\n");

        
	if( (int)me->query_skill("canhe-zhi", 1) < 100 )
		return notify_fail("你的参合指还未练成，不能使用七剑连环指！\n");
	if((int)me->query("max_neili") < 1000 )
		return notify_fail("你的内力修为不够，不能使用七剑连环指！\n");
	if((int)me->query("neili") < 800 )
		return notify_fail("你现在真气不足，不能使用七剑连环指！\n");
	if((int)me->query("jingli") < 500 )
		return notify_fail("你现在精力不足，不能使用七剑连环指！\n");
	if((int)me->query_temp("lianhuan"))
		return notify_fail("你正在使用七剑连环指！\n");
	if(me->query_skill_mapped("finger") != "canhe-zhi"
	 || me->query_skill_prepared("finger") != "canhe-zhi")
		return notify_fail("你没有用指，无法使用七剑连环指！\n");
	if((int)me->query_skill("sword", 1) < 100 )
		return notify_fail("你的基本剑法不够娴熟，不能在剑招中使用七剑连环指。\n");

	message_vision(MAG"\n$N"MAG"使出慕容剑法之精髓「七剑连环指」，但见$P右手食指在"+weapon->name()+MAG"上一弹，画剑花朵朵相辉相映，直袭$n"MAG"！\n"NOR, me,target);
	me->set_temp("lianhuan", 7);
	me->receive_damage("neili", 100);
	me->receive_damage("jingli", 100);
if(me->query_skill("murong-jianfa",1) >=450 && !userp(target))
 target->add_busy(2+random(2));
              me->add_temp("apply/attack", i /2);
	me->add_temp("apply/damage", d /3 );
	me->add_temp("apply/sword",d/4);
	me->add_temp("apply/finger",d/4);
	me->add_temp("apply/strength",d/10);
              me->add_temp("apply/dodge", i /3);


	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if( me->is_fighting(target))
        {
            weapon->unequip(); 
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
            weapon->wield(); 
        }
    if(me->is_fighting(target))
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        
    if( me->is_fighting(target) && random((int)me->query_str()) > 30)
        {
            weapon->unequip(); 
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
            weapon->wield(); 
        }

	me->start_perform(3, "「七剑连环指」");
	call_out("check_fight", 1, me, 4, i, d);
	return 1;
}

void remove_effect2(object me, int i)
{
	if (me)   me->add_temp("apply/dodge",- i /3);
                          
}

void remove_effect(object me, int i, int d)
{
	if(!me) return;

	me->delete_temp("lianhuan");
  
              me->add_temp("apply/attack",- i /2);
	me->add_temp("apply/damage", -d /3 );
	me->add_temp("apply/sword",-d/4);
	me->add_temp("apply/finger",-d/4);
	me->add_temp("apply/strength",-d/10);

	if (living(me))
		message_vision(HIY"\n$N"HIY"的「七剑连环指」绝技运行完毕，气回丹田，缓缓收功。\n"NOR, me);
	me->start_perform(2, "「七剑连环指」");
	d = 1 + random(2);
if(me->query_skill("murong-jianfa",1) <=350 )
        me->add_busy(d);
	call_out("remove_effect2", d+d, me, i);
}

void check_fight(object me, int i, int j, int d)
{
	object weapon, target;

	if (!me ) return;

	target = offensive_target(me);

	if(!i
	|| !living(me)
	|| !target
	|| !me->is_fighting(target)
	|| environment(target)!=environment(me)
	|| !me->query_temp("lianhuan")
	|| me->query("neili") < 200
	|| me->query("jingli") < 200)
		return remove_effect(me, j, d);

	if(me->query_skill_mapped("sword") != "murong-jianfa") {
		tell_object(me, HIR"你临时改换剑法，决定不再使用「七剑连环指」绝技。\n");
		remove_effect(me, j, d);
	} else if(!objectp(weapon = me->query_temp("weapon"))
		|| weapon->query("skill_type") != "sword"){
		tell_object(me, HIR"你临时改换武器，决定不再使用「七剑连环指」绝技。\n");
		remove_effect(me, j, d);
	} else if (me->is_busy())
		call_out("check_fight", 1, me, i, j, d);
	else {
		me->receive_damage("neili", 50);
		me->receive_damage("jingli", 50);
		if (objectp(target) && me->is_fighting(target))
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		call_out("check_fight", 1, me, --i, j, d);
	}
}

string perform_name(){ return MAG"七剑连环指"NOR; }
int help(object me)

{
        write(HIG"\n慕容剑法之「七剑连环指」："NOR"\n\n");
        write(@HELP
        要求：  当前内力 800 以上；
                最大内力 1000 以上；
                当前精力 500 以上；
                慕容剑法等级 100 以上；
                神元功等级 100 以上；
                基本剑法等级 100 以上；
                激发剑法为慕容剑法；
                激发招架为慕容剑法、斗转星移或参合指；
                激发内功为神元功。
HELP
        );
        return 1;
}
