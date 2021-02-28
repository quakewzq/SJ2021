// linglong.c 玲珑棒诀

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
    int ap,dp,damage,jl;
    object weapon;
    weapon = me->query_temp("weapon");
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("[玲珑棒诀]只能在战斗中使用。\n");

      if (!weapon || weapon->query("skill_type") != "stick"
       || me->query_skill_mapped("stick") != "dagou-bang")
      return notify_fail("你手里无棒，无法使用玲珑棒决！\n");
        if((int)me->query_int() < 25)
                return notify_fail("你悟性不够,不能使用[玲珑棒诀]！\n");

         if( (int)me->query_skill("huntian-qigong", 1) < 150 )
           return notify_fail("你的混天气功修为不够，使不出「玲珑棒诀」绝技。\n");
        //if (me->query_skill_mapped("force") != "huntian-qigong")
        //   return notify_fail("没有混天气功作为根基，是无法使出「玲珑棒诀」绝技的！\n"); 
       if((int)me->query_skill("dagou-bang",1) < 180)
       return notify_fail("你的打狗棒法修为不够,目前还不能使用「玲珑棒诀」！\n");
       if ((int)me->query_skill("bangjue",1)<150)
           return notify_fail("「玲珑棒诀」是以打狗棒诀为基础的，你棒决不熟如何使用？\n");
      if((int)me->query("max_neili") < 2000)
        return notify_fail("你内力修为现在不够, 不能用「玲珑棒诀」！\n");
       if ((int)me->query("neili")<800)
        return notify_fail("你内力用尽, 不能用「玲珑棒诀」！\n");
//           if( target->is_busy() )
//                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧ⅵ\n");
        me->start_perform(5,"「玲珑棒诀」");
        msg = HIY"$N轻声一笑，潇洒已极，双目精光四射，口中念念有词。\n";
        msg+="但见棒子化成了一团碧影，猛点$n后心“强间”、“风府”、\n";
        msg+="“大椎”、“灵台”、“悬枢”各大要穴。只要被棒端点中，非死即伤。\n"NOR;
      message_vision(msg, me, target);  
     ap=random(me->query("combat_exp"))+me->query_skill("bangjue",1)*(1+random(me->query("int")/2));
     dp= (int)target->query("combat_exp");
     if(ap>dp ) {
     damage=me->query_skill("dagou-bang",1)+me->query_skill("bangjue",1)*(1+random(me->query("int")/5));
     if (damage>3000)
         damage=3000;
     msg=CYN"$n叫声不好，势在不及回身招架，只得向前窜跃趋避，\n
     岂知$N的点打连绵不断，一点不中，又点一穴，棒影\n
     只在$n背后各穴上晃来晃去。$n一个疏神，连连中招!\n" NOR;
     target->receive_damage("qi",damage);
     target->receive_damage("jingli",damage/2);
     target->receive_wound("qi",damage);
    me->add("neili", -500);
    me->start_busy(2);
      message_vision(msg, me, target);
        } else if(ap>dp/2){
        msg = HIG "$N朗声诵道：[狗急跳墙如何打？ 快击狗臀劈狗尾。],\n";
        msg+=  "随之向$n下盘接连攻出数招\n" NOR;
           message_vision(msg,me,target); 
             for (jl=0;jl<3;jl++)
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
             me->start_busy(2);
        }
        else if(ap>dp/4){
        msg = HIG "$N悄声念道：[棒回掠地施妙手 ，横打双犬莫回头。], 随之棒影横掠而下，$n躲闪不及连中几下。\n";
                message_vision(msg, me, target);
 target->start_busy(4);
          }
         else {
               msg="$n早识得丐帮打狗神技[玲珑棒诀]的厉害,料敌机先远远逃了开去。\n";
          me->start_busy(random(5));
               message_vision(msg, me, target);
               }
          return 1;
}

