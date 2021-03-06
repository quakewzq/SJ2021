// shuangfei.c 双飞两虹影
// Created by snowman@SJ 18/03/2001

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

int is_pfm() { return 1;}

#define PFM_NAME 	"双飞两虹影"
string perform_name(){ return HIM+PFM_NAME+NOR; }

int perform(object me, object target)
{     
      	if( (int)me->query_skill("qingyin-jian",1) < 120 )
           	return notify_fail("你的清音剑法不够娴熟，不能使用" + PFM_NAME + "！\n");
      
      	if( (int)me->query_skill("sword",1) < 120 )
           	return notify_fail("你的基本剑法等级不够，不能使用" + PFM_NAME + "！\n");  
      
      	if( (int)me->query_skill("sancheng-gong", 1) < 120 )
           	return notify_fail("你的三乘功法等级不够，不能使用" + PFM_NAME + "！\n");

      	if (me->query_skill_mapped("force") != "sancheng-gong")
           	return notify_fail("你所使用的内功不是三乘功法。\n");

      	if( (int)me->query("max_neili") < 1000 )
           	return notify_fail("你的内力太弱，不能使用" + PFM_NAME + "！\n");
      
      	if( (int)me->query("neili") < 500 )
           	return notify_fail("你的内力太少了，无法使用出" + PFM_NAME + "！\n"); 
        
        return (int)call_other( this_object(), "main", me, target);
}

