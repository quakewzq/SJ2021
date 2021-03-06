// xi.c
// add by keinxin@sj2
// 2003.5

#include <ansi.h>

inherit F_SSERVER;
int exert(object me, object target)
{
	int sp, dp;

	if ( target == me ) target = offensive_target(me);

	if( environment(me)->query("no_fight") )
		return notify_fail("在这里不能攻击他人。\n");

	if( !objectp(target) || target->query("id") == "mu ren" )
		return notify_fail("你要吸取谁的真气？\n");

	if (target->query("race") != "人类")
		return notify_fail("搞错了！只有人才能有真气！\n");

	if ( me->query_temp("sucked") )
		return notify_fail("你刚刚吸取过真气！\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("你必须空手才能施用化功大法吸人真气！\n");

        if( !me->is_fighting() || !target->is_fighting())
                return notify_fail("你必须战斗中吸人真气！\n");

	if( (int)me->query_skill("huagong-dafa",1) < 30 )
		return notify_fail("你的化功大法功力不够，不能吸取对方的真气。\n");

	if( (int)me->query("neili",1) < 10 )
		return notify_fail("你的内力不够，不能使用化功大法。\n");

        if( (int)target->query("qi") < 30 )
		return notify_fail( target->name() +
			"已经真气涣散，你已经无法从他体内吸取真气了！\n");

        if( target->query_temp("no_kill") )
        return notify_fail("不能打，打不得啊！\n");

        if(target==me)
        return notify_fail("用 suicide 指令会比较快:P。\n");

        if(me->is_busy())
        return notify_fail("你现在正忙。\n");
	message_vision(
		HIR "$N突然诡异的一笑，双手一扬，拇指对准$n的掌心按了过来！\n\n" NOR,
		me, target );

	if ( living(target) )
	{

            target->fight_ob(me);

	}

        sp = me->query_skill("force") + me->query_skill("dodge") + me->query_skill("huagong-dafa",1);
        dp = target->query_skill("force") + target->query_skill("dodge");

	me->set_temp("sucked", 1);		

        if (( random(sp) > random(dp)/2 ) || !living(target) )
	{
		tell_object(target, HIR "你突然觉得全身气血自手掌奔涌而出，四肢无力，再也使不出劲来！\n" NOR);
		tell_object(me, HIG "你觉得" + target->name() + "的"HIR"气血"HIG"自手掌源源不绝地流了进来。\n" NOR);

		target->receive_damage("qi", (int)me->query_skill("huagong-dafa", 1)*2 );
		target->receive_wound("qi", (int)me->query_skill("huagong-dafa", 1)/2 );
		me->add("qi", (int)me->query_skill("huagong-dafa", 1)*2 );
		me->add("eff_qi", (int)(me->query_skill("huagong-dafa", 1)/2) );
		if ( me->query("eff_qi") > me->query("max_qi") ) me->set("eff_qi", me->query("max_qi"));
		
		if ( me->query("qi") > me->query("max_qi")*2 ) me->set("qi", me->query("max_qi")*2);

		if( target->query("combat_exp") >= me->query("combat_exp") )
			me->add("qi", (int)me->query_skill("huagong-dafa", 1)*2 );

                target->start_busy(random(3));
		me->add("neili", -5);

		call_out("del_sucked", random(4), me);
	}
	else
	{	
		message_vision(HIY "可是$p看破了$P的企图，内力猛地一震，借势溜了开去。\n" NOR, me, target);
                me->start_busy(2);
		call_out("del_sucked", random(4), me);
	}

	return 1;
}

void del_sucked(object me)
{
	if ( me->query_temp("sucked") )
	me->delete_temp("sucked");
}
