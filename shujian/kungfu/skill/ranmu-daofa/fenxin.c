// renmu-daofa 燃木刀法
// by hunthu 

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, string arg)
{
      object weapon, target;
      int i, j, z;       
     j = me->query_skill("ranmu-daofa", 1);
     z = me->query_skill("yijin-jing", 1)/10;
      i = me->query_skill("yijin-jing",1)/2;
      weapon = me->query_temp("weapon");  
      

      if( !target ) target = offensive_target(me);

      if( !target || !me->is_fighting(target) )
           return notify_fail("「焚心」只能在战斗中对对手使用。\n");

        if (!weapon || weapon->query("skill_type") != "blade"
       || me->query_skill_mapped("blade") != "ranmu-daofa")
           return notify_fail("你现在无法使出「焚心」绝技！\n");

        if (weapon->query("id") != "mu dao")
           return notify_fail("你没有木刀，无法使出「焚心」绝技！\n");

        if(me->query_skill("ranmu-daofa", 1) < 160 )
                return notify_fail("你的燃木刀法火候不够，使不出「焚心」绝技。\n");

        if(me->query_skill("blade", 1) < 140 )
                return notify_fail("你的基本功还不够娴熟，使不出「焚心」绝技。\n");

        if( (int)me->query_skill("force") < 200 )
                return notify_fail("你的内功等级不够，使不出「焚心」绝技。\n");

        if( (int)me->query_str() < 32)
                return notify_fail("你的膂力还不够强劲，使不出「焚心」绝技。\n");

        if( (int)me->query_dex() < 30)
                return notify_fail("你的身法还不够迅猛，使不出「焚心」绝技。\n");
 
       if(me->query_skill("yijin-jing", 1) < 170 )   
                return notify_fail("你的易筋经修为不够，无法使用「焚心」绝技。\n");  

       if(me->query_temp("ranmu")) 
       return notify_fail("你现在正在使用「焚心」绝技。\n"); 

       if (me->query_temp("fumo"))
        return notify_fail("你现在正在使用「金刚伏魔」神功。\n"); 

        if (me->query("neili") < 1000)
        return notify_fail("你的内力不够。\n");
        if (me->query("jingli") < 800)
        return notify_fail("你的精力不够。\n");
        me->add("neili", -300);
        me->add("jingli", -500);
        me->add_temp("apply/strength", z);
        me->add_temp("apply/attack", j); 
        me->add_temp("apply/damage", j);
        me->set_temp("ranmu", 1);
        call_out("check_fight", 1, me, z, j, i);
        message_vision(HIR"$N单掌合揖，突然爆吼一声，运起佛门至上金刚伏魔功，\n手中的木刀顿时化作一团火焰，激荡的炙流将$n团团围住！\n"NOR,me,target);
        return 1;
}

void remove_effect(object me, int j, int z, object weapon)
{
       
    me->add_temp("apply/strength", -z);
    me->add_temp("apply/attack", -j);
        me->add_temp("apply/damage", -j);
    me->delete_temp("ranmu");
    tell_object(me, HIR"你「焚心」绝技运行完毕，气回丹田");
    if (weapon && weapon->query("id") == "mu dao") {
        weapon->unequip();
        weapon->set_name("木头", ({ "mu tou" }));
        weapon->set("unit", "块");
        weapon->set("weapon_prop", 0);
        tell_object(me, "，手中的木刀变成了一块木头。\n" NOR);
    }
    else tell_object(me, "。\n" NOR);
}

void check_fight(object me, int z, int j, int i)
{
    object weapon;      

    if (!me) return;
    if(!objectp(weapon = me->query_temp("weapon"))
     || weapon->query("id") != "mu dao"
     || weapon->query("skill_type") != "blade")
    {
        remove_effect(me, j, z, weapon);
        return;
    }
    if (i < 1 || !me->is_fighting()) {
        remove_effect(me, j, z, weapon);
        return;
    }
    call_out("check_fight", 1, me, z, j, i-1);
}
string perform_name(){ return HIR"焚心"NOR; }