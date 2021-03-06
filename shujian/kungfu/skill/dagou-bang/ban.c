// ban.c 打狗棒法--绊字诀
// Creat by Looklove@SJ 3/16/2001
// modified by Looklove 2001.5.10
// Modified by Lane@SJ 2005.7.29

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HBBLU"绊字诀"NOR; }
int perform(object me, object target)
{
	string msg;
	object tweapon, weapon;
	int ap ,dp ,p, n;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("「绊字诀」只能对战斗中的对手使用。\n");

	weapon = me->query_temp("weapon");

	if( !weapon
	 || weapon->query("skill_type") != "stick"
	 || me->query_skill_mapped("stick") != "dagou-bang" 
	 //|| me->query_skill_mapped("parry") != "dagou-bang" 
	 )
		return notify_fail("你现在无法使用「绊字诀」。\n");

	ap = me->query("combat_exp");
	dp = target->query("combat_exp");

	tweapon = target->query_temp("weapon");

	if( me->query_skill("dagou-bang", 1) < 140 )
		return notify_fail("你的打狗棒法还不够娴熟，不会使用「绊字诀」。\n");

	if( me->query_skill("bangjue",1) < 140 )
		return notify_fail("你的打狗棒诀不够娴熟，无法使出「绊字诀」。\n");

	if( (int)me->query_skill("huntian-qigong",1) < 140 )
		return notify_fail("你的混天气功根基不足，无法使出「绊字诀」。\n");

	if( (int)me->query("neili") < 600 )
		return notify_fail("你的内力不够，无法使出「绊字诀」。\n");

	if( (int)me->query("jingli") < 400 )
		return notify_fail("你的精力不足以让你使出「绊字诀」。\n");

	if( (int)me->query("max_neili") < 2000 )
		return notify_fail("你内力修为现在不够，不能用「绊字诀」！\n");

	if( target->query_temp("dgb/ban") )
		return notify_fail("对方已经被拌中了，放手攻击吧。\n");

	n = me->query_skill("bangjue", 1);

	if( me->query_skill("dagou-bang", 1) > 350 )
		n += random(me->query_skill("bangjue", 1)/2);

	ap = COMBAT_D->skill_power(me, "stick", SKILL_USAGE_ATTACK);
	dp = COMBAT_D->skill_power(target, "dodge", SKILL_USAGE_DEFENSE);

	ap += ap /100000 * me->query_skill("stick") * me->query_int(1)/3;
	dp += dp /100000 * target->query_skill("dodge") * target->query_int(1)/3;

	msg = HBBLU"$N"+weapon->name()+HBBLU"挥出，以「绊字诀」着地扫去，一绊不中，二绊续至，连环钩盘，绵绵而不绝。\n"NOR;

	if( ( ap = random(ap+dp) ) > dp*3/2 ) {
		msg += HBBLU"$n纵身稍慢，被"+weapon->name()+HBBLU"在左胫上一拨，右踝上一钩，扑地倒了。\n"NOR;
		target->add_busy(2+random(3));
		target->recieve_damage("qi", n*3, me);
		target->recieve_wound("qi", n*3, me);
		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		target->set_temp("dgb/ban", n);
		target->add_temp("apply/dodge",-n);
		target->apply_condition("dgb_ban_wound", n/30);
		me->add("neili", -400);
		me->add("jingli", -200);
		me->start_busy(random(2));
		call_out("check_perform", 1, target, n);
	}
	else if( ap > dp ) {
		msg += HBBLU"$n脚下慌乱，抬脚想去踏住"+weapon->name()+HBBLU"，却被"+weapon->name()+HBBLU"在脚踝上一绊，扑通倒地。\n"NOR;
		target->add_busy(1+random(2));
		target->recieve_damage("qi", n*2, me);
		target->recieve_wound("qi", n*2, me);
		if( random(2) ) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		target->set_temp("dgb/ban", n/2);
		target->add_temp("apply/dodge",-n/2);
		target->apply_condition("dgb_ban_wound",n/40);
		me->add("neili", -300);
		me->add("jingli", -100);
		me->start_busy(random(2));
		call_out("check_perform", 1, target, n/2);
	}
	else {
		msg += HIG"$n下盘功夫十分扎实，闪展腾挪间躲开"+weapon->name()+HIG"的绊绕，顺势一脚踢中$N的屁股。\n"NOR;
		me->start_busy(1);
		me->add("neili", -150);
		me->add("jingli", -50);
	}
	if( wizardp(me) ) tell_object(me, HIY"打狗棒法「绊字诀」命中率对比 "+ap+" ："+dp+"。\n"NOR);
	me->start_perform(3, "绊字诀");
	message_vision(msg, me, target);
	return 1;
}

void check_perform(object target, int bonus)
{
	if ( !target || !target->query_temp("dgb/ban")) return;
	if ( target->query_temp("dgb/ban")
	&& ! target->query_condition("dgb_ban_wound")) {
		target->add_temp("apply/dodge", bonus);
		target->delete_temp("dgb/ban");
		return;
	}
	call_out("check_perform", 1, target, bonus);
}

int help(object me)
{
        write(HBBLU"\n打狗棒「绊字诀」："NOR"\n");
        write(@HELP
        打狗棒以轻、巧、灵诸称，舞将起来是四处只见棒影不见人影。
        这「绊字诀」，却是专攻敌人下盘的招数。对于下盘不稳的对手
        极是有效，一旦绊中，对手身形变慢，必处处受制。

        要求：  最大内力 2000 以上；
                当前内力 600 以上；
                打狗棒等级 140 以上；
                混天气功等级 140 以上；
                打狗棒诀等级 140 以上：
                激发招架为打狗棒。
HELP
        );
        return 1;
}
