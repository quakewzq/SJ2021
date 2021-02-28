// tiezhangxianglong
// updated by keinxin for sj2

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target)
{
	string msg;
	int extra;
	int i;
	object weapon;
	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("铁掌降龙只能对战斗中的对手使用。\n");
	 
    if( (int)me->query("neili", 1) < 600 )
		return notify_fail("你现在内力不足，不能使用！\n");	
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("「铁掌降龙」只能空手使用。\n");		

	if( (int)me->query_skill("tiezhang-zhangfa", 1) < 150 )
		return notify_fail("你的铁掌掌法不够娴熟，不能用铁掌降龙。\n");

	if( (int)me->query_skill("guiyuan-tunafa", 1) < 60 )
		return notify_fail("你的归元吐纳法不够娴熟，不能使用铁掌降龙。\n");

	extra = me->query_skill("tiezhang-zhangfa",1) / 20;
	extra += me->query_skill("guiyuan-tunafa",1) /20;
 i = extra/4;
    if( (int)me->query("neili", 1) <  (80 * i) )
		return notify_fail("你现在内力不足，不能使用！\n");	
        me->add_temp("apply/attack", extra*6);    
        me->add_temp("apply/damage", extra*2);
	msg = BBLU+HIC  "$N运起［归元吐纳法］，同时使出［铁掌降龙］一阵一阵的掌力，如潮水般的击向$n！" NOR;
       COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
        for(i=0;i<extra/4;i++)
	{
	
                switch(random(5))
                        {
                        case 0: { msg = BBLU+HIC "$N身形突转，身形如同在水上轻轻飘过，瞬然绕到$n身后，一掌轻轻拍出！\n" NOR;break;}
                        case 1: { msg = BBLU+HIC "$N突转身形倒转，猛然双掌拍出，排山倒海般地袭向$n！\n" NOR;break;}
                        case 2: { msg = BBLU+HIC "$N双手一错，一上一下向$n的胸口及丹田击到！\n" NOR;break;}
                        case 3: { msg = BBLU+HIC "$N使出铁掌擒拿手，看准$n的手腕，一把抓去！\n" NOR;break;}
                        case 4: { msg = BBLU+HIC "$N深吸了一口气，暗暗将师傅的秘传“天雷气”凝聚到双掌之中……\n" NOR;break;}
                        }	
	
	COMBAT_D->do_attack(me,target, weapon, TYPE_REGULAR,msg);
	}
i = extra/4;
        me->add_temp("apply/attack", -extra*6);
        me->add_temp("apply/damage", -extra*2);
me->start_busy(3);
me->add("neili", - 80 * i);
me->start_perform(20,"铁掌降龙");
	return 1;
}
