// xuedao-jing.c 血刀经
// write by iceland
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "$N略略侧身，一招「斩头式」反手从背后横劈出一刀，直奔$n的项颈",
	"skill_name" : "斩头式",
	"lvl" : 0,
	"damage_type" : "割伤",
]),
([
	"action" : "$N突然横卧于地，$n目瞪口呆之际，一招「破膛刀」，手中$w由下而上直劈$n的小腹",
	"skill_name" : "破膛刀",
	"lvl" : 20,
	"damage_type" : "割伤",
]),
([
	"action" : "$N足尖一点，一个倒翻头顶着地，一招「去魂电」，$w一闪，自左而右，由右到左连出十刀",
	"skill_name" : "去魂电",
	"lvl" : 40,
	"damage_type" : "割伤",
]),
([
	"action" : "$N怪叫一声，飞腾空中，一招「流星经天」，手中$w脱手而出，疾射$n的$l",
	"skill_name" : "流星经天",
	"lvl" : 60,
	"damage_type" : "割伤",
]),
([
	"action" : "$N脸色诡异，喉中“呵呵”低吼，一招「蛇行」，$w灵动异常的在$n的$l游走过去",
	"skill_name" : "蛇行",
	"lvl" : 80,
	"damage_type" : "割伤",
]),
([
	"action" : "$N一招「三界咒」，手中$w微微一抖，“嗤嗤嗤”三声轻响，向$n头、胸、腹连劈三刀",
	"skill_name" : "三界咒",
	"lvl" : 100,
	"damage_type" : "割伤",
]),
([
	"action" : "$N炸雷般大喝一声，一式「魔分身」$w照$n搂肩带背斜劈下来，力道凶猛，势不可挡",
	"skill_name" : "魔分身",
	"lvl" : 120,
	"damage_type" : "割伤",
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("你使用的武器不对。\n");
	if (me->query("max_neili") < 150)
		return notify_fail("你的内力不够。\n");
	if (me->query_skill("longxiang-boruo", 1) < 20)
		return notify_fail("你的龙象般若功火候太浅。\n");
	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level, j;
	level   = (int) me->query_skill("xuedao-jing",1);

for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
if (me->query("quest/雪山/shendao/jidao") ) {
return ([  
				 "action" : HIR+replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIR)+NOR,
				"lvl": action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"force":300,
				"dodge":130,
                                "damage":220+random(180),
				"parry":120,
			]);
	}


else if( me->query_temp("sjz_power") && me->query_temp("xdpfm") ) {
return ([  
                                 "action" : WHT+replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"WHT)+NOR,
				"lvl": action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"force":300,
				"dodge":130,
        "damage":200+random(160),
				"parry":120,
			]);
	}

	
			return ([  
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"force":150+random(300),
				"dodge":random(30),
                                "damage":160+random(100),
				"parry":random(30),
			]);
	}

}
int practice_skill(object me)
{
	int lvl = me->query_skill("xuedao-jing", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if (me->query("jingli") < 40)
		return notify_fail("你的体力不够，练不了血刀经。\n");
	if (me->query("neili") < 20)
		return notify_fail("你的内力不够，练不了血刀经。\n");
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}

mixed hit_ob(object me, object target)
{
   int lv = me->query_skill("shenzhao-jing",1);

   if( random(10) > 6 && lv > 250 && !me->query_temp("xdszj") && me->query("quest/雪山/shendao/jidao") && me->query_temp("sjz_power") )
          {
me->set_temp("xdszj",1);
                message_vision(HIW"$N大喝一声，将神照功力运至"+me->query_temp("weapon")->query("name")+"之上，向$n砍去。" NOR,me,target);
me->add_temp("apply/attack",  me->query_skill("shenzhao-jing", 1)/3);

if(wizardp(me))  message_vision(HIW "\n$N有xdszj吗？"+chinese_number(me->query_temp("xdszj"))+"！！！" NOR,me,target);

                         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(4)?1:3);
target->receive_damage("qi", lv/3, me);

                         me->add_temp("apply/attack", -me->query_skill("shenzhao-jing", 1)/3);
me->delete_temp("xdszj");
if(wizardp(me))  message_vision(HIY "\n$N删了xdszj吗？"+chinese_number(me->query_temp("xdszj"))+"！！！\n" NOR,me,target);

         }
     
}







string perform_action_file(string action)
{
	return __DIR__"xuedao-jing/" + action;
}
