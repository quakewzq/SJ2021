//cijian.c
//by spiderii@ty参照SJ编写

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int j, lvl = me->query_skill("tangshi-jianfa", 1);

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target)
	 || !living(target) )
		return notify_fail("「刺肩式」只能对战斗中的对手使用。\n");

	
    if( (int)me->query_skill("tangshi-jianfa", 1) < 180 ) 
                return notify_fail("你的躺尸剑法还未练成，无法使用「刺肩」字诀！\n");

    if((int)me->query_skill("sword", 1) < 180 )
                return notify_fail("你的基本剑法不够娴熟，不能使用「刺肩」字诀！\n");

    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "tangshi-jianfa")
                return notify_fail("你必须使用剑法，才能使出「刺肩」字诀!\n");

   if(me->query_skill_mapped("parry") != "tangshi-jianfa")
           return notify_fail("「刺肩」字诀需要使用躺尸剑法招架一切敌方攻击。\n"); 

   if((int)me->query("max_neili") < 3000 )
           return notify_fail("你内力修为尚浅，使不出「刺肩」字诀。\n");  

   if( (int)me->query("neili") < 1000 )
           return notify_fail("你现在真气太弱，使不出「刺肩」字诀。\n");
	
   message_vision(HIY"\n$N"HIY"轻轻念道：“孤鸿海上来，池潢不敢顾。”$N霎时之间如换人一般，身形沉稳，剑势飘逸！"MAG"！\n"NOR, me,target);


	j = lvl/2;
	me->set_temp("tangshi/cijian",3);
       me->add_temp("apply/attack", j);
       me->add_temp("apply/damage", j);
	
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0,3);

       me->add_temp("apply/attack", -j);
	me->add_temp("apply/damage", -j);

	me->delete_temp("tangshi/cijian");

	me->start_busy(random(2));
	me->add("neili", -300);
	me->add("jingli", -100);
	me->start_perform(4, "「刺肩式」");
	return 1;
}

string perform_name(){ return HIW"刺肩式"NOR; }

int help(object me)
{
        write(HIW"\n躺尸剑法之「刺肩式」："NOR"\n\n");
        write(@HELP
       躺尸剑法极其精妙的一招。

　　　　要求：　当前内力 3000 以上；
　　　　　　    最大内力 1000 以上；
　　　　　　　　躺尸剑法等级 180 以上；
　　　　　　　　基本剑法等级 180 以上；
　　　　　　　　激发招架为躺尸剑法。

HELP
        );
        return 1;
}
