// by darken@SJ
// modified by Olives@SJ 5/4/2001
// 解决连续死的bug
// By Spiderii@ty更新效果
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include <combat_msg.h>

string perform_name(){ return HBBLU"【铁掌】"NOR; }
int perform(object me, object target)
{
        int p, j,h;
        string msg;
        j = me->query_skill("tiezhang-zhangfa", 1);

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
          || !me->is_fighting(target)
          || !living(target)
          || environment(target)!= environment(me))
                return notify_fail("「铁掌」只能在战斗中对对手使用。\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用「铁掌」！\n");

        if( (int)me->query_skill("tiezhang-zhangfa", 1) < 350 )
                return notify_fail("你的铁掌不够娴熟，使不出铁掌绝技。\n");

        if( (int)me->query_skill("guiyuan-tunafa", 1) < 350 )
                return notify_fail("你归元吐纳法不够，使不出铁掌绝技。\n");

        if( (int)me->query_skill("shuishangpiao", 1) < 350 )
                return notify_fail("你水上飘等级不够，使不出铁掌绝技。\n");

        if( (int)me->query("jiali") < 200 )
                return notify_fail("你加力不够，使不出铁掌绝技。\n");
/*
        if (me->query_skill_mapped("force") != "guiyuan-tunafa")
                return notify_fail("你所使用的内功不对。\n");
*/
        if( (int)me->query_str() < 60 )
                return notify_fail("你的膂力还不够强劲，使不出「铁掌」来。\n");

        if( (int)me->query_con() < 60 )
                return notify_fail("你的体格还不够健壮，使不出「铁掌」来。\n");

        if( (int)me->query_dex() < 60 )
                return notify_fail("你的身法还不够迅捷，使不出「铁掌」来。\n");

        if (me->query_skill_prepared("strike") != "tiezhang-zhangfa"
         || me->query_skill_mapped("strike") != "tiezhang-zhangfa"
         
         || me->query_temp("weapon"))
                return notify_fail("你现在无法使用「铁掌」！\n");

        if( (int)me->query("max_neili") < 7000)
                return notify_fail("你现在内力太弱，使不出「铁掌」。\n");

        if( (int)me->query("neili") < 5000 )
                return notify_fail("你现在真气太弱，使不出「铁掌」。\n");

        j *= 7;
        j += me->query("jiali")*8;
        j -= target->query_con()*10;
        j = j + random(j/4);

h = target->query("str");
if (h < 50) h =  target->query("con");
if (h < 50) h =  target->query("dex");
if (h < 50) h =  target->query("int");


        msg = HBBLU "\n$N将毕生功力聚集于掌上，丝毫无任何花巧，平平的向$n慢慢推去。\n"NOR;
        msg+= HBBLU "$n全身四周已全被这掌力封住，只得硬碰硬挡下这一招。\n"NOR;

if(h <50)  if (random(me->query_str()) > target->query_str()/3
        &&  random(me->query_dex(1)) > target->query_dex(1)/3
        &&  random(me->query("neili")) > target->query("neili")/3
        &&  random(me->query_skill("force")) > target->query_skill("force") /3 )
        {
                msg += HBRED"$n被$N这一掌打的血肉模糊！\n"NOR;
                me->kill_ob(target);
                target->set_temp("last_damage_from", me);
                //target->set("max_qi", -1);这个写法诡异了一点点
                // darken老大，你写错了吧？
//晕了就算了。                target->set("eff_qi",-1);
                target->set("qi",-1);
//                 if (userp(target) && userp(me)) me->apply_condition("killer",200);

        }
         else
        {
                target->receive_wound("qi", j /3 );
                target->receive_damage("qi",j);
                msg += HBRED"只听$n一声惨嚎，想必受了极重的伤！\n"NOR;
        }
        p = (int)target->query("qi")*100/(int)target->query("max_qi");
        msg += "( $n"+eff_status_msg(p)+" )\n";
        me->add("neili", -2500-random(500));
        message_vision(msg, me, target);
if(userp(me) && me->query("env/damage"))             tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+ j+ WHT"点攻击伤害。\n"NOR); 
if(userp(target)&& target->query("env/damage"))      tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+ j+ WHT"点伤害。\n"NOR);
        me->start_busy(4);
        me->start_perform(7,"「铁掌」");
        return 1;
}

