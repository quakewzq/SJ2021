// makelove.c
// modified by wind
// modified by akuma 10:36 AM 4/13/2002

#include <ansi.h>
void ing(object, object);
void post(object me, object obj);
void sec_post(object me, object obj);
void trd_post(object me, object obj);
void over(object, object);

int main(object me, string arg)
{
	object obj, *ob,where;
	int i;

	if ( !arg || !objectp(obj = present(arg, environment(me)))) return notify_fail("你想和谁做爱？\n");

	if ( !obj->is_character() || me->query("gender") == obj->query("gender") )
		return notify_fail("这样……？！恐怕不行吧？\n");

	if ( !living(obj)) return notify_fail("人家都这样了，你还...\n");

	if ( !environment(me)->query("sleep_room") || environment(me)->query("no_sleep_room"))
		return notify_fail("总得找个温馨点儿的地方吧。\n");

	if ( me->query("gender") == "女性" && me->query_condition("pregnant") )
		return notify_fail ("你已经怀孕了，还要……？不要命了？\n");

	if ( obj->query("gender") == "女性" && obj->query_condition("pregnant") )
		return notify_fail ("人家已经怀孕了，还要……？你可够残忍的\n");

	if ( me->query("gender") == "女性" && me->query_condition("yuejing_butiao") ) {
		me->force_me("say 人家正来那个，不要……");
		return 0;
	}
	if ( obj->query("gender") == "女性" && obj->query_condition("yuejing_butiao") ) {
		obj->force_me("say 人家正来那个，不要……");
		return 0;
	}
	if ( (int)me->query("age", 1) < 18 ) return notify_fail ("要知道，童子功难练，你要珍惜。\n");

	if ( (int)obj->query("age", 1) < 18 ) return notify_fail ("欺负那么小的孩子，不害臊呀。\n");
	
	where=environment(me);

	ob = all_inventory(environment(me));
	for(i=0; i<sizeof(ob); i++)
		if( ob[i]->is_character()&&ob[i] != me && ob[i]!=obj&&!wizardp(ob[i]) )
			return notify_fail("这儿还有别人呢，多不好意思呀！\n");

	if(!me->query_temp("makelove/quest")) {
		if( me->query("gender") == "男性" ) {
			message_vision(HIM "$N轻轻来到$n身后，双手环抱在$n的腰间，\n\n" +
				"在$n耳边柔声说道：亲爱的，今晚……\n\n"NOR, me, obj);
			tell_object(obj, HIR "傻子也能看出来他想和你共渡良宵，\n" +
				"如果你愿意，请你也对" + me->name() + "("+(string)me->query("id")+")" +
				"下一次 makelove 指令。\n" NOR);
		CHANNEL_D->do_channel( me, "sys", sprintf("%s(%s)"HIR"在%s"HIR"想和%s(%s)那个，请大家来观摩学习。\n",
			me->name(1),getuid(me),(string)where->query("short"),obj->name(1), geteuid(obj)			
			));
		}
		else {
			message_vision(HIM "不知是因为烛光，还是酒精，亦或是因为兴奋，$N的小脸儿红红的，\n\n" +
				"端着酒杯，$N直勾勾地盯着$n：亲爱的……听说……喝酒……乱性……\n\n"NOR, me, obj);
			tell_object(obj, HIR "傻子也能看出来她想和你共渡良宵，" +
				"如果你愿意，请你也对" + me->name() + "("+(string)me->query("id")+")" +
				"下一次 makelove 指令。\n\n" NOR);
		CHANNEL_D->do_channel( me, "sys", sprintf("%s(%s)"HIR"在%s"HIR"想和%s(%s)那个，请大家来观摩学习。\n",
			me->name(1),getuid(me),(string)where->query("short"),obj->name(1), geteuid(obj)			
			));
		}
		obj->set_temp("makelove/quest",1);
	}
	else {
		if( me->query("gender")=="男性" ) {
			message_vision(HIM "$N回敬似的盯着$n的眼睛，半晌一言不发，突然一把抱住$n，一双热唇堵住了$n的嘴，\n" +
				"让$n简直喘不上来气，酒杯、红烛打了一地……\n\n"NOR, me, obj);
			call_out("ing", 1, me, obj);
		}
		else {
			message_vision(HIM "$n甚至能看见$N羞红的耳根，$N轻轻挣开$n的怀抱，\n" +
				"默默地焚香沐浴，$n却再也忍不住，一把将$N抱了起来……\n\n"NOR, me, obj);
			call_out("ing", 1, obj, me);
		}
		me->delete_temp("makelove/quest");
	}
	log_file("static/makelove",sprintf("%s(%s)和%s(%s)在%s做爱于%s\n",
		me->name(1),getuid(me),obj->name(1), geteuid(obj),(string)where->query("short"),ctime(time()) ));
	return 1;
}

