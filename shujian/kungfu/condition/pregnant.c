// /kungfu/condition/pregnant.c
// by akuma 11:37 PM 2/19/2002

#include <ansi.h>
#include <condition.h>

int update_condition ( object me, int duration )
{
	mapping my;

        my = me->query_entire_dbase();

	if ( duration < 800 && duration >= 300 ) {
		if ( me->query_temp("pregnant") > 0 )
			me->add_temp ("pregnant", -1);
		else {
			if ( me->query("gender") == "女性" ) {
				message_vision ("$N只觉一阵不适，吐出一些清水，双颊红晕起来。\n", me);
				if ( my["pur"] > 20 )
					command ("blush");
				if ( my["pur"] < 10 )
					command ("iddle " + my["id"]);
				me->set_temp("pregnant", 5);
			}
		}
	}
	if ( duration < 300 && duration >= 50 ) {
		if ( me->query_temp("pregnant") > 0 )
			me->add_temp ("pregnant", -1);
		else {
			if ( me->query("gender") == "女性" ) {
				message_vision ("$N抚摸着自己日益隆起的腹部，脸上露出一丝甜意。\n", me);
				me->set_temp("pregnant", 5);
			}
		}
	}
	if ( duration < 50 ) {
		if ( me->query_temp("pregnant") > 0 )
			me->add_temp ("pregnant", -1);
		else {
			if ( me->query("gender") == "女性" ) {
				switch ( random (1) ) {
				case 0 :
					message_vision ("由于腹部的日益隆起，$N的行动变得不便了起来。\n", me);
					break;
				case 1 :
					message_vision ("突然之间，$N只觉腹中的孩子在练习踢腿。\n", me);
					break;
				}
				tell_object ( me, HIY"马上就要生了，快去找个大夫吧。\n"NOR );
				me->start_busy(1);
				me->set_temp("pregnant", 5);
			}
		}
	}
	me->apply_condition("pregnant", duration-1);
	if ( duration <= 0 ) {
		if ( me->query("gender") == "女性" ) {
			me->delete_temp("pregnant");
			message_vision ("$N一声惨叫，隆起的腹部奇痛无比。倒在了地上。\n", me);
			tell_object ( me, HIR"你只觉奇痛无比，孩子好像就要出来了。\n"NOR );
			me->set_temp("last_damage_from", "难产");
			me->die();
		}
		return 0;
	}
	return CND_CONTINUE;
}

string query_type(object me)
{
	return "hurt";
}

