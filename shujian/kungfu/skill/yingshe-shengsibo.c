//daidai制作于2005-10-07

// yingshe-shengsibo 鹰蛇生死博



#include <ansi.h>

#include <combat.h>

inherit SKILL;

mapping *action = ({

([      "action" : "$N左掌护胸，右臂微举作蛇形，续而向外疾伸，一式「灵蛇出洞」攻向$n的$l",

        "force" : 140,

        "dodge" : 10,

        "damage_type" : "瘀伤",

        "lvl" : 0,

        "skill_name" : "灵蛇出洞"

]),



([      "action" : "$N倏地抢上一步，使出「飞鹰现爪」，左臂横挥，一转身，双手十指犹似两把鹰爪，猛插$n的$l",

        "force" : 180,

        "dodge" : 10,

        "parry" : 10,

        "lvl" : 10,

        "damage_type" : "抓伤",

        "skill_name" : "飞鹰现爪"

]),



([      "action" : "$N使出「画蛇添足」，双手向$n抓去，同时又无声无息地一脚踢向$n的$l",

        "force" : 200,

        "dodge" : 10,

        "damage_type" : "瘀伤",

      "lvl" : 20,

        "skill_name" : "画蛇添足"

]),([      "action" : "$N拔地而起，一式「凶鹰袭兔」，从半空中飞扑而下，迅猛地抓向$n的$l",

        "force" : 220,

        "dodge" : 10,

        "parry" : 10,

        "damage": 5,

        "lvl" : 30,

        "damage_type" : "抓伤"

,

        "skill_name" : "凶鹰袭兔"

]),

([      "action" : "只见$N跌扑于地，趁着$n向前探视，突然蹦起使出「杯弓蛇影」，向$n连抓几把",

        "force" : 240,

        "dodge" : 10,

        "damage_type" : "抓伤",

        "lvl" : 40,

        "skill_name" : "杯弓蛇影"

]),

([      "action" : "$N腾空高飞三丈，一式「鹰扬万里」，天空中顿时显出一个巨灵爪影，缓缓罩向$n",

        "force" : 280,

        "dodge" : 0,

        "parry" : 0,

        "damage": 20,

        "lvl" : 50,

        "damage_type" : "抓伤"

,

        "skill_name" : "鹰扬万里"

]),

([      "action" : "$N双手徊旋中幻出万道蛇影，一招「万蛇汹涌」，诡异奇玄、铺天盖地推向$n",

        "force" : 300,

        "dodge" : 0,

        "damage_type" : "内伤",

        "lvl" : 60,

        "skill_name" : "万蛇汹涌"

]),

([      "action" : "$N单腿直立，双臂平伸，一式「雄鹰展翅」，双爪一前一后拢向$n的$l",

        "force" : 320,

        "dodge" : 15,

        "parry" : 15,

        "damage": 15,

        "lvl" : 70,

        "damage_type" : "抓伤",

        "skill_name" : "雄鹰展翅"

]),

([      "action" : "$N出其不意地使一式「白蛇吐信」，右手食中两指微分，闪电般地往$n的$l猛捅",

        "force" : 360,

        "dodge" : 0,

        "damage_type" : "瘀伤",

        "lvl" : 80,

        "skill_name" : "白蛇吐信"

]),

([      "action" : "$N左右手掌爪互逆，一式「鹰击长空」，无数道劲气破空而出，迅疾无比地击向$n",

        "force" : 380,

        "dodge" : 10,

        "parry" : 0,

        "damage": 15,

        "lvl" : 90,

        "damage_type" : "抓伤"

,

        "skill_name" : "鹰击长空"

]),

([      "action" : "$N双臂柔若无骨地伸缩着，使出「蛇磐青竹」缠住$n，右臂从不可思议处抹到$n的$l",

        "force" : 420,

        "dodge" : 5,

        "damage_type" : "内伤",

        "lvl" : 100,

           "skill_name" : "蛇磐青竹"

 ] ),

([      "action" : "$N一式「蛇鹰互搏」，双手带着嘶嘶破空之声，猛烈迅速地尽往$n上身要害攻击",

        "force" : 480,

        "dodge" : 20,

        "damage_type" : "瘀伤",

        "lvl" : 120,

        "skill_name" : "蛇鹰互搏"

]),});

int valid_enable(string usage) { return usage=="claw" || usage=="hand" ||  usage=="parry"; }



int valid_combine(string combo) { return combo=="yingshe-shengsibo"; }



int valid_learn(object me)

{
	 mapping myfam = (mapping)me->query("family");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))

                return notify_fail("练鹰蛇生死博必须空手。\n");

	if ( myfam["family_name"] !=  "华山派")
		  return notify_fail("你非华山弟子，无资格修习此武功。\n");

                     if ((int)me->query("max_neili") < 300)

                return notify_fail("你的内力太弱，无法练鹰蛇生死博。\n");

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

        int i, level,attack;

        object ob;

        

        ob = me->select_opponent();

        level = me->query_skill("yingshe-shengsibo", 1)+1;

    

            if( me->query_temp("huashan_shengsi")    &&living(ob)

&&me->query_skill_prepared("hand") == "yingshe-shengsibo"

&&me->query_skill_prepared("claw") == "yingshe-shengsibo"

&&!me->query_temp("huashan_yingshe")

&&me->query("neili")>800

)

    {    

        attack=level/100;

    if(attack>4) attack=4;

                            if(attack<=1) attack=1;

message_vision(HIY "\n紧接着$N右手五指并拢成蛇头之形，点、打、刺、戳，有如急风暴雨般攻出了"+ chinese_number(attack+1)+"招。\n" NOR, me);

                    for(i=0;i<attack;i++)

                    {

                        me->add("neili", -(50+random(50)));

                        

                        ob = me->select_opponent();

                        if(!living(ob))

                        {

                        break;

                        }

                        me->set_temp("huashan_yingshe",1);

                    COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 1);  

                        me->delete_temp("huashan_yingshe");

me->delete_temp("huashan_shengsi");

                    }

        }





        

        for(i = sizeof(action); i > 0; i--)

                if(level > action[i-1]["lvl"])

                        return action[NewRandom(i, 20, level/5)];

}



int practice_skill(object me)

{

        if ((int)me->query("jingli") < 30)

                return notify_fail("你的精力太低了。\n");

        if ((int)me->query("neili") < 20)

                return notify_fail("你的内力不够练鹰蛇生死博。\n");

        me->receive_damage("jingli", 25);

        me->add("neili", -5);

        return 1;

}

string perform_action_file(string action)

{

        return __DIR__"yingshe-shengsibo/" + action;

}