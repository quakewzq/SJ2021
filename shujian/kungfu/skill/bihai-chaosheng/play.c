// play.c 碧海潮生曲
// Modified by Darken@SJ
// By Spiderii@ty 加入限制,对洗手ID无效果
#include <ansi.h>
inherit F_CLEAN_UP;

void playing(object *ob, int skill, int damage, object me);

string exert_name() { return HIG"碧海潮生曲"NOR; }

int exert(object me, object target)
{
        object *ob;
        object weapon;
        int skill, damage;
        if (me->query_skill("bihai-chaosheng", 1) < 100)
                return notify_fail("你的碧海潮生功还没到家。\n");
        if( environment(me)->query("no_fight") )
                return notify_fail("在这里不能攻击他人。\n");
        if (!weapon = me->query_temp("weapon"))
                return notify_fail("你要用什么来吹奏？\n");
        if (!weapon->id("xiao"))
                return notify_fail("你手里的兵器不是箫！\n");
        if( (int)me->query("neili") < 500 )
                return notify_fail("你的内力不够。\n");
        if ((int)me->query("age") < 20)
                return notify_fail("没结婚你就想吹箫,你当你是周星驰啊？\n");
        skill = me->query_skill("bihai-chaosheng",1);

        me->add("neili", -300);
        damage = skill;
        me->start_busy(3);
        me->start_exert(8,"碧海潮生曲");
        message_vision(HIM"$N幽幽咽咽地吹奏起“碧海潮生曲”来，曲调如泣如述，柔情万端。\n"NOR, me);
        ob = all_inventory(environment(me));
        call_out("playing",2, ob, skill, damage, me);
        return 1;
}

void playing(object *ob, int skill, int damage, object me)
{
        int i;
        ob = all_inventory(environment(me));

        if (!living(me) || me->is_ghost())
        {
                me->delete_temp("thd/play1");
                me->delete_temp("thd/play2");
                me->delete_temp("thd/play3");
                remove_call_out("playing");
                return;
        }
        for (i = 0; i < sizeof(ob); i++)
        {
                if (!living(ob[i]) || ob[i] == me || ob[i]->query("combat_exp")>me->query("combat_exp")*3/2 ||ob[i]->query("combat_exp")<= me->query("combat_exp")*2/3 )
                        continue;
                if (ob[i]->query("age") >= 16)
                {
                        if (ob[i]->query_skill("bihai-chaosheng",1)>50)
                                message_vision(HIW"$N对碧海潮生曲习以为常，没什么反应。\n"NOR, ob[i]);
                        if (ob[i]->query("no_pk"))
                                message_vision(HIW"$N已经金盆洗手了,箫声没有多大效果。\n"NOR, ob[i]);
                        else if (ob[i]->query("class") == "bonze" )
                        {
                                if (random(10)>6)
                                        message_vision(HIW"$N平时清心寡欲，箫声没有多大效果。\n"NOR, ob[i]);
                                else
                                {
                                        message_vision(HIR"$N被箫声扰的心烦意乱，失去了克制力。\n"NOR, ob[i]);
                                        if ((skill*20) > ((int)ob[i]->query("neili")/2))
                                        {
                                                if( damage > 0 )
                                                {
                                                        ob[i]->receive_damage("jing", damage + random(damage), me);
                                                        if( (int)ob[i]->query("neili") < (int)me->query("neili")*2)
                                                                ob[i]->receive_wound("jing", damage, me);
                                                                ob[i]->start_busy(3); 
                                                        message_vision(HIR"$N觉得面红耳赤，百脉贲张，心旌摇动，呼吸急促。\n"NOR, ob[i]);
                                                }
                                        }
                                }
                        }
                        else if (random((skill*20)) < ((int)ob[i]->query("neili")/2))
                        {
                                message_vision(HIY"$N运起内力抵抗箫声，没什么反应。\n"NOR, ob[i]);
                                ob[i]->add("neili",-skill*3);
                        }
                        else
                        {
                                if( damage > 0 )
                                {
                                        ob[i]->receive_damage("jing", damage+random(damage), me);
                                        if( (int)ob[i]->query("neili") < (int)me->query("neili")*2)
                                                ob[i]->receive_wound("jing", damage, me);
                                                ob[i]->start_busy(3); 
                                        message_vision(HIR"$N觉得面红耳赤，百脉贲张，心旌摇动，呼吸急促。\n"NOR, ob[i]);
                                }
                                if (userp(ob[i])) ob[i]->fight_ob(me);
                                else if (!ob[i]->is_killing(me)) ob[i]->kill_ob(me);
                        }
                }
                else
                        tell_object(ob[i], "你的年纪尚小，听了一阵，没有什么特别的感受。\n");
        }
        if (!me->query_temp("thd/play1") && me->query_skill("qimen-bagua",1)>=200)
        {
                message_vision(HBYEL"$N脚下踩着八卦方位，内息流动，曲调陡然拔高。\n"NOR, me);
                me->start_busy(3);
                me->set_temp("thd/play1",1);
                call_out("playing",3,ob,skill+random(skill/2), damage, me);
        }
        else if (!me->query_temp("thd/play2") && me->query_skill("taoism",1)>=200)
        {
                message_vision(HBMAG"$N精通道家练气之道，内息在丹田运转一周，曲调更是令人血脉奋张。\n"NOR, me);
                me->start_busy(3);
                me->set_temp("thd/play2",1);
                call_out("playing",3,ob,skill+random(skill), damage, me);
        }
        else if (!me->query_temp("thd/play3") && me->query_temp("thd/is_fast"))
        {
                message_vision(HBWHT"$N配合奇门五转身法，越走越快，曲调也越来越高，越来越细。\n"NOR, me);
                me->start_busy(3);
                me->set_temp("thd/play3",1);
                call_out("playing",3,ob,skill+random(skill), damage, me);
        }
        else
        {
                me->delete_temp("thd/play1");
                me->delete_temp("thd/play2");
                me->delete_temp("thd/play3");
        }
}

int help(object me)
{
        write(HIG"\n「碧海潮生曲」："NOR"\n");
        write(@HELP

        运使碧海潮生内力，使用箫吹奏出碧海潮生曲。此曲能影响听者的情绪，具
        体效果由吹奏者决定，轻则令人血脉奋张，心起绮念，重则令人不自主地狂
        舞不休，走火入魔而亡。

        要求：  碧海潮生等级 100 以上；
                最大内力 500 以上；
                奇门八卦等级 200 以上持续时间增加；
                道德经等级 200 以上持续时间增加；
                使用奇门五转时持续时间增加；
                对出家人效果减弱；
                对入世未深的年轻人效果减弱；
                对熟悉碧海潮生功者无效。
HELP
        );
        return 1;
}


