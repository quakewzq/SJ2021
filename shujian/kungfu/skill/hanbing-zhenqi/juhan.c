// by darken@SJ
// Lklv add help at 2001.10.06

#include <ansi.h>
inherit F_SSERVER;
string exert_name(){ return HIW"聚寒诀"NOR; }

int exert(object me)
{
	string msg;
	int lv = me->query_skill("hanbing-zhenqi",1);

	if (!me->is_fighting())
		return notify_fail("你只能在战斗中使用「聚寒诀」。\n");

	if (lv < 60)
		return notify_fail("以你目前的内功修为尚无法使用「聚寒诀」。\n");

	if (me->query("qi") < me->query("max_qi")/3)
		return notify_fail("你的气血不足。\n");
		
	if ( me->query_temp("ss/focus") >= 15 )	
		return notify_fail("你已经将「聚寒诀」发挥得淋漓尽致。\n");

	msg = HIW"$N内息流动，周身温度陡然降低，居然结了薄薄一层寒霜！\n"NOR;

	if (!me->query_temp("ss/focus")) {
		call_out("remove_effect", lv/5 + random(10), me);
	}
    //这个没有必要吧？一旦死了怎么办？
	//me->receive_damage("qi", 200+random(50));
	me->add_temp("ss/focus", random(lv/200)+1);

	if ( me->query_temp("ss/focus") > 15 )
		me->set_temp("ss/focus", 15);

	message_vision(msg, me);
	me->start_exert(1, "「聚寒诀」");
	return 1;
}

void remove_effect(object me)
{
	if (!me || !me->query_temp("ss/focus") ) return;
	message_vision(HIW"$N周身的寒气渐渐的散去了。\n"NOR,me);
	me->delete_temp("ss/focus");
}

int help(object me)
{
	write(HIW"\n寒冰真气之「聚寒诀」："NOR"\n\n");
        write(@HELP
	战斗中使用，提升本身功力。
	要求：  寒冰真气  60  级以上；
                当前气超过最大气的 1/3 以上。

HELP
        );
        return 1;
}
