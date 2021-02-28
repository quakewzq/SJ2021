// jiushi.c 九式合一

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;
string  *pfattack_msg = ({
                       HIW"「倒剑式」"HIM"$N突然将所有剑式倒转为施。但见$n顿时被逼得手忙脚乱，自己向$N的$W"HIM"撞将上来。\n"NOR,
                       HIW"「逆剑式」"HBCYN"$N将$W"HIW""HBCYN"交到左手，剑招变的左右颠倒。$n一时没有弄懂被刺个正着。\n"NOR,
                       HIW"「落剑式」"HIC"$N腾身而起，成头下脚上势，从空中攻向$n。$n防备不及结果被$N的$W"HIC"刺中。\n"NOR,
                       HIW"「摇剑式」"HBBLU"只见$N的$W"HIW""HBBLU"有如灵蛇一般左右迂回着。$n不知$W"HIW""HBBLU"要攻向自己的什么位置，站在原地发呆，结果被刺中。\n"NOR,
                       HIW"「荡剑式」"HIW"$N的剑招突然变得犹如风中柳絮，飘忽不定。$n只觉眼前一花，胸口已被刺中。\n"NOR,
                       HIW"「浪剑式」"HBGRN"犹如大海狂涛，又四面向$n压去。$n只觉置身于$N剑招形成的狂风暴雨之中，不知不觉已被刺中。\n"NOR,
                       HIW"「挫剑式」"HIB"$n与$N互相一搓身，只见$N将$W"HIB"轻轻一带。$n的小腹已中了$N的一剑。\n"NOR,
                       HIW"「离剑式」"HBYEL"只见$N手中$W"HIW""HBYEL"剑光暴长，闪电中甩出，急若流星飞向$n。$n躲避不及被$W"HIW""HBYEL"刺中。\n"NOR,
                       HIW"「剑气式」"HIG"$N手中$W"HIG"虚空一点，只见三丈之内剑气纵横连绵不绝袭向$n。$n急忙腾空而起但已经太晚，剑气已经贯胸而过。\n"NOR,
                       });

string *pfparry_msg = ({
                      NOR"$n看破了$N的企图，不慌不忙，一圈一点破解了$N的这招。\n"NOR,
                      NOR"$n腾身而起，$N的剑招险险从脚下擦过。\n\n"NOR,
                      NOR"$N突然从左方攻去一剑，不料$n身体轻轻向右飘出，化解了这招。\n"NOR,
                      });

int perform(object me, object target)
{
    int damage , zhao;
    string msg,wn;
    object weapon;
	

    if (!target ) target = offensive_target(me);
    
    if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("「九式合一」只能在战斗中使用。\n");    

    if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
        return notify_fail(RED"开什么玩笑，没装备剑就想使「九式合一」？\n"NOR);

    if (!target || !target->is_character() || !me->is_fighting(target) )
        return notify_fail("「九式和一」只能对战斗中的对手使用。\n");

    if ((int)me->query_skill("dugu-jiujian", 1) < 300 )
        return notify_fail(WHT"你独孤九剑不够娴熟，使不出「九式合一」。\n"NOR);

    if ((int)me->query("max_neili")<4000)
        return notify_fail(RED"你内力修为不足，无法运足内力。\n"NOR);

     

    if ((int)me->query("neili")<1800)
    {
        return notify_fail(HIC"你现在内力不够，没能将「九式合一」使完！\n"NOR);
    }
	
    me->start_perform(5,"九式合一");
    msg = HIW "$N手中"+weapon->query("name")+HIW"剑芒跃动，剑光暴长，剑尖颤动使出独孤九剑的，独门绝技\n"NOR;
    msg += HIR"「九式合一」"+HIW+"剑光左右飘忽，上下不定，直向$n卷去！\n"NOR;
	//┌㊣︻︻︻$▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▅▆▇▇◤
	message_vision(msg, me, target);
	for (zhao=0;zhao<9;zhao++)
	{ 

		if (random(me->query("combat_exp")) > (int)target->query("combat_exp")/3)

		{
			me->start_busy(3);
			if( !target->is_busy() )
			{
				target->start_busy(random(2));
			}
			damage = (int)me->query_skill("dugu-jiujian", 1) + (int)me->query_skill("sword", 1);
			damage = 100 + damage*19/10 + random(damage/10)+ me->query("jiali");
			damage = damage*19/10 + random(damage/10);
			damage = damage*15/10;
			
			
			
			if( !target || environment(target) != environment(me) ) 
			{
				tell_object(me, "太可惜了，你下手的目标已经走了。\n");
				return 1;
			}
			
			
			target->receive_damage("qi", damage);
			
			target->receive_wound("qi", damage/8);

			//msg += pfattack_msg[random(sizeof(pfattack_msg))];
			//msg += pfattack_msg[zhao];
			msg = pfattack_msg[zhao];
			me->add("neili", -damage/5);
			msg = replace_string(msg, "$W", weapon->query("name"));
			message_vision(msg, me, target);
			if(userp(me) && me->query("env/damage"))
				tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage+ WHT"点攻击伤害。\n"NOR);    
			if(userp(target)&& target->query("env/damage"))
				tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ damage+ WHT"点伤害。\n"NOR);
		} 
		else
		{
			me->start_busy(3);
	  
			//msg += pfparry_msg[random(sizeof(pfparry_msg))];
			msg = pfparry_msg[random(sizeof(pfparry_msg))];
			message_vision(msg, me, target);
	   }
		
		
	}
	//msg = replace_string(msg, "$W", weapon->query("name"));
    //message_vision(msg, me, target);

    if(!target->is_fighting(me)) target->fight_ob(me);
    return 1;
}
