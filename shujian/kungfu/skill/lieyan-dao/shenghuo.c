// guangming.c  圣火光明
// By River@SJ

#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return HIC"圣火光明"NOR; }

string *xue_name = ({ 
"劳宫穴","膻中穴","曲池穴","关元穴","曲骨穴","中极穴","承浆穴","天突穴","百会穴",
"幽门穴","章门穴","大横穴","紫宫穴","冷渊穴","天井穴","极泉穴","清灵穴","至阳穴",
}); 

string *limb=({
"颈部","后心","右腿","头部","小腹","胸口","腰间","裆部","右肩","右臂","右脚",
});

int perform(object me, object target)
{
	object weapon;
	int damage, p, ap, dp;
	string msg,name,dodge_skill,limbs;

	if(!target) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("「圣火光明」只能对战斗中的对手使用。\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	 ||(string)weapon->query("skill_type") != "blade")
		return notify_fail("你使用的武器不对。\n");
                
	if((int)me->query_skill("lieyan-dao", 1) < 100 )
		return notify_fail("你的烈焰刀法不够娴熟，不会使用「圣火光明」。\n");

	if ( !me->query_skill("jiuyang-shengong", 1))
	if ( me->query_skill("shenghuo-shengong", 1) < 100 )
		return notify_fail("你的圣火神功不够高，不能使用「圣火光明」。\n");
                        
	if((int)me->query_skill("piaoyi-shenfa", 1) < 100 )
		return notify_fail("你的飘翼身法不够高，不能使用「圣火光明」。\n");

	if( me->query_temp("qkdny/yin") )
		return notify_fail("你正在施展乾坤大挪移「引」字诀呢！\n");

	if( me->query_temp("qkdny/hua") )
		return notify_fail("你正在施展乾坤大挪移「化」字诀呢！\n");

	if((int)me->query("jingli", 1) < 300 )
		return notify_fail("你的精力修为不够，不能使用「圣火光明」。\n");

	if( me->query_skill_mapped("blade") != "lieyan-dao")
		return notify_fail("你现在的状态无法使用「圣火光明」。\n");

	if ((int)me->query("neili",1) < 800)
		return notify_fail("你的真气不够，无法使用「圣火光明」。\n");

	msg = HIC"\n$N大吼一声："HIR"为善除恶，惟光明故，喜乐悲愁，皆归尘土"HIC"。"+weapon->query("name")+HIC"和人合二为一，带着漫天杀气扑向$n。\n"NOR;

	ap = me->query("combat_exp", 1) / 1000 * me->query_skill("blade");
	dp = target->query("combat_exp", 1) / 1000 * target->query_skill("parry");

	if( random(ap + dp) > dp || !living(target)) {
		limbs= limb[random(sizeof(limb))];
		msg +=CYN"$n只觉得所有退路都被这逼人的杀气笼罩，避无可避，不由大惊失色，登时眼前一花，"+weapon->name()+CYN"已从其"+limbs+"洞穿而出！\n"NOR;
		damage = me->query_skill("blade");
		damage += me->query_skill("dodge");
		damage *= 3;
		damage += random(damage/2);
		if(damage > 3500) damage = 3500 + (damage-3500)/3;
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/3, me);
		me->add("neili", - 250);
		me->add("jingli", - 70);
		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "割伤");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "割伤");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		msg = replace_string( msg, "$w", weapon->name());
		msg = replace_string( msg, "$l", limbs);
		if( me->query_skill("yingzhua-shou",1 ) > 100
	 	 && me->query_skill_mapped("hand") == "yingzhua-shou"
		 && me->query_skill_prepared("hand") == "yingzhua-shou"
		 && ! target->is_busy()){
			name = xue_name[random(sizeof(xue_name))];
			msg += HIC"\n$N紧跟着上前一步，乘对方不备之际，左手变掌为鹰爪之势，自左向右抓向$n的"+name+"。\n"NOR;

			ap = me->query("combat_exp", 1)/ 1000 * me->query_skill("hand");
			dp = target->query("combat_exp", 1) / 1000 * target->query_skill("dodge");

			if( random(ap + dp) > dp || !living(target)) {
				me->add("neili", -100);
				target->add_busy( random(me->query_skill("yingzhua-shou", 1)/50) + 2);
				msg += CYN"结果$n的"+name+"被抓个正着，全身不由自主的一颤，顿时不可动弹。\n"NOR;
			}
			else {
				dodge_skill = target->query_skill_mapped("dodge");
				if( !dodge_skill ) dodge_skill = "dodge";
				msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
				me->add("neili", -50);
			}
			message_vision(msg, me, target);
			me->start_perform(3,"「圣火光明」");
			me->start_busy(random(2));
			return 1;
		}
	}
	else {
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
		me->add("neili", -100);
		me->start_busy(1);
	}
	message_vision(msg, me, target);
	me->start_perform(2,"「圣火光明」");
	return 1;
}

int help(object me)
{
        write(HIC"\n烈焰刀法「圣火光明」："NOR"\n");
        write(@HELP
        要求：  当前内力 800 以上；
                当前精力 300 以上；
                烈焰刀法等级 100 以上；
                飘翼身法等级 100 以上；
                圣火神功等级 100 以上；
                激发刀法为烈焰刀法。

        另外：
                鹰爪擒拿手等级 100 以上；
                激发手法为鹰爪擒拿手；
                备鹰爪擒拿手；
                有附加作用。

HELP
        );
        return 1;
}
