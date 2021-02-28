// 降龙十八掌
// by snowman@SJ
// Modify by Lklv for npc can't add gift
// Modify by Lane@SJ 2005.08.03 
// Update by lsxk@hsbbs 2007/7/3

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

#define KANGLONG "/kungfu/skill/xianglong-zhang/kanglong"

string perform_name(){ return WHT"降龙十八掌"NOR; }

int perform(object me, object target)
{
	int i, j, ap, dp, a, jiali;

	string ac, *msg = ({  "攻势不绝", "手腕一翻", "肘部一抬", "沉肩坠肘", "拧腰跨步", "拳随身转", });
	object *allenemy;
	
	i = me->query_skill("xianglong-zhang", 1);

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !me->is_fighting(target)
	 || !living(target)
	 || environment(target) != environment(me) )
		return notify_fail("「降龙十八掌」只能在战斗中对对手使用。\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("你必须空手才能使用「降龙十八掌」！\n");

	if( (int)me->query_skill("xianglong-zhang", 1) < 50)
		return notify_fail("你的降龙十八掌还不够娴熟，使不出「降龙十八掌」绝技。\n");

	if( (int)me->query_skill("huntian-qigong", 1) < 50 )
		return notify_fail("你的混天气功等级还不够，使不出「降龙十八掌」绝技。\n");

	//if( me->query_skill_mapped("force") != "huntian-qigong" )
	//	return notify_fail("你所使的内功不对，使不出「降龙十八掌」绝技。\n");

	if( (int)me->query_skill("force") < 50 )
		return notify_fail("你的内功等级不够，不能使用「降龙十八掌」。\n");

	if( (int)me->query_str(1) < 6 )
		return notify_fail("你的膂力还不够强劲，使不出「降龙十八掌」来。\n");

	if( me->query_skill_prepared("strike") != "xianglong-zhang"
	 || me->query_skill_mapped("strike") != "xianglong-zhang")
	 //|| me->query_skill_mapped("parry") != "xianglong-zhang")
		return notify_fail("你现在无法使用「降龙十八掌」！\n");

	if( (int)me->query("max_neili") < -1 )
		return notify_fail("你现在内力太弱，使不出「降龙十八掌」。\n");

	if( (int)me->query("neili") < -1 )
		return notify_fail("你现在真气太弱，使不出「降龙十八掌」。\n");

	if( (int)me->query("jingli") < 80 )
		return notify_fail("你的精力不足以让你使出「降龙十八掌」。\n");

       // if( (int)me->query_temp("xlz/xiao") && userp(me) && i<551 )
		//return notify_fail("你正在使用「降龙啸」。\n");

	//if( me->query_temp("xlz/py") )
	//	return notify_fail("你正在使用「降龙十八掌」。\n");

  // allenemy = me->query_enemy();
    //count = sizeof(allenemy);

   // message_vision(HBMAG+HIW "\n$N" HIR "吐气发音，纵声长啸，犹如轰隆隆一声雷响，正如神龙探首，在半空中猛起个焦雷霹雳！\n"
	//	+ "啸声未毕，只见$N" HIR "推出" + ((count>1)?"数":"一") + "掌，如雷声中夹着的狂风，以群龙奔腾、势不可挡之势攻向" 
	//	+ ((count>1)?"众人":allenemy[0]->query("name")) + HIR "！\n"NOR, me);
	
	message_vision(HBMAG+HIW "\n$N大喊一声，双臂环绕，双掌齐出。这门功夫正是洪七公之不传秘籍「降龙十八掌」！\n"
              HBMAG"降龙掌法中的"+ HIW +"降龙十八掌"+ NOR + WHT +HBMAG+"，此刻$N掌力大盛，当真了得！\n"NOR, me); 
//foreach (ob in all_inventory(environment(me))) {
	//ob->kill_ob(me);


	 me->set_temp("xlz/new",18);
	 me->set_temp("xlz/auto",1);
	 me->set_temp("xlz_auto",1);
	 me->set_temp("hit_ob_hit",1);
	 me->add_temp("apply/damage", 500);
	 me->add_temp("apply/strike", 500);
	 me->add_temp("apply/strength", 50);
	 target->set_temp("must_be_hit",1);
   
	for(a=0;a<18;a++)
{
	         target = offensive_target(me);
			 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
 		   
}


	me->delete_temp("xlz/auto");
	me->add_temp("apply/damage", -500);
	//me->add_temp("apply/attack", j);
	me->add_temp("apply/strike", -500);
	me->add_temp("apply/strength", -50);
	//me->add_temp("neili", 100000);
	me->reincarnate();
	return 1;
}
void remove_effect2(object me, int i)
{
	if (me)   me->add_temp("apply/dodge",- i /3);
                          
}





int help(object me)
{
	write(WHT"\n降龙掌「降龙十八掌」："NOR"\n");
	write(@HELP
	降龙十八掌为降龙掌有数绝技之最，一式十八招，招招克命。
	要求：	最大内力 200 以上；
		当前内力 150 以上；
		当前精力 80 以上；
		降龙掌等级 50 以上；
		混天气功等级 50 以上；
		内功有效等级 30 以上；
		膂力 6 以上：
		
HELP
	);
	return 1;
}