void ing(object me, object obj)
{
	if( obj->query("id") != me->query("marry/id") ) {
		if ( me->query("gender")=="男性" ) {
			message_vision(HIW"$N轻轻地抚摸着$n的全身，亲吻着$n的脸颊。兴奋地说道：家花真不如野花香！\n\n"NOR,
				me, obj);
			obj->force_me("blush");
		}
		if ( me->query("gender")=="女性" ) {
			if ( me->query("marry") ) {
				message_vision(HIW"$N娇喘如丝，羞色道：轻点……别让我老公看见……\n\n"NOR,
					me, obj);
				obj->force_me("hehe");
			}
			else {
				message_vision(HIW"$N娇喘如丝，羞色道：哥哥爱死妹妹了……\n\n"NOR,
					me, obj);
				obj->force_me("ok");
			}
		}
	}
	else {
		if ( me->query("gender")=="男性" ) {
			message_vision(HIW"$N轻轻地抚摸着$n的全身，亲吻着$n的脸颊。说道：有妻如此，今生何求？！\n\n"NOR,
				me, obj);
			obj->force_me("iddle");
		}
		if ( me->query("gender")=="女性" ) {
			message_vision(HIW"$N娇喘如丝，羞色道：轻点……别让我老公看见……\n\n"NOR,
				me, obj);
			obj->force_me("hoho");
		}
	}
	me->start_busy(100);
	obj->start_busy(100);
	call_out("post", 10, me, obj);
}

void post(object me, object obj)
{
	message_vision(HIM"\n$N看着$n雪白的皮肤，禁不住情欲大动。\n\n"NOR,me,obj);
	call_out("sec_post", 3, me, obj);
}

void sec_post(object me, object obj)
{
	message_vision(MAG"\n$N和$n相互宽衣解带，羞答答的上了床。\n\n"NOR, me, obj);
	call_out("trd_post", 10, me, obj);
}

void trd_post(object me, object obj)
{
	message_vision(HIW"\n$N和$n相拥而卧，翻云覆雨，汗水淋漓，曲尽温柔，无所不至。\n\n"NOR, me, obj);
	call_out("over", 10, me, obj);
}

