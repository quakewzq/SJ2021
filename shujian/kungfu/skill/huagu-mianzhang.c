// huagu-mianzhang.c 化骨绵掌
// rewrite by olives@SJ
// 4/19/2000
// Update By lsxk@Hsbbs 增加颜色效果  2007/6/6

inherit SKILL;
#include <ansi.h>
#include <combat_msg.h>
#include <combat.h>

mapping *action = ({
([
	"action" : "只见$N身形展动，绕着$n不停转圈，身法奇快，一式「春风拂柳」，一掌又一掌地向$n身上击去",
	"damage_type" : "内伤",
	"lvl" : 0,
	"post_action" : (: call_other, __FILE__, "do_attack" :),  //级别设置低一点，小player也可以用出来
	"skill_name" : "春风拂柳"
]),
([
	"action" : "$N双掌一立，一式「灵蛇出洞」，右手化掌为抓，噗的一声，挟着一股劲风向$n的猛抓过去",
	"damage_type" : "刺伤",
	"lvl" : 15,
	"post_action" : (: call_other, __FILE__, "qin_na" :),  //级别设置低一点，小player也可以用出来
	"skill_name" : "灵蛇出洞"
]),
([
	"action" : "$N缓缓地举起双掌，一式「轻风细雨」，不带一点掌力地轻轻地拍向$n的前胸",
	"damage_type" : "内伤",
	"lvl" : 30,
	"post_action" : (: call_other, __FILE__, "no_pfm" :),  //级别设置低一点，小player也可以用出来
	"skill_name" : "轻风细雨"
]),
([
	"action" : "只见$N一肩转身，左手护面，右手伏击，乘$n不备，一式「风行草偃」，猛地一掌击出",
	"damage_type" : "瘀伤",
	"lvl" : 45,
	"post_action" : (: call_other, __FILE__, "do_damage" :),
	"skill_name" : "风行草偃"
]),
([
	"action" : "$N右掌略偏，在$n左肩轻轻一按，然后左掌向穿出，一式「半雨半晴」，向$n的$l轻轻拍了下去",
	"damage_type" : "瘀伤",
	"lvl" : 60,
	"post_action" : (: call_other, __FILE__, "dian_xue" :),
	"skill_name" : "半雨半晴"
]),
([
	"action" : "$N身形猛地向上跃起，一式「如影随形」，双臂柔若无骨般地缠上$n的双臂，然后双掌一合，轻飘飘地向$n前胸拍去",
	"damage_type" : "瘀伤",
	"lvl" : 80,
	"post_action" : (: call_other, __FILE__, "san_du" :),
	"skill_name" : "如影随形"
]),
});

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练化骨绵掌必须空手。\n");
	if ((int)me->query_skill("dulong-dafa", 1) < 30)
		return notify_fail("你的毒龙大法火候不够，无法学化骨绵掌。\n");
	if ((int)me->query("max_neili") < 250)
		return notify_fail("你的内力太弱，无法练化骨绵掌。\n");
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
   string msg;
	level = (int)me->query_skill("huagu-mianzhang", 1);

	for(i = sizeof(action); i > 0; i--) {
		if(level >= action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
												
                   msg = action[j]["action"];
                    if (me->query_temp("sld/pfm/bujue"))
                        msg = HIC + msg + NOR;

			if(me->query_temp("sld/dianxue"))
			return ([
                           "action": msg,
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
				"post_action": (: call_other, __FILE__, "dianxue" :),
				"force": me->query("shen")>0?200 +random(200):250+random(250),
				"attack": me->query("shen")>0?50 +random(100):100+random(150),
				"dodge": me->query("shen")>0?random(30):random(30)-10,
				"parry": me->query("shen")>0?random(30):random(20),
			]);
						
			return ([
                           "action": msg,
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
				"post_action": action[j]["post_action"],
				"force": me->query("shen")>0?150 +random(300):200+random(350),
				"dodge": me->query("shen")>0?random(30):random(30)-10,
				"parry": me->query("shen")>0?random(30):random(20),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("huagu-mianzhang", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query("jingli") < 50)
		return notify_fail("你的精力太低了。\n");
	if ( me->query("neili") < 20)
		return notify_fail("你的内力不够练化骨绵掌。\n");
	me->receive_damage("jingli", 40 );
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)
{   
	return __DIR__"huagu-mianzhang/" + action;	   
}

void skill_improved(object me)
{
	int skill, yl;
	skill = me->query_skill("huagu-mianzhang", 1);
	yl = me->query_skill("shenlong-yaoli", 1);
	if( skill >= 200 && !me->query("sld/hgmz") ){
		tell_object(me, HIW"\n忽然，你觉得心中一阵畅然，浑身只觉精力弥漫，有使不完的劲，不禁长啸起来。！\n"NOR);
		me->add("max_neili", random(yl+random(yl)));
		me->set("sld/hgmz", 1);
	}
}
void dianxue(object me,object victim,object weapon,int damage)
{
	int ap,dp,pp,lvl;
	if (!victim->is_fighting(me)
	|| victim == me
	|| victim->is_ghost()
	|| !living(victim)
	)
		return;
	if (me->query_skill("tenglong-bifa",1) < 30)
		return;
	if( damage > 0 )
	{
		if( objectp(me) )
		{
			ap = COMBAT_D->skill_power(me,"dagger",SKILL_USAGE_ATTACK);
			dp = COMBAT_D->skill_power(victim,"dodge",SKILL_USAGE_DEFENSE);
			pp = COMBAT_D->skill_power(victim,"parry",SKILL_USAGE_DEFENSE);
			lvl = me->query_skill("tenglong-bifa",1);
			if(random(ap+dp)>dp/3 && random(ap+pp)>pp/3)
			{
					switch(random(3))
					{
						case 0:
							message_vision(HIW"只见$n闷哼一声，原来$p的【神藏穴】已经被$N击中！\n"NOR,me,victim);
							victim->add_condition("no_exert",1+random(lvl/20));
							break;
						case 1:
							message_vision(HIR"只见$n闷哼一声，原来$p的【神封穴】已经被$N击中！\n"NOR,me,victim);
							victim->add_condition("no_perform",1+random(lvl/20));
							break;
						case 2:
							message_vision(HIC"只见$n闷哼一声，原来$p的【步廊穴】已经被$N击中！\n"NOR,me,victim);
							victim->start_lost(1+random(lvl/10));
							break;
					}
			}
		}
	}
}

void do_attack(object me,object victim,object weapon,int damage)
{
	int ap,dp,pp,lvl;

	if (!victim->is_fighting(me)
	|| victim == me
	|| victim->is_ghost()
	|| !living(victim)
	|| me->query_temp("sld/post_action/neishang")	// 这个是防止如果在post_action里面在do_attack引起的问题
	|| me->is_perform()
//	|| me->query_temp("sld/pfm")
	)
		return;

	if (me->query_skill("huagu-mianzhang",1) < 30)
		return;

	me->set_temp("sld/post_action/neishang",1);

	if( damage > 0 )
	{
		if( objectp(me) )
		{
			ap = COMBAT_D->skill_power(me,"strike",SKILL_USAGE_ATTACK);
			dp = COMBAT_D->skill_power(victim,"dodge",SKILL_USAGE_DEFENSE);
			pp = COMBAT_D->skill_power(victim,"parry",SKILL_USAGE_DEFENSE);
			lvl = me->query_skill("huagu-mianzhang",1);
			if(random(ap+dp)>dp/3 && random(ap+pp)>pp/3)
			{
					message_vision("$N趁$n旧力已尽，新力未生之际乘机又补上一掌。\n"NOR ,me,victim);
					me->add_temp("apply/attack",lvl/10);
					COMBAT_D->do_attack(me,victim,me->query_temp("weapon"),TYPE_REGULAR);
					me->add_temp("apply/attack",-lvl/10);

					if(!random(5)
					&& me->query("env/化骨绵掌")=="内伤")
					{
						me->add_temp("apply/attack",lvl/8);
						message_vision("只见$N手臂如同灵蛇一般柔弱无骨，在几乎不可能发招的情况下，缠上$n的手臂，再发一招。\n"NOR,me,victim);
						COMBAT_D->do_attack(me,victim,me->query_temp("weapon"),TYPE_REGULAR);
						me->add_temp("apply/attack",-lvl/8);
						me->start_perform(1+random(2),"「绵掌内伤」");
					}

			}
		}
	}
	me->delete_temp("sld/post_action/neishang");
}

void qin_na(object me,object victim,object weapon,int damage)
{
	int ap,dp,pp;
	object vwp;

	if(!victim->is_fighting(me)
	|| victim == me
	|| victim->is_ghost()
	|| !living(victim)
	|| me->query_temp("sld/post_action/qinna")   // 这个是防止如果在post_action里面在do_attack引起的问题
	|| me->is_perform()
//	|| me->query_temp("sld/pfm")           // pfm的时候如果再出来这个，可能会太强
	//|| me->query("env/化骨绵掌")!= "擒拿"    // 如果不想用，也不勉强。
	|| victim->query_temp("lost_attack")       // 对方已经被擒拿住了，没必要再擒拿了。
	)
		return;

	if(me->query_skill("huagu-mianzhang",1)<60)
		return;

	me->set_temp("sld/post_action/qinna",1);

	if( damage > 0 )
	{
		if( objectp(me) )
		{
			ap = COMBAT_D->skill_power(me,"dagger",SKILL_USAGE_ATTACK);
			dp = COMBAT_D->skill_power(victim,"dodge",SKILL_USAGE_DEFENSE);
			pp = COMBAT_D->skill_power(victim,"parry",SKILL_USAGE_DEFENSE);
			if(random(ap+dp+pp)>dp+pp) //之所以这么判断要求高，怕一开始太强
			{
				message_vision(HIW"$n窜高伏低，身法轻盈，但是$N手臂如同灵蛇一般，缠上$n的手臂，。\n"NOR,me,victim);
				message_vision(HIW"只见$N右手扣住$n的脉门，左手反腕一曲一点，径取$n手腕的阳溪穴。\n"NOR,me,victim);
				vwp = victim->query_temp("weapon");
				if(objectp(vwp))
				{
					message_vision(HIW"$n只觉手腕一阵酸麻，手中的"+vwp->name()+HIW+"再也把持不住，当啷一声掉落在了地上。\n"NOR,me,victim);
					vwp->unequip();
					vwp->move(environment(me));
					if(vwp->query("no_get")
					|| vwp->query("unique"))
						destruct(vwp);
					victim->reset_action();
					victim->set_temp("lost_attack",2);
				}
				else
				{
					message_vision(HIW"结果一击命中，$n只觉得手腕一阵酸麻，竟然再也抬不起手来。\n"NOR,me,victim);
					victim->set_temp("lost_attack",3+random(3));
				}
				me->start_perform(3,"「点穴擒拿」");
			}
		}
	}
	me->delete_temp("sld/post_action/qinna");
}

void no_pfm(object me,object victim,object weapon,int damage)
{
	int m_neili,v_neili,m_force,v_force,effect;

	if(!victim->is_fighting(me)
	||  victim == me
	||  victim->is_ghost()
	|| !living(victim)
	||  victim->query_condition("no_perform")   // 如果对方已经不能perform了，就不必再附加效果了。
	|| me->is_perform()
//	||  me->query_temp("sld/pfm")
	)
		return;

	if(me->query_skill("huagu-mianzhang",1)<100)
		return;

	if( damage > 0 )
	{
		if( objectp(me) && objectp(victim) )
		{
			message_vision(HIY"$N的手掌紧贴着$n的身体，掌心劲力急吐，内劲深入$n的奇经八脉。\n"NOR,me,victim);
			m_neili = me->query("neili");
			v_neili = victim->query("neili");
			m_force = me->query_skill("force");
			v_force = victim->query_skill("force");
			effect = SKILL_D("dulong-dafa")->force_effect(victim->query_skill_mapped("force"));
			if(random(m_neili+m_force*8)>(v_neili+v_force*8)/3
			&& random(effect) > 0)
			{
				message_vision("$n惊惧如狂，急忙运起内力，想驱出体内异种真气，却发现真气已经深入到自己的五脏六腑，无法驱出！\n"NOR,me,victim);
				if(effect<3)
					victim->apply_condition("no_perform",1+random(5-effect));
				me->start_perform(2+random(3),"「内劲锁魂」");
			}
			else
			{
				message_vision("$n不慌不忙，运起体内"+(effect>0?"纯阳":"雄浑")+"真气，眨眼工夫便驱出体内真气！\n"NOR,me,victim);
				me->start_perform(1+random(2),"「内劲锁魂」");
			}
		}
	}
}

void do_damage(object me,object victim,object weapon,int damage)
{
	int m_neili,v_neili,m_force,v_force,effect;

	if(!victim->is_fighting(me)
	||  victim == me
	||  victim->is_ghost()
	|| !living(victim)
	|| me->is_perform()
//	||  me->query_temp("sld/pfm")
	)
		return;

	if(me->query_skill("huagu-mianzhang",1)<100)
		return;

	if( damage > 0 )
	{
		if( objectp(me) && objectp(victim) )
		{
			message_vision(HIY"$N的手掌紧贴着$n的身体，掌力吞吐不定，送出一道隐寒无比的内劲。\n"NOR,me,victim);
			m_neili = me->query("neili");
			v_neili = victim->query("neili")+1;
			m_force = me->query_skill("force");
			v_force = victim->query_skill("force");
			effect = SKILL_D("dulong-dafa")->force_effect(victim->query_skill_mapped("force"));
			damage = m_force+ me->query("jiali");
			damage = damage/2 + random(damage/2);
	     if(m_neili<m_force) m_neili = m_force;
	     if(v_neili<v_force) v_neili = v_force;
		    if(v_force<=0) v_force = 1;
			   damage *= (m_neili*100/v_neili/100);
			damage *= (5-effect);
			if(wizardp(me))
				tell_object(me,sprintf("damage = %O",damage));
			if(damage)
			{
				if(random(m_neili+m_force*8)>(v_neili+v_force*8)/3
				&& !random(effect))
				{
					message_vision("$n急忙运起体内真气，想要驱出体内寒气，寒气已经对自己的五脏六腑造成了很大的伤害！\n"NOR,me,victim);
					victim->recieve_damage("qi",damage);
					victim->recieve_wound("qi",damage/2);
					COMBAT_D->report_status(victim);
					me->start_perform(1+random(3),"「内功伤敌」");
				}
				else
				{
					message_vision("$n不慌不忙，运起体内"+(effect>0?"纯阳":"雄浑")+"真气，$N灌注的内力竟然丝毫不起作用！\n"NOR,me,victim);
					me->start_perform(1+random(2),"「内功伤敌」");
				}
			}
		}
	}
}

void dian_xue(object me,object victim,object weapon,int damage)
{
	int effect;

	if(!victim->is_fighting(me)
	||  victim == me
	||  victim->is_ghost()
	|| !living(victim) 
	//||  me->query("env/化骨绵掌")!= "点穴"    // 如果不想用，也不勉强。
	|| me->is_perform()
//	||  me->query_temp("sld/pfm")
	||  victim->is_busy()
	)
		return;

	if(me->query_skill("huagu-mianzhang",1)<100)
		return;

	if( damage > 0 )
	{
		if( objectp(me) && objectp(victim) )
		{
			message_vision(HIY"$N紧跟着变掌为指，手指连动，轻拂$n身上数道大穴。\n"NOR,me,victim);
			effect = SKILL_D("dulong-dafa")->force_effect(victim->query_skill_mapped("force"));
			if(random(me->query("combat_exp")+victim->query("combat_exp"))>victim->query("combat_exp")
			&& !random(effect))
			{
				message_vision(HIY"一股阴柔的指力随之侵入$n的周身大穴。\n"NOR,me,victim);
				victim->apply_condition("fx_busy",1+random(5-effect));
				me->start_perform(1+random(3),"「指力点穴」");
			}
			else
			{
				message_vision("$n不慌不忙，运起体内"+(effect>0?"纯阳":"雄浑")+"真气，$N灌注的内力竟然丝毫不起作用！\n"NOR,me,victim);
				me->start_perform(1+random(2),"「指力点穴」");
			}
		}
	}
}

void san_du(object me,object victim,object weapon,int damage)
{
	int effect;

	if(!victim->is_fighting(me)
	||  victim == me
	||  victim->is_ghost()
	|| !living(victim) 
	//||  me->query("env/化骨绵掌")!= "散毒"    // 如果不想用，也不勉强。
	|| me->is_perform()
//	||  me->query_temp("sld/pfm")
	||  victim->is_busy()
	)
		return;

	if(me->query_skill("huagu-mianzhang",1)<100)
		return;

	if( damage > 0 )
	{
		if( objectp(me) && objectp(victim) )
		{
			message_vision(HIG"$N紧跟着掌心按住$n的心口，掌力急吐，掌心竟然现出碧绿的颜色。\n"NOR,me,victim);
			effect = SKILL_D("dulong-dafa")->force_effect(victim->query_skill_mapped("force"));
			if(random(me->query("combat_exp")+victim->query("combat_exp"))>victim->query("combat_exp")
			&& !random(effect))
			{
				message_vision(HIG"$n一个不留神被打了个正着。\n"NOR,me,victim);
				if(5-effect>0)
					{
						switch (me->query("env/散毒"))
						{
							case "qianli"  : victim->apply_condition("qianli_poison",2+random(5-effect));
									 break;
							case "ruanjin" : victim->apply_condition("7bug_poison",2+random(5-effect));
									 break;
							case "fugu"    : victim->apply_condition("fugu_poison",2+random(5-effect));
									 break;
							default	       : victim->apply_condition("snake_poison",2+random(5-effect));
									 break;
						}

					}
				me->start_perform(1+random(3),"「掌力散毒」");
			}
			else
			{
				message_vision("$n不慌不忙，运起体内"+(effect>0?"纯阳":"雄浑")+"罡气，$N掌心所带的毒气竟然无法侵入$n身周三尺！\n"NOR,me,victim);
				me->start_perform(1+random(2),"「掌力散毒」");
			}
		}
	}
}
