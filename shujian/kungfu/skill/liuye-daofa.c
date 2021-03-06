// xiuluo-dao.c 修罗刀

inherit SKILL;
#include <ansi.h>

mapping *action = ({
([
	"action" : "$N刀锋回转，连出数刀，刀刀不离$n的$l",
	"lvl" : 0,
	"damage_type" : "割伤"
]),
([
	"action" : "$N左一刀，右一刀，逼著$n连连后退",
	"lvl" : 20,
	"damage_type" : "割伤"
]),
([
	"action" : "$N突然刀交左手，一刀砍向$n的$l，$n惊慌之下，只得向后急退",
	"lvl" : 50,
	"damage_type" : "割伤"
]),
([
	"action" : "$N施展出铁掌掌法，左手连拍，$n往左一避，正撞上刀锋来路",
	"lvl" : 80,
	"damage_type" : "割伤"
]),
([
	"action" : "$N刀刀连环，不等招数使老便已变招，十六刀连续往$n的$l招呼",
	"lvl" : 120,
	"damage_type" : "割伤"
]),
([
	"action" : "$N孤注一掷，集全身之力于刀锋上，向$n一击砍出",
	"lvl" : 160,
	"damage_type" : "割伤"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("你使用的武器不对。\n");
	if ((int)me->query("max_neili") < 50)
		return notify_fail("你的内力不够。\n");
	if ((int)me->query_skill("guiyuan-tunafa", 1) < 10)
		return notify_fail("你的归元吐纳法火候太浅。\n");
	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level, j;
	level   = (int) me->query_skill("liuye-daofa",1);

	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			if ( me->query_temp("daozhang")) {
				return ([  
					"action": CYN+action[j]["action"]+NOR,
					"lvl": action[j]["lvl"],
					"damage_type" : action[j]["damage_type"],
					"force": 200+random(300),
					"dodge": random(30),
					"damage": 100+random(80),
					"parry": random(30),
				]);
			}
			return ([  
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"force":150+random(300),
				"dodge":random(30),
				"damage":60+random(100),
				"parry":random(30),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("liuye-daofa", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query("jingli") < 40)
		return notify_fail("你的体力不够练柳叶刀法。\n");
	if ( me->query("neili") < 20)
		return notify_fail("你的内力不够练柳叶刀法。\n");
        me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"liuye-daofa/" + action;
}
