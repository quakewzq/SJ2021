// yinsuo-jinling.c 银索金铃
// By River
#include <ansi.h>
inherit SKILL;

string  *msg = ({
"$N左手轻扬，手中$w忽地甩了出来，直扑$n的$l。无声无息，事先竟没半点朕兆",
"$N手持$w矫矢似灵蛇击向$n，再加两枚金球不断发出玎玎之声，更是扰人心魄",
"$n又听得金球中发出玎玎声响，声虽不大，却是十分怪异，入耳荡心摇魄。",
"$N身形一变，转手一挥$w，$n大惊之下，身子後仰，$w离脸数寸急掠而过",
"$N手腕微抖，$w翻将过去，自下而上，打向$n身上$l处的「合谷穴」",
"$N手中两条$w犹如水蛇般蜿蜒而出，玎玎两响，$n手腕上的「灵道穴」都被$w点中",
"$N微微一笑跨前一步，右手$w一抖，$w矫夭飞舞，好比彩凤朝阳一般抽向$n",
});

int valid_enable(string usage)
{ 
	return usage == "whip" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
    if(me->query_temp("sanwu/buwei")){
        if((int)me->query_skill("yinsuo-jinling",1)<350)
        return ([
                "action":       msg[random(sizeof(msg))],
                "damage":       180 + random(120),
                "damage_type":  "拉伤",
                "dodge":        5+random(30),
                "force":        random(330) + 180,
                "parry":        random(30),
            ]);
        if((int)me->query_skill("yinsuo-jinling",1)<450)
        return ([
                "action":HIW +replace_string(replace_string(msg[random(sizeof(msg))], "$w", "$w"), "$w", "$w"HIW)+NOR,
                "damage":       200 + random(140),
                "damage_type":  "拉伤",
                "dodge":        10+random(30),
                "force":        random(300) + 200,
                "parry":        random(30),
            ]);
        else
        return ([
                "action":HIR +replace_string(replace_string(msg[random(sizeof(msg))], "$w", "$w"), "$w", "$w"HIR)+NOR,
                "damage":       150 + random(200),
                "damage_type":  "拉伤",
                "dodge":        20+random(30),
                "force":        random(300) + 200,
                "parry":        random(30),
            ]);
        }
        if(me->query_temp("juan") && (int)me->query_skill("yinsuo-jinling",1)>=350)
        return ([
                "action":HIG +replace_string(replace_string(msg[random(sizeof(msg))], "$w", "$w"), "$w", "$w"HIG)+NOR,
                "damage":       220 + random(150),
                "damage_type":  "拉伤",
                "dodge":        10+random(30),
                "force":        random(300) + 200,
                "parry":        random(30),
            ]);
        else
	return ([
		"action":	msg[random(sizeof(msg))],
		"damage":	160 + random(100),
		"damage_type":	"拉伤",
		"dodge":	random(30),
		"force":	random(300) + 150,
		"parry":	random(30),
       ]);
}

int valid_learn(object me)
{
	object weapon;
	if( (int)me->query("max_neili") < 500 )
		return notify_fail("你的内力不足，没有办法练银索金铃, 多练些内力再来吧。\n");
	if ((int)me->query_skill("yunu-xinjing", 1) < 100)
		return notify_fail("你的玉女心经内功火候太浅。\n");
	if (!objectp(weapon = me->query_temp("weapon"))
	 || ( string)weapon->query("skill_type") != "whip" )
		return notify_fail("你使用的武器不对。\n");
	return 1;
}
 
int practice_skill(object me)
{
	if ( me->query("jingli") < 40)
		return notify_fail("你的体力不够练银索金铃。\n");
	if ( me->query("neili") < 20)
		return notify_fail("你的内力不够练银索金铃。\n");
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	object weap,weap1;
	int ap, dp;
	weap = victim->query_temp("weapon");
	weap1 = me->query_temp("weapon");

	if( !me->query("env/no_chan")
	 && me->query_skill("yinsuo-jinling", 1) > 120
	 && me->query("neili") > 700
	 && victim->query_temp("weapon")
	 && random(me->query_skill("yinsuo-jinling",1)) > victim->query_skill("dodge", 1)/2 
	 && random(10) > 7) {
		message_vision(HIY"只见$N急速挥舞"+ weap1->name() + HIY"，转出无数个大小圈子，以阴柔之劲缠住对方的" + weap->name() +HIY"！\n" NOR, me );
		victim->add_busy(1);
		ap = me->query("combat_exp", 1) /1000 * me->query_dex(1);
		dp = victim->query("combat_exp", 1) /1000 * victim->query_str(1);
		if (random(ap + dp ) > dp ) {
			message_vision(HIY"$N气运手臂用力一拽，"+ weap->name()+ HIY"却无法从"+weap1->name()+HIY"的缠绕中脱开，情急之下只好放弃了手中的兵刃。\n" NOR, victim );
			weap->move(environment(me));
			victim->reset_action();
		}
		else {
			message_vision(HIY"$N暗运巧劲，"+ weap->name()+ HIY"顺着方向快速旋转数下，解开了"+weap1->name()+HIY"的缠绕。\n" NOR, victim );
			victim->add("neili", -50);
		}
		me->add("neili", -(20+random(30)));
	}
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"yinsuo-jinling/" + action;
}
