//xunlei.c

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
string perform_name(){ return HIY"迅雷诀"NOR; } 
int perform(object me, object target)
{
        object weapon;
				
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
	   		  return notify_fail("「迅雷诀」只能对战斗中的对手使用。\n");

        if( me->query_temp("xunlei_yushi"))
	  		   return notify_fail("你剑势未尽，不能再施展「迅雷诀」！\n");

        if((string)me->query_skill_mapped("sword") != "xunlei-jian" && userp(me))
           return notify_fail("你现在无法使用「迅雷诀」！\n");
                   
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
	  		   return notify_fail("你使用的武器不对。\n");

        if( (int)me->query("neili") < 800 )
	   		 	 return notify_fail("你的内力不够！\n");
				
				if( (int)me->query("max_neili") < 1500 )
	   		 	 return notify_fail("你的内力修为不够！\n");
	   		 	 
        if((int)me->query_skill("xuantian-wuji",1) < 140 )
           return notify_fail("你的玄天无极功还不够火候，使不出「迅雷诀」。\n");
           
        if( me->query_skill("xunlei-jian", 1) < 140 )
	    		 return notify_fail("你的迅雷十六剑未臻高妙境界，无法使用「迅雷诀」！\n");

if(me->query_skill("xunlei-jian",1) <450)
      me->start_perform(5,"迅雷诀");
        message_vision(HIR "\n$N手中"+weapon->query("name")+HIR"剑尖指向自己胸口，剑柄斜斜向外，怪异之极，竟似回剑自戕一般！\n\n"	 NOR, me,target);
me->delete_temp("xunlei");
        me->set_temp("xunlei",4);
        me->add("neili", -50);
        me->set_temp("xunlei_yushi",1);
        call_out("checking", 1, me, target);
        return 1;
}


void checking(object me, object target)
{

 	object weapon;
 	int i,k;
 	
 	if( !me )  return;
 		
 	if( !target ) target = offensive_target(me);
       
  if( !target || !(target->is_character()) || !(me->is_fighting(target)) ) {
			call_out("xunlei_end", 1, me);
		return; 
  }
  
  weapon = me->query_temp("weapon");

  if (!objectp(weapon = me->query_temp("weapon"))
    || (string)weapon->query("skill_type") != "sword") {
		tell_object(me, "\n你手中无剑，当下停止了迅雷诀的架势。\n" NOR);
			call_out("xunlei_end", 1, me);
		return;
	}
	else if ( weapon->query("weapon_prop") == 0 ) {
		tell_object(me, "\n你的"+weapon->name()+"已毁，无法持续「迅雷诀」的攻势！\n\n" NOR);
		call_out("xunlei_end", 1, me);

		return;
	}
	else if ( (int)me->query("neili") < 400  ) {
		message_vision(HIR"$N的内劲後继无力，不得不停止「迅雷诀」的攻势！\n" NOR, me,target);
        	call_out("xunlei_end", 1, me);
		return;
	}
	else if ( me->query_skill_mapped("sword") != "xunlei-jian" ) {
		tell_object(me, HIR "\n你转而施展其他剑法，无法再以「迅雷诀」攻敌！\n\n" NOR);
        	call_out("xunlei_end", 1, me);
		return;
	}
	else if ( me->is_busy() ) {
		tell_object(me, HIR "\n你现在动作不够灵活，无法继续维持「迅雷诀」攻势！\n\n" NOR);
		call_out("xunlei_end", 1, me);
		return;
	}
	else if (!me->is_fighting()) {
		tell_object(me,  "\n你现在没有和人过招，当下收回了「迅雷诀」的攻势。\n" NOR);
		call_out("xunlei_end", 1, me);
		return;
	}
	if( environment(target) != environment(me) ) {
		tell_object(me, "你见对方已经不在这里，当下停止了「迅雷诀」的攻势。\n");
		call_out("xunlei_end", 1, me);
		return;
	}
	else{

        if ( me->query_temp("xunlei") ==4 )message_vision(HIY"\n$N纵身近前，"+weapon->name()+HIY"陡然弯弯弹出，剑尖直刺$n，出招之快真乃为任何剑法所不及！\n" NOR, me,target);
        if ( me->query_temp("xunlei") ==3 )message_vision(HIW"\n$N伸指在"+weapon->name()+HIW"上一弹，剑声嗡嗡，有若龙吟，"+weapon->name()+HIW"颤处，剑锋来势神妙无方！\n" NOR, me,target);
        if ( me->query_temp("xunlei") ==2 )message_vision(HIG"\n$N陡然间大喝一声，"+weapon->name()+HIG"上寒光闪动，喝道：「"+target->name()+HIG"，可小心了！」\n" NOR, me,target);
        if ( me->query_temp("xunlei") ==1 )message_vision(HIR"\n只见$N随手挥剑，"+weapon->name()+HIR"颤处，前后左右，瞬息之间已攻出了四四一十六招！\n" NOR, me,target);
				me->add("neili", -100);
				
        i=me->query_skill("xunlei-jian",1);
if(!userp(me)) i = i /2;
        me->add_temp("apply/attack", i/2);
        me->add_temp("apply/damage", i/3);
        me->add_temp("apply/sword",  i/3);

        
        for(k = 0; k < 3; k++) {
                if (me->is_fighting(target))
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        }
        if (me->is_fighting(target))
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3); 
        
        me->add_temp("apply/attack", -i/2);
        me->add_temp("apply/damage", -i/3);
        me->add_temp("apply/sword",  -i/3);


        if ( me->query_temp("xunlei") ==1 ) {
						message_vision(HIY "\n$N顺势圈转手中"+weapon->name()+HIY"，一十六手迅雷剑已然尽数使出！\n" NOR, me, target);      	
        		call_out("xunlei_end", 6, me);        		
					}
				else {
	  				me->set_temp("xunlei", me->query_temp("xunlei")-1);
	   				call_out("checking", 4, me, target);
	  		 }  
      }


}  

void xunlei_end(object me)
{
    int i;
    if (me) {
        tell_object(me, HIW "\n你暗自调息，渐渐平复腾涌的真气。\n\n" NOR);
        i = (4 - me->query_temp("xunlei")) / 2;
        if (i<0) i = 0;
        me->start_busy(i+random(2));
        me->delete_temp("xunlei");
        me->delete_temp("xunlei_yushi");				
		}		
}

int help(object me)
{
        write(HIY"\n「迅雷诀」："NOR"\n");
        write(@HELP
        迅雷十六剑以其快、狠诸称，尤其是其速度,号称四处只见剑影不见人
        影。这「迅雷诀」则是将迅雷十六剑快、狠充分发挥的剑诀。

        要求：  最大内力 1500 以上；
                当前内力 800 以上；
                迅雷十六剑等级 140 以上；
                玄天无极功等级 140 以上；
                
HELP
        );
        return 1;
}


