// youming.c
// Modified by Lane@SJ 2005/4/14

#include <ansi.h>

inherit F_SSERVER;

int exert(object me, object target)
{
	int ap, dp;
	int nh = me->query_skill("linji-zhuang", 1)/2;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("「幽冥」字诀只能对战斗中的对手使用。\n");

	if( (int)me->query_skill("linji-zhuang", 1) < 180 )
		return notify_fail("你的临济十二庄修为还不够。\n");

	if( me->query("class") != "bonze" && me->query("family/generation") > 3 )
		return notify_fail("你不是出家人，无法领会临济十二庄的「幽冥」字决！\n");

	if( (int)me->query("neili") < 1500 )
		return notify_fail("你的真气不够。\n");

	if( (int)me->query("max_neili") < 2000 )
		return notify_fail("你的内力修为不够。\n");

	if( me->query_temp("ljz/youming") )	// 修改标记（原为：yun_youming）
		return notify_fail("你正在运用临济十二庄的「幽冥」字诀！\n");

	if( me->query_temp("ljz/wuwo") )	// 改成 不能和 wuwo 同时使用
		return notify_fail("你正在运用临济十二庄的「无我」字决！\n");


	tell_object(me,MAG"你潜运临济十二庄的「幽冥」字诀。。。\n"NOR);

	if( nh > 150 ) nh = 150 + (nh - 150)/10;

	me->set_temp("ljz/youming", nh);  	// 标记修改
	me->add("neili", - 250);
	me->add_temp("apply/armor", nh);

	ap = me->query("combat_exp", 1 ) /1000 * me->query_skill("force");
	dp = target->query("combat_exp", 1)/ 1000 * target->query_skill("force");

	ap += ap/2;

	me->start_perform(2,"「幽冥」字诀");
	me->start_exert(2,"「幽冥」字诀");
	me->start_busy(random(2));

	if ( random(ap + dp) > dp ) {
		message_vision(HIW"$N脸色突然变得阴森可怖，$n陡然冷汗直冒！\n"NOR, me, target);
		me->add_condition("no_perform",nh/30);
		me->add_condition("no_exert",nh/30);
		target->add_condition("no_perform",nh/30);
		target->add_condition("no_exert",nh/30);
		me->start_perform(nh/30,"「幽冥」字诀");
		target->start_perform(nh/30, me->name()+"的「幽冥」字诀");
	}
	call_out("remove_effect", 1, me, target, nh);
	return 1;
}

void remove_effect(object me,object target,int count)
{
	int i;
	if( !me ) return;
	if( !target
	 || !me->is_fighting("target")
	 || count < 1 ) {
		i = me->query_temp("ljz/youming");
		me->add_temp("apply/armor", -i);
		me->delete_temp("ljz/youming");
		message_vision(HIR"$N散去了「幽冥」心法，恢复了正常。\n"NOR, me);
		return;
	}
	call_out("remove_effect", 1, me, count - 1);
}

string exert_name(){ return HIW"幽冥字决"NOR; }

int help(object me)
{
        write(HIW"\n临济十二庄「幽冥字诀」："NOR"\n\n");
        write(@HELP
        要求：  当前内力 1500 以上；
                最大内力 2000 以上；
                临济十二庄等级 180 以上；
                出家或俗家三代弟子；
                不能和「无我」字诀同时使用。
HELP
        );
        return 1;
}
