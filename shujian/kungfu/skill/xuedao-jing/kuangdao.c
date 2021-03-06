//kuang.c -血刀「血影狂刀」
// Modified by Keinxin@SJ2
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
    int extra;
	object weapon;
    string msg;
	extra=me->query_skill("xuedao-jing",1)/3;
    if( !target ) target = offensive_target(me);
    if( !target||!target->is_character()||!me->is_fighting(target) )
    return notify_fail("你只能对战斗中的对手使用「血影狂刀」。\n");
    if( (int)me->query_skill("xuedao-jing",1) < 220)
    return notify_fail("你目前功力还使不出「血影狂刀」。\n");
    
    	
    	if (!objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "blade")
			return notify_fail("你使用的武器不对。\n");
	if( (int)me->query("neili") < 500 )
    return notify_fail("你的内力不够。\n");
    me->add("neili", -300);
    me->add_temp("apply/attack", extra);	
    me->add_temp("apply/damage", extra);
    
    	if(extra <= 80)
		msg = HIR"\n$N狂啸一声，以兵刃自砍手臂，顿时一飙鲜血飞溅在"NOR+weapon->query("name")+HIR"之上，"NOR+weapon->query("name")+HIR"隐隐泛出一层血色。";
	else
	if(extra <= 120)
		msg = HIR"\n$N狂啸一声，以兵刃自砍胸膛，顿时一腔鲜血飞溅在"+weapon->query("name")+HIR"之上，"NOR+weapon->query("name")+HIR"泛出一层血色！";
	else
		msg = RED"\n$N狂啸一声，当头砍了自己一刀，顿时一股鲜血飞溅在"+weapon->query("name")+RED"之上，"NOR+weapon->query("name")+RED"整个变的通红！！！";
    
        message_vision(msg, me, target);                


        if(me->is_fighting(target)){	
	msg = BBLU+RED  "血光一现！\n\n "HIC"$N足尖一点，一个倒翻单手撑地，一招「去魂电」，$w"HIC"一闪，自左而右，由右到左连出十刀。" NOR;
	COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
        
        }
        if(me->is_fighting(target)){
        msg = BBLU+RED  "刀山血海！！\n\n"HIW"$N怪叫一声，飞腾空中，一招「流星经天」，手中$w"HIW"脱手而出，疾射$n " NOR;
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
        
        }
        if(me->is_fighting(target)){   
        msg = BBLU+RED  "血海深仇！！！\n\n"HIB"$N脸色诡异，喉中“呵呵”低吼，一招「蛇行」，$w"HIB"灵动异常的在$n游走过去 " NOR;     
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
        
        }
        if(me->is_fighting(target) && me->query_skill("xuedao-jing",1) > 300){    
        msg = BBLU+RED  "血流成河！！！！\n\n"HIY"$N一招「三界咒」，手中$w"HIY"微微一抖，“嗤嗤嗤”三声轻响，向$n头、胸、腹连劈三刀。" NOR;    
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
        
        }
        if(me->is_fighting(target) && me->query_skill("xuedao-jing",1) > 340){   
        msg = BBLU+RED  "以血祭刀！！！！！\n\n"WHT"$N炸雷般大喝一声，一式「魔分身」$w"WHT"照$n搂肩带背斜劈下来，力道凶猛，势不可挡。" NOR;     
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
        }
    me->add_temp("apply/attack", -extra);	
    me->add_temp("apply/damage", -extra);
	me->start_perform(4,"血影狂刀");


    return 1;
}

