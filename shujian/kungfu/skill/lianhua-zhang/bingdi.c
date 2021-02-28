// bingdi.c 「并蒂莲花」

#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return HIG"并蒂莲花"NOR; }

int perform(object me, object target)
{
	int lvl,jiali;

	lvl = (int)me->query_skill("lianhua-zhang", 1);

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 ||!target->is_character()
	 ||!me->is_fighting(target))
		return notify_fail("「并蒂莲花」只能对战斗中的对手使用。\n");

	if( me->query_skill_prepared("strike") != "lianhua-zhang"
	 || me->query_skill_mapped("strike") != "lianhua-zhang"
	 )
		return notify_fail("你必须用莲花掌才能发出此绝招。 \n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("「并蒂莲花」只能空手使用。\n");

	if( me->query_skill("huntian-qigong", 1) < 120 )
		return notify_fail("你的混天气功功力还不足以使用「并蒂莲花」!\n");

	if( me->query_skill("lianhua-zhang",1) < 120 )
		return notify_fail("你的莲花掌修为不够，还不能使出「并蒂莲花」绝技!\n");

	

	if( me->query("max_neili") < 1500 )
		return notify_fail("你的内力修为尚欠火候。\n");

	if( me->query("neili") < 700 )
		return notify_fail("你现在内力不够, 不能使用「并蒂莲花」! \n");

	if( me->query("jingli") < 500 )
		return notify_fail("你现在精力不够, 不能使用「并蒂莲花」! \n");

	if( me->query_temp("lhz/bdlh") )
		return notify_fail("你目前气血翻涌，无法运用「并蒂莲花」！\n");

	if( me->query_temp("lhz/cailian") )
		return notify_fail("你感到气血翻涌，无法运用「并蒂莲花」！\n");

	message_vision(HIG"\n$N脚下不丁不八，右掌自上向下，左掌自下向上，交错连续划了两个圆圈，\n"
                       +"双掌在胸前一并，然后双腕外翻，又划了两个圆圈后突然分袭向$n。\n"
                       +"这两掌唤做「并蒂莲花」，使出来时双掌如穿花蝴蝶般飞舞，非常好看。\n"NOR,me,target);

	jiali = (int)me->query("jiali");
	me->add("neili",- 300);
	me->add("jingli", -80);

	lvl /= 4;

	if( me->query_skill("lianhua-zhang", 1) > 280 )
		lvl = to_int(me->query_skill("lianhua-zhang", 1)/4.0 * me->query_skill("lianhua-zhang", 1)/280.0);

	me->add_temp("apply/strike", lvl);
	me->add_temp("apply/attack", lvl);
	COMBAT_D->do_attack(me, target, 0, 1);

	me->set_temp("lhz/bdlh",2);
	if( present(target,environment(me)) && me->is_fighting(target) )
		COMBAT_D->do_attack(me, target, 0, 1);

	if( present(target,environment(me)) && me->is_fighting(target) )
		COMBAT_D->do_attack(me, target, 0, random(3)?1:3);

	me->add_temp("apply/strike", -lvl);
	me->add_temp("apply/attack", -lvl);
	me->delete_temp("lhz/bdlh");
	me->start_perform(3, "并蒂莲花");
	me->start_busy(random(2));
	return 1;
}

int help(object me)
{
        write(HIG"\n莲花掌「并蒂莲花」："NOR"\n");
        write(@HELP
        并蒂莲花为莲花掌技巧之一。功力达到者可连续发出几掌。
        要求：  最大内力  1500 以上；
                当前内力  700 以上；
                当前精力  500 以上；
                莲花掌等级 120 以上；
                混天气功等级 120 以上；
                激发招架为莲花掌。
HELP
        );
        return 1;
}