int main(object me, object target)
{
	object weapon;
	int modify, damage, ap, dp;
	string msg, *limbs, limb;
	
	if( !target ) target = offensive_target(me);
     
      	if( !target || !target->is_character() || !me->is_fighting(target) || !living(target) 
        || me->query("neili") < 500 || me->query("jingli") < 100 
        || environment(target) != environment(me) )
                return notify_fail("你目前无法使用「" + PFM_NAME + "」！\n");   
                	
	weapon = me->query_temp("weapon");
      	if (!weapon
       	|| weapon->query("skill_type") != "sword"
       	|| me->query_skill_mapped("sword") != "qingyin-jian" )
       		return notify_fail("你现在无法使用" + PFM_NAME + "！\n");      
       		
       	modify = (int)me->query("emei_pfm/qingyin") + (int)me->query_temp("apply/qingyin");

	ap = me->query("combat_exp")/100000 * me->query_skill("qingyin-jian",1) * me->query_dex();
       	dp = target->query("combat_exp")/100000 * target->query_skill("parry",1) * target->query_dex();
       	if (ap < 1) ap = 1;
       	if (dp < 1) dp = 1;
       	if( modify > 1 )
		ap += ( ap / 10 * modify );
		
	if( wizardp(me) && me->query("env/debug") )
		write("AP: " + ap +"，DP: " + dp +"，Modify: " + modify +"\n");
		
	me->add("neili", -350); 
      	me->add("jingli", -50); 
	msg = HIW"\n$N长啸一声，身子往高空升去，半空中身形急转，手中的" + weapon->name() + HIW"飞舞而出，内劲到处，闪出一明一晦两道光芒！\n";
	switch(modify){
		case 0:
		case 1: break;
		case 2..4: 
			msg += HIW"剑光反射下，恰似两道蒙蒙水雾中五彩缤纷的"HIG"彩虹"HIW"，一闪一闪，直袭$n！\n"; break;
		case 5..7: 
			msg += HIW"这光芒宛如水面上一派似雾非雾的"HIC"水珠"HIW"，飞腾于空中，跌落在水里，散向$n！\n"; break;
		case 8..10: 
			msg += HIW"四周树木花草瞬时无风自动，那光芒如惊涛拍石，发出阵阵的"HIB"轰鸣"HIW"，向$n汹涌拍击！\n"; break;
		default: msg += HIW"刹那间，那光芒来回交错穿插，如涛如瀑，激起飞花碎玉，「" + perform_name() + HIW"」已达绝境！\n"; break;
	}
	
      	message_vision(msg+NOR, me,target);
      	
      	me->add_temp("apply/attack", 50);
      	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
      	me->add_temp("apply/attack", -50);
      	
      	me->start_busy(1);
      	target->start_busy(1);
      	me->start_perform(7, PFM_NAME);
      	if( random(ap + dp) > dp ){
      		msg = HIY"\n$n连退数步，可始终摆脱不出这双飞绝技，$p把心一横，运功全身准备硬接了！\n"NOR;
      		if (target->query("neili") <= 50){
			tell_object(target, "你猛然发觉自己真气已然枯竭耗尽，无法运劲相抗了！\n");
			msg += RED"结果只听$n一声惨叫，被绞进了剑光之中，顿时全身血肉横飞，眼见是活不成了！！\n"NOR;
			target->receive_damage("qi", (int)target->query("qi")+1, me);
                	msg += "( $n"+eff_status_msg(1)+" )\n";   
			message_vision(msg, me, target);
			return 1;
		}
		else if( me->query("neili") * 3 < target->query("neili") ) {
			msg += HIR"不料$p内功深厚，这一碰之下，只受了点轻伤！！\n"NOR;
			damage = (int)me->query_dex() * (modify + 1);
			target->receive_damage("qi", damage, me);
			msg += "( $n"+eff_status_msg((int)target->query("qi")*100/(int)target->query("max_qi"))+" )\n";   
			message_vision(msg, me, target);
     			return 1;
     		}
     		else {
     			limbs = target->query("limbs");
        		limb = limbs[random(sizeof(limbs))];
     			damage = me->query_skill("sword") + (weapon->query("weapon_prop/damage") * 2);
     			damage += modify * (me->query_dex() * 4 + me->query_str() + me->query("jiali") );
     			if( me->query("neili") > target->query("neili") * 2 )
     				damage *= 2;
     			else if( me->query("neili") > target->query("neili")/2*3 )
     				damage += random(damage);
     			else if( me->query("neili") > target->query("neili") )
     				damage += random(damage/2);
     					
     			if( wizardp(me) && me->query("env/debug") )
				write("Damage: " + damage +"\n");

     			target->receive_damage("qi", damage, me);
     			target->receive_wound("qi", damage/2 + random(damage/2), me);
        		msg += damage_msg(damage, "刺伤") + 
        			"( $n"+eff_status_msg((int)target->query("qi")*100/(int)target->query("max_qi"))+" )\n"; 
        		msg = replace_string(msg, "$l", limb);
                   	msg = replace_string(msg, "$w", "双飞剑气"); 
                   	message_vision(msg, me, target);
                   	return 1;
                }
        }

        if( random(2) )
        	message_vision(YEL"\n$n注视着$N的每一个动作，突然一下弹起后跃，脱出了" + PFM_NAME + "的范围！\n"NOR, me, target);
        else {
        	msg = target->query_skill_mapped("dodge");
	     	if( !msg ) msg = "dodge";
             	message_vision("\n"+SKILL_D(msg)->query_dodge_msg(target, 1), me, target);
        }

	if( random(2) && me->is_fighting(target) ){
		me->add_temp("apply/attack", 50);
      		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
      		me->add_temp("apply/attack", -50);
	}

      	return 1;
}

int help(object me)
{
	write(HIG"\n\t清音剑法「" + perform_name() + HIG"」："NOR"\n");
	write(@HELP
			双飞两虹影，万古一牛心
			
	此乃戊戍六君子之一的刘光第的联语，用传神之笔描绘出“双桥清音”的
	风韵。清音阁黑白二水冲牛心石，是峨眉山十景之一，其惊涛拍石，激起
	飞花碎玉，洒珠喷雪，水面上一派似雾非雾的水珠，飞腾于空中，跌落在
	水里。阳光映射，双飞桥在蒙蒙水雾中恰似两道五彩缤纷的彩虹。此剑式
	的要点便在于领会这似雾似幻的境界，领会的越多，威力越大。
	
	要求：	
		清音剑法等级 120 以上；
		基本剑法等级 120 以上；
		三乘功法等级 120 以上；
		最大内力 1000 以上； 
		内力 500 以上。
HELP
	);
	return 1;
}

