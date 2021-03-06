inherit F_SSERVER;

#include <ansi.h>
#include "/kungfu/skill/yiyang-zhi/liumai_msg.h";
#include "/kungfu/skill/eff_msg.h";
int perform(object me, object target)
{       
                
        if( !target ) target = offensive_target(me);  
        
        if(!me->query_skill("liumai-shenjian", 1)) return 0;  
  
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character()
           || !me->is_fighting(target) || !living(target) )
                return notify_fail("「六脉神剑」只能在战斗中使用。\n");
                
        if( objectp( me->query_temp("weapon")) )
                return notify_fail("只有空手才能施展「六脉神剑」。\n");

        if (me->query_skill_prepared("finger") != "yiyang-zhi" || 
            me->query_skill_mapped("finger") != "yiyang-zhi" )
                return notify_fail("「六脉神剑」以一阳指为根基,你不运起一阳指,怎么可以施展「六脉神剑」。\n");    
        
        if (me->query_skill_prepared("strike") == "kurong-changong")
                return notify_fail("「六脉神剑」劲力变化精微,你无法和枯荣禅掌同时使用。\n");
                      
        
        if((int)me->query_skill("yiyang-zhi", 1) < 160 || (int)me->query_skill("finger", 1) < 160)
                return notify_fail("你的指法基本功夫还不够娴熟，就想乱用「六脉神剑」？\n");

        if(me->query_skill("force")<250)
                 return notify_fail("以你现在的内功修为还使不出「六脉神剑」来。\n");        
                                
        if(me->query_skill("liumai-shenjian", 1) < 30)
                return notify_fail("你的「六脉神剑」修为太低。\n");        
      
        if( (int)me->query("max_neili") < 3000 )
                return notify_fail("你的内力修为太弱，根本使不出「六脉神剑」来！\n");
        if( (int)me->query("neili") < 1000 )
                return notify_fail("你的真气不够！\n");
                
        if(me->query_temp("start_6mai")) return notify_fail("你已经在运用六脉神剑的无形剑气了！\n");

       
        tell_object(me, HIW"\n你先行存念，然后鼓气出指，内劲真气勃发，开始运用六脉神剑！\n"NOR); 
        me->set_temp("start_6mai", 1);
        remove_call_out("check_6mai");        
        remove_call_out("checking");
        call_out("check_6mai", 1, me, target);
        call_out("checking", me->query_skill("liumai-shenjian", 1), me);
        return 1;
}
int checking(object me)
{
        if(me->query_temp("start_6mai")){
              me->delete_temp("start_6mai");
              tell_object(me, HIW"\n你内劲运行一周天，将六脉神剑的招数用了一遍！\n"NOR);
              remove_call_out("checking_6mai");
              remove_call_out("checking");
        } 
        return 1;
}
int check_6mai(object me, object target)
{
        string msg, *limbs, dodge_skill,limb;
        int lv, neili, ap, dp, damage, p, j;
        mapping act, *action;
        object wep; 
        lv = (int)me->query_skill("liumai-shenjian", 1);

       
 action = ({
([      "action" : liumai_msg[1+random(4)],
        "t_msg" : target_msg[1+random(2)],
        "damage" : 4,
        "lvl" : 0,
        "skill_name" : "少泽剑",
        "damage_type" : "刺伤"
]),
([      "action" : liumai_msg[6+random(4)],
        "t_msg" : target_msg[2+random(2)],
        "damage" : 5,
        "lvl" : 30,
        "skill_name" : "关冲剑",
        "damage_type" : "刺伤"
]),
([      "action" : liumai_msg[11+random(4)],
        "t_msg" : target_msg[4+random(2)],
        "damage" : 6,
        "lvl" : 60,
        "skill_name" : "商阳剑", 
        "damage_type" : "刺伤"
]),
([      "action" : liumai_msg[16+random(4)],
        "t_msg" : target_msg[6+random(2)],
        "damage" : 7,
        "lvl" : 90,
        "skill_name" : "中冲剑",
        "damage_type" : "刺伤"
]),
([      "action" : liumai_msg[21+random(4)],
        "t_msg" : target_msg[8+random(2)],
        "damage" : 4,
        "lvl" : 120,
        "skill_name" : "少冲剑",
        "damage_type" : "刺伤"
]),
([      "action" : liumai_msg[26+random(4)],
        "t_msg" : target_msg[10+random(2)],
        "damage" : 7,
        "lvl" : 150,
        "skill_name" : "少商剑",
        "damage_type" : "刺伤"
]), 
([      "action" : liumai_msg[random(sizeof(liumai_msg))],
        "t_msg" : target_msg[random(sizeof(target_msg))],
        "damage" : 7+random(4),
        "lvl" : 180,
        "skill_name" : "六脉神剑",
        "damage_type" : "刺伤"
]),
});

        if (lv >= 180) j = 6;
        else if (lv >= 150) j = 5;
        else if (lv >= 120) j = 4;
        else if (lv >= 90) j = 3;
        else if (lv >= 60) j = 2;
        else if (lv >= 30) j = 1;
        else j = 0;
        act = action[random(j)];
        damage = act["damage"];
        msg = act["action"];
        neili = (int)me->query("neili");        

         if(!objectp(target)||!target||environment(me)!=environment(target)||target->is_ghost()||!living(target) ){
                me->delete_temp("start_6mai"); 
                remove_call_out("checking");
                remove_call_out("checking_6mai");
                return 1;
        } 
        if(!living(me)||me->is_ghost()||!me->is_fighting()){
                me->delete_temp("start_6mai");
                remove_call_out("checking");
                remove_call_out("checking_6mai");
                return 1;
                }
        if(!me->query_skill("liumai-shenjian", 1)||!me->query_temp("start_6mai")){
                me->delete_temp("start_6mai");
                remove_call_out("checking");
                remove_call_out("checking_6mai");
                return 1;
                } 
        if( objectp( me->query_temp("weapon")))
                {
                me->delete_temp("start_6mai");
                remove_call_out("checking");
                remove_call_out("checking_6mai");
                return 1;
                }  
        
        if (me->query_skill_prepared("finger")!="yiyang-zhi"|| 
            me->query_skill_mapped("finger")!="yiyang-zhi"){
                tell_object(me,"你变换了武功，无法再使用「六脉神剑」进行攻击了。\n"); 
                me->delete_temp("start_6mai");
                remove_call_out("checking");
                remove_call_out("checking_6mai");
                return 1;
        } 
        if (me->query_skill_prepared("strike") == "kurong-changong") {
                tell_object(me,"你变换了武功，无法再使用「六脉神剑」进行攻击了。\n"); 
                me->delete_temp("start_6mai");
                remove_call_out("checking");
                remove_call_out("checking_6mai");
                return 1;
                }    
        if(neili < 500){
                tell_object(me,"你发现自己现在的真气太弱，已经不够使出「六脉剑气」了。\n");           
                me->delete_temp("start_6mai");
                remove_call_out("checking");
                remove_call_out("checking_6mai");
                return 1;
                }                    
        if(me->is_busy()){
                call_out("check_6mai", 1+random(8-j), me, target);
                return 1;
                }

        ap = me->query_skill("force")+me->query_skill("finger")+me->query_skill("dodge")+me->query_int();
        dp = target->query_skill("force")+target->query_skill("parry")+target->query_skill("dodge")+target->query_con();
        ap *= me->query("combat_exp")/1000;
        dp *= target->query("combat_exp")/1000;
        
        limbs = target->query("limbs");
        limb = limbs[random(sizeof(limbs))];
        msg = replace_string(msg,"$l",limb);
        message_vision(msg, me, target);
        tell_object(target, HIR+act["t_msg"]+NOR); 
        wep = target->query_temp("weapon");

        if(random(ap+dp)> (dp/(random(2)+1))){
             me->add("neili", -damage*25);
             damage *= (lv/2+me->query_skill("finger"))/3;
             damage += me->query("jiali")*(random(j)+1)/3;
             damage -= target->query_temp("apply/armor");
             damage -= target->query_temp("apply/parry")/2; 
             if (damage<0) damage=10;
             damage *=j;
             if(neili > target->query("neili")*2) damage += damage/2; 
             if(damage < me->query_skill("finger"))
                damage =me->query_skill("finger");   
             if(damage > 1500) damage = 1500 + random(damage-1500)/ 50;

//the target has a weapon in hand
             if(objectp(wep) && random(3) == 1){     
                   if(me->query("neili") < target->query("neili")){
                        me->start_busy(1);
                        msg = HIY"结果只听哐的一声，$n用手中$W"HIY"竟然接下了那$w！\n" NOR;                        
                        }
                   else if(me->query("neili") >= target->query("neili")*2){
                         if(wep->query("rigidity") >= 3){
                               me->start_busy(1);
                               wep->move(environment(target));
                               target->receive_damage("qi", 150);  
                               target->receive_wound("qi", 50);      
                               msg = HIW"结果只听啪的一声，$n拿捏不住$W"HIW"被脱手震飞，虎口也在猛烈撞击下震裂！\n" NOR;
                               target->reset_action();
                               }
                         else{ 
                                me->start_busy(1);
                                msg = HIW"结果只听拍的一声响，$n手中$W"HIW"为$N的$w所断，化为寸许的二三十截，飞上半空，闪出点点白光！\n" NOR;
                                msg = replace_string(msg, "$W", wep->name());
                                wep->unequip();
                                wep->move(environment(target));
                                wep->set("name", wep->query("name")+"碎片");
                                wep->set("value", 0);
                                wep->set("unit", "些");
                                wep->delete("long");
                                wep->set("weapon_prop", 0);
                                target->reset_action();
                                }
                        }       
                   else {       
                         if(wep->query("rigidity") >= 8){
                                me->start_busy(1);
                                msg = HIY"结果只听一声大响，$W"HIY"在$w的冲击下不住颤抖，飞花四溅！\n" NOR;
                                }
                         else{
                                me->start_busy(1);
                                wep->move(environment(target));  
                                msg = HIW"$n慌忙举$W"HIW"一挡，当的一声后，那"+wep->query("unit")+"$W"HIW"又被震飞！\n" NOR;
                                target->reset_action(); 
                                }
                         }
                   msg = replace_string(msg, "$W", wep->name());
                   msg = replace_string(msg, "$w", "无形剑气");          
                   message_vision(msg, me, target);
                   if(!me->is_fighting() || !target || environment(me) != environment(target)||target->is_ghost() || !living(target) ){
                        me->delete_temp("start_6mai");
                        remove_call_out("checking");
                        remove_call_out("checking_6mai");
                        return 1;
                } else call_out("check_6mai", 1+random(8-j), me, target);
                   }
             else{
                   target->receive_damage("qi", damage);
                   target->receive_wound("qi", damage/(2+random(2)));          
                   p = (int)target->query("qi")*100/(int)target->query("eff_qi");
                   msg = damage_msg(damage, act["damage_type"]);
                   msg += "( $n"+eff_status_msg(p)+" )\n";
                   msg = replace_string(msg, "$l", limb);
                   msg = replace_string(msg, "$w", "无形剑气");          
                   message_vision(msg, me, target);
                   if(wizardp(me)) tell_object(me, "6mai_damage: "+damage+" \n");
                if(!me->is_fighting() || !target || environment(me) != environment(target)||target->is_ghost() || !living(target) ){ 
                        me->delete_temp("start_6mai");
                        remove_call_out("checking");
                        remove_call_out("checking_6mai");
                        return 1;
                } else call_out("check_6mai", 1+random(8-j), me, target);                   
                   }
            }
        else{
             me->start_busy(1);
//           HIY"$N全力向后一纵一闪，凶险万分地避开了那急速而来的无形剑气！\n"NOR, target);
             dodge_skill = target->query_skill_mapped("dodge");
             if( !dodge_skill ) dodge_skill = "dodge";
             message_vision(SKILL_D(dodge_skill)->query_dodge_msg(target, 1), me, target);
             if(!me->is_fighting() || !target || environment(me) != environment(target)||target->is_ghost() || !living(target) ){
                   me->delete_temp("start_6mai");
                   remove_call_out("checking");
                   remove_call_out("checking_6mai");
                   return 1;
                  } else call_out("check_6mai", 1, me, target);    
             }                               
       if(target->query("qi")*2 <= target->query("max_qi")
           && !target->is_killing(me->query("id"))
           && !me->is_killing(target->query("id"))){ 
             me->remove_enemy(target);
             target->remove_enemy(me);
             if (me->query("race") == "人类") {
                                if (!me->query("mute") && target->query("mute"))
                                        message_vision( winner_msg[random(sizeof(winner_msg)/2)], me, target);
                                        if (me->query("mute") && !target->query("mute"))
                                                message_vision(winner_msg[sizeof(winner_msg)/2 + random(sizeof(winner_msg)/2)], me, target);
                                        if (!me->query("mute") && !target->query("mute"))
                                                message_vision( winner_msg[random(sizeof(winner_msg))], me, target);
                        } else message_vision( winner_animal_msg[random(sizeof(winner_animal_msg))], me, target);
             }

       return 1;
} 