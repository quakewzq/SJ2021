#include <ansi.h>

int exert(object me)
{
	int i;

	if(me->query_temp("jiuyin/powerup"))
		return notify_fail("你正在运使九阴总诀。\n");

	if ((int)me->query_skill("jiuyin-zhengong", 1) < 200)
		return notify_fail("你的九阴真功修为还不够。\n");

	if ((int)me->query_skill("daode-jing", 1) < 200)
		return notify_fail("你的道德经修为还不够。\n");

	if( (int)me->query("neili") < 1500 )
		return notify_fail("你的真气不够。\n");

        i = me->query_skill("force")/5;
	me->add("neili", -500);
	me->start_exert(3, "九阴总诀");
	me->add_temp("apply/dodge", i);
        me->add_temp("apply/parry", i);
	me->add_temp("apply/force", i);
	me->add_temp("apply/sword", i);
	me->add_temp("apply/whip", i);
	me->add_temp("apply/strike", i);
	me->add_temp("apply/cuff", i);
	me->add_temp("apply/claw", i);
	me->set_temp("jiuyin/powerup", 1);
	message_vision(HIY"$N运起九阴总诀，功夫威力陡然大增！\n"NOR, me);

	if ( me->is_fighting())
		me->start_busy(random(2));
	call_out("remove_effect", (int)me->query_skill("force")/4, me, i);
	return 1;
}

void remove_effect(object me, int i)
{
	if (!me) return;
	me->delete_temp("jiuyin/powerup");
	me->add_temp("apply/dodge", - i);
	me->add_temp("apply/force", - i);
        me->add_temp("apply/parry", - i);
	me->add_temp("apply/sword", - i);
	me->add_temp("apply/whip", - i);
	me->add_temp("apply/strike", - i);
	me->add_temp("apply/cuff", - i);
	me->add_temp("apply/claw", - i);
	message_vision(HIY"$N的九阴总诀运使完毕，吁了一口气。\n"NOR, me);
}

string exert_name(){ return HIY"九阴总诀"NOR; }

int help(object me)
{
        write(HIY"\n九阴真功之「九阴总诀」："NOR"\n\n");
        write(@HELP
        要求：  当前内力 1500 以上；
        	道德经等级 200 以上；
                九阴真功等级 200 以上。

HELP
        );
        return 1;
}
