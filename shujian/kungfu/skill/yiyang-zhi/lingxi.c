//yiyang-zhi's perform lingxi
//灵犀一指
//keinxin@sj2

#include <ansi.h>
inherit F_SSERVER;
int qianlong_hit(object me, object target, object weapon, int damage);
 
int perform(object me, object target)
{       
        string msg;
        
        if( !target ) target = offensive_target(me);
 
        if( !target 
         || !target->is_character()
         || !present(target,environment(me)) )
                return notify_fail("「灵犀一指」？\n");
        if( !living(target) )
        	return notify_fail("对方已经晕过去了。\n");
 

 		if( !me->is_fighting(target) )
 			return notify_fail("你只能对战斗中的对手出「灵犀一指」。\n"); 
 	       
        if( me->query_temp("weapon") )
                return notify_fail("只有空手才能施展「灵犀一指」。\n"); 

        if( (int)me->query_skill("yiyang-zhi", 1) < 200 ||
            (int)me->query_skill("finger", 1) < 200 )
                return notify_fail("你有的功夫还不够娴熟，不会使用「灵犀一指」。\n");

        if(!me->query_skill("kurong-changong", 1))
           	if(me->query_skill("qiantian-yiyang", 1) < 200)
                	return notify_fail("以你现在的内功修为还使不出「灵犀一指」。\n");        
         
        

        if (me->query_skill_prepared("finger") != "yiyang-zhi" || 
            me->query_skill_mapped("finger") != "yiyang-zhi" )
                return notify_fail("你现在无法使出「灵犀一指」进行攻击。\n");      

        if( ((int)me->query("eff_qi")* 100 / (int)me->query("max_qi")) > 50 )
		return notify_fail("你没有到生死关头无法使出「灵犀一指」进行攻击。\n");      
	                                                                                         
      
        if( (int)me->query("max_neili") < 4000 )
                return notify_fail("你的内力修为太弱，不能使用「灵犀一指」！\n");

        if( (int)me->query("neili") < (int)me->query("max_neili")/2 )
                return notify_fail("你的真气不够！\n");
        
        if( (int)me->query("jingli") <= (int)me->query("max_jingli")/2 )
                return notify_fail("你的精力不够！\n");

        if ((string)me->query("class")=="bonze")
         	msg = WHT "\n$N忽然低唤了一声："+target->name()+",声音犹似在千重梦魔浮沉中气若游丝地传来。"NOR;    
	else 	msg = WHT "\n$N忽然大喝一声："+target->name()+",声音犹似晴空霹雳，震的双耳”嗡嗡“做响。"NOR; 
        tell_object(target, WHT"你只觉眉心印堂间有一股力量像要把自己的双眉撕裂一般。\n"NOR);

        
        message_vision(msg, me, target);
        
        
        me->set("neili",0);

 	me->start_call_out( (: call_other, __FILE__, "main", me, target :), 3);

       	return 1;
}


int main(object me, object target)
{ 
        int i;
        mapping action;
	        
        if( !me ) return 0;
         
        if( me->is_ghost() || !living(me) ){    
        	me->delete_temp("yyz_ql");
                return 1;
        }
        if( !me->is_fighting() ) return 0;

	if( !target || !living(target) || environment(target) != environment(me) || !me->is_fighting(target) ){
		write("你才发觉对手已经没有了。\n");
		return 1;
	}
	
        if( me->query_temp("weapon") ){
		write("你得放下武器才能出「灵犀一指」啊。\n");
		return 1;
	}
        
        if( ((int)me->query("eff_qi")* 100 / (int)me->query("max_qi")) > 50 ){
		write("「灵犀一指」是拼命招数，你留到关键时刻用吧。\n");
		return 1;
	}




        message_vision(RED "$N受伤极重，急忙竭力抵挡，突然之间，$N眉心穴一阵滚热，自玄关热流直沉任脉，而照流连接督脉，两股异流迅速周折一大周天后，在带脉合流为一，在冲脉化流为劲，$N本来一招即出，竟中途易招为指“吱”的一声，指风破空而出！\n\n"NOR, me,target); 
 
         if (random(me->query("combat_exp"))> target->query("combat_exp")/3 ){                  
                message_vision(RED "\n$n见到$N忽然使出一招一阳指，精妙绝伦，指风本来甚为轻微，一旦遇自己的护身真气，骤改为锐劲，“波”地一声，戳破而入，$n一怔之下，\n"
                +"指风已直逼眉心，$n应变奇速，左掌叠在右掌之后，右掌掌心外吐，左掌掌背格在额前，“啪”的一声，指风射人他掌心内。$n右掌已运聚全力，\n"
                +"抗拒指风，左掌又加以支撑，但那一缕指风，连闯三关，所发的破空之声一次比一次更烈，仍然有一小部分内劲透进眉心要穴。\n"NOR, me, target);        
                target->apply_condition("no_exert", target->query_condition("no_exert") + 1);
                target->apply_condition("no_perform", target->query_condition("no_perform") + 1);
                target->unconcious();
         message_vision(RED "$N这一指，耗尽了所有的元气，只觉的自己疲弱之极，整个人就像一株突然枯了的朽木一般。！\n\n"NOR, me,target);          
                me->unconcious();
          return 1;           
         }
                message_vision(HIC"可是$n看破了$N的招式,趁机发动进攻！\n" NOR,me,target);
                me->start_busy(4);
               
         return 1;     

}