void over(object me, object obj)
{
        if ( random(10) > 8 && me->query("gender") == "女性" && ! obj->query_condition("xu_ruo") ) {
                if ( ! me->query("baby_on") && ! me->query("no_pregnant") ) {
			message_vision(HIC+BLINK"$N一声大叫，划破宁静的夜空……\n\n"NOR, me, obj);
			me->set("preg/id", obj->query("id"));
			me->set("preg/name", obj->query("name"));
			me->set("preg/con", obj->query("con"));
			me->set("preg/int", obj->query("int"));
			me->set("preg/dex", obj->query("dex"));
			me->set("preg/str", obj->query("str"));
			me->set("preg/per", obj->query("per"));
			me->set("preg/pur", obj->query("pur"));
			me->set("preg/kar", obj->query("kar"));
			me->apply_condition("pregnant", 500);
		}
	}
        if ( random(10) > 8 && obj->query("gender") == "女性" && ! me->query_condition("xu_ruo") ) {
                if ( ! obj->query("baby_on") && ! obj->query("no_pregnant") ) {
			message_vision(HIC+BLINK"$n一声大叫，划破宁静的夜空……\n\n"NOR, me, obj);
			obj->set("preg/id", me->query("id"));
			obj->set("preg/name", me->query("name"));
			obj->set("preg/con", me->query("con"));
			obj->set("preg/int", me->query("int"));
			obj->set("preg/dex", me->query("dex"));
			obj->set("preg/str", me->query("str"));
			obj->set("preg/per", me->query("per"));
			obj->set("preg/pur", me->query("pur"));
			obj->set("preg/kar", me->query("kar"));
			obj->apply_condition("pregnant", 500);
		}
	}
	message_vision(HIM"许久许久，$N和$n终于停了下来，但仍然相互畏依不愿分开。\n\n"NOR, me,obj);
	if( me->query("qi") < 30 || me->query("jing") < 30 || obj->query("qi") < 30 || obj->query("jing") < 30 ) {
                if( me->query("qi")<30 || me->query("jing") < 30 ) {
			message_vision(HIR "$N突然口吐鲜血，晕倒在地。看来是纵欲过度了。\n"NOR,me);
			me->unconcious();
		}
		else {
			message_vision(HIR "$N突然口吐鲜血，晕倒在地。看来是纵欲过度了。\n"NOR,obj);
			obj->unconcious();
		}
        }
        else
        switch(random(10)) {
        case 0:
                message_vision(HIR "$N突然大叫一声，显然是极度兴奋，紧接着竟晕死过去！\n"NOR,me);
                me->unconcious();
                obj->add("qi",obj->query_str()-55+random(10));
                obj->add("jing",obj->query_con()-55+random(10));
                break;
        case 1:
                message_vision(HIR "$N突然大叫一声，显然是极度兴奋，紧接着竟晕死过去！\n"NOR,obj);
                obj->unconcious();
                me->add("qi",obj->query_str()-55+random(10));
                me->add("jing",obj->query_con()-55+random(10));
                break;
        default:
                if(random(1)) {
                        message_vision(YEL "$N坐在一旁闷头不语，望了一眼仍在微微娇喘的$n，" +
				"喃喃说到：要不然……再让我试一次……\n\n"NOR, me, obj);
                }
                else {
			message_vision(HIY "$n静静地躺在$N的怀里，靠着那起伏的胸膛，" +
				"听着那均匀的呼吸，感到无限的幸福……\n\n"NOR, me, obj);
                }
                obj->add("qi",obj->query_str()-55+random(10));
                obj->add("jing",obj->query_con()-55+random(10));
                me->add("qi",obj->query_str()-55+random(10));
                me->add("jing",obj->query_con()-55+random(10));
        }
	if ( me->query_condition("pregnant") ) {
		me->force_me("cry3");
		me->force_me("say 以后叫我出去怎么见人呀？！");
	log_file("static/makelove",sprintf("%s(%s)被%s(%s)把肚子搞大了。\n",
		me->name(1),getuid(me),obj->name(1), geteuid(obj)));
	}
	if ( obj->query_condition("pregnant") ) {
		obj->force_me("cry3");
		obj->force_me("say 以后叫我出去怎么见人呀？！");
	log_file("static/makelove",sprintf("%s(%s)被%s(%s)把肚子搞大了。\n",
		obj->name(1), geteuid(obj),me->name(1),getuid(me)));
	}
	me->start_busy(1);
	obj->start_busy(1);
        me->delete("no_pragnant");
        obj->delete("no_pragnant");
	me->add("makelove", 1);
	obj->add("makelove", 1);
}

int help(object me)
{
	write(@HELP
指令格式 : makelove <人物>
做爱！
相关知识参看初中《生理卫生》课本，或者向在线老师寻问。

HELP);
	return 1;
}
