#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
	 int extra;
	 object weapon;
        extra = me->query("death_times");
        if (extra>50) extra = 50;
	 if( !target ) target = offensive_target(me);
        if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
                return notify_fail("「"+HIY"亢"NOR+HIC"龙"NOR+HIW"无"NOR+HIR"悔"NOR+"」只能对战斗中的对手使用。\n");

               if( objectp(me->query_temp("weapon")) )
              return notify_fail("你必须空手使用「"+HIY"亢"NOR+HIC"龙"NOR+HIW"无"NOR+HIR"悔"NOR+"」！\n");
     
        if( (int)me->query_skill("xianglong-zhang", 1) < 220 )
                return notify_fail("你的降龙十八掌不够娴熟，无法施展出「"+HIY"亢"NOR+HIC"龙"NOR+HIW"无"NOR+HIR"悔"NOR+"」。\n");

        if (me->query_skill("huntian-qigong", 1)<220)
                return notify_fail("你的本门内功火候未到！\n");
                
        if(!me->query("xlz/wuhui"))
                return notify_fail("你还没有领会到降龙十八掌最厉害的武功。\n");                   
       
        if ( (int)me->query("max_neili") < 2000)
                return notify_fail("你的内力不够，无法施展出「"+HIY"亢"NOR+HIC"龙"NOR+HIW"无"NOR+HIR"悔"NOR+"」。\n");
                
        if ( (int)me->query("neili") < 1500)
                return notify_fail("你的真气不够，无法施展出「"+HIY"亢"NOR+HIC"龙"NOR+HIW"无"NOR+HIR"悔"NOR+"」。\n");
                 me->add_temp("apply/strength", extra);
                 me->add_temp("apply/attack", extra*6);
	         me->add_temp("apply/damage", extra*2);
	me->add("neili", -1000);
		 msg = HIR "\n\n$N想起自己平生遭遇过"+chinese_number(me->query("death_times"))+"次生死危亡。\n\n现在又处于生死关头。求生欲望大增。\n"HIW"双掌平平提到胸前，使出降龙十八掌的最后绝学「"+HIY"亢"NOR+HIC"龙"NOR+HIW"无"NOR+HIR"悔"NOR+HIW"」，排山倒海般推向$n！\n\n" NOR;
       	         message_vision(msg, me, target);                
	msg =  HIC  "$N脚下一转，突然欺身到$n身前，右掌斜转护住全身，左掌运劲一招「龙战于野」，猛然砍向$n的$l！" NOR;
	       if(me->is_fighting(target)) 
	       COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
	        
        msg =  HIB  "$N身形向前移动，双掌分使两式「双龙取水」，凌厉的掌风一左一右，但却不分先后，同时压向$n$l！" NOR;
               if(me->is_fighting(target))
               COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);

        msg =  HIY  "$N一招未完，一招又起，左掌回收，右掌向右横推，一招「见龙在田」，迅捷无比地劈向$n的$l！" NOR;
               if(me->is_fighting(target))
               COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
             	
        msg =  HIG "$N右掌聚成拳状，格开$n手臂，接着左掌向前推出，一招「潜龙勿用」，雄浑的掌力缓缓压向$n！" NOR;
               if(me->is_fighting(target))
               COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
              
        msg =  HIB  "但见$N左掌护胸，身体后转，背对$n，右掌紧跟着一摆，一招「神龙摆尾」拍向身后的$n！" NOR;
               if(me->is_fighting(target))
               COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
             	
        msg =  HIW "$N突然一跃飞起半空，身形旋转，双掌居高临下，一招「飞龙在天」直向身下的$n压去！" NOR;
               if(me->is_fighting(target))
               COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);

        me->add_temp("apply/strength", -extra);
        me->add_temp("apply/attack", -extra*6);
        me->add_temp("apply/damage", -extra*2);
        if( random(me->query("combat_exp")) > target->query("combat_exp")/4
		&& me->query("xlz/hang") && me->is_fighting(target))
	 {

 msg = HIR"\n\n\n$N咬紧牙关，双掌护身，心中默念降龙十八掌的口诀!"+HIY"亢"NOR+HIC"龙"NOR+HIW"无"NOR+HIR"悔!!"NOR+" ";
                msg += RED"\n结果「轰」地一声，$n全身气血倒流，口中鲜血狂喷而出！\n"NOR;
                target->receive_damage("qi",(int)me->query_skill("strike")*5);
                target->receive_wound("qi",(int)me->query_skill("strike")*5);
		target->receive_wound("jing", 10 + random(200));
                if (!target->is_busy()) target->start_busy(2);
		message_vision(msg, me, target);
                COMBAT_D->report_status(target);
	}
        me->start_busy(3);
        me->start_perform(10,"亢龙无悔");
        return 1;
}
