// xixue.c 吸血青蝠
// By River
#include <ansi.h>

inherit F_SSERVER;
int perform(object me,object target)
{
	string msg;
	int skill, damage, p, ap, dp;
	skill = me->query_skill("hanbing-mianzhang",1);

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !me->is_fighting(target))
		return notify_fail("你只能对战斗中的对手使用「吸血青蝠」。\n");

	if( me->query_temp("weapon"))
		return notify_fail("你拿着武器怎么能使用「吸血青蝠」！\n");

	if( skill < 120 )
		return notify_fail("你的「寒冰绵掌」等级不够, 还不能使用「吸血青蝠」！\n");

	if( me->query_skill_mapped("strike") != "hanbing-mianzhang")
		return notify_fail("你现在无法使用「吸血青蝠」！\n");

	if (me->query_skill_prepared("strike") != "hanbing-mianzhang")
		return notify_fail("你现在无法使用「吸血青蝠」！\n");

	
	if( me->query_skill("dodge", 1) < 120 )
		return notify_fail("你的轻功不够，无法熟练运用「吸血青蝠」！\n");

	if( !me->query_skill("jiuyang-shengong", 1))
	if( me->query_skill("shenghuo-shengong", 1) < 120)
		return notify_fail("你的圣火神功等级不够，无法使用「吸血青蝠」！\n");

	if((int)me->query("neili") < 400)
		return notify_fail("你的内力不够使用「吸血青蝠」。\n");

	if( me->query_temp("qkdny/yin") )
		return notify_fail("你正在施展乾坤大挪移「引」字诀呢！\n");

	if((int)me->query("jingli") < 200)
		return notify_fail("你的精力不够使用「吸血青蝠」。\n");

	msg = HIC"\n$N突然如同一只吸血青蝠，欺近$n的身前，张嘴便向$n的咽喉咬去。\n"NOR;

	ap = me->query("combat_exp") * me->query_dex(1);
	dp = target->query("combat_exp") * target->query_dex(1);

	if( random(ap + dp) > dp || !living(target)) {
		msg += HIR"$n只觉得咽喉一阵剧痛，$N正在狂吸$n的鲜血！\n"NOR;
		damage = skill*2;
		damage += me->query_skill("strike");
		damage += me->query_skill("force");
		damage += random(damage/2);

		me->add("neili",-250);
		me->add("jingli", -80);

		if(target->query("neili") >= skill*2)
			target->add("neili", - random(skill*2));
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/2, me);
		target->add_condition("hb_poison", skill / 15);
		target->add_busy(random(3));
		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "啮伤");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "啮伤");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
	}
	else {
		msg += CYN"只见$n不慌不忙，轻轻一闪，躲过了$N的利齿！\n"NOR;
		me->add("neili",-100);
		me->add("jingli",-50);
	}
	me->start_perform(3, "吸血青蝠");
	me->start_busy(random(2));
	message_vision(msg, me, target);
	return 1;
}

string perform_name(){ return HIC"吸血青蝠"NOR; }

int help(object me)
{
        write(HIC"\n寒冰绵掌之「吸血青蝠」："NOR"\n\n");
        write(@HELP
        要求：  当前内力 400 以上；
                当前精力 200 以上；
                寒冰绵掌等级 120 以上；
                若无九阳神功需圣火神功等级 120 以上；
                基本轻功等级 120 以上；
                激发掌法为寒冰绵掌；
                激发招架为寒冰绵掌或乾坤大挪移。

HELP
        );
        return 1;
}
