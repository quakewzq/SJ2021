// huashan-qigong.c  华山气功  By lsxk@hsbbs 2007/7/22

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { 
	  if (this_player()->query("family/family_name")=="华山派"|| this_player()->query("cw_mp/华山派")
 )
return usage == "force"; }

#include "force.h"

int valid_learn(object me)
{
        
        int lvl, i;
        lvl = (int)me->query_skill("huashan-qigong", 1);
        i = (int)me->query("shen", 1);

        if ( me->query("gender") == "无性" && lvl > 49)
                return notify_fail("你无根无性，阴阳不调，修炼正宗的华山气功?\n");

        if ( me->query("class") == "bonze" )
                return notify_fail("华山气功讲究阴阳调合，有违佛家六根清净之意，"
                        +RANK_D->query_respect(me)+"欲修此功，已是罪过。\n");

        if ((int)me->query_skill("force", 1) < 15)
                return notify_fail("你的基本内功火候还不够。\n");

        if ((lvl > 10 && lvl < 100 && i < lvl*lvl*lvl / 20 )
            || ( lvl >=100 && i < 10000))
                return notify_fail("你的侠义正气太低了，还好意思学习这华山气功。\n");

        return valid_public(me);
}

int practice_skill(object me)
{
       if((int)me->query_skill("huashan-qigong", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("huashan-qigong", (int)me->query("int"));
                   me->add("potential", -1*(1+random(3)));
                   me->add("neili", -100); 
                   return 1;
           }
           else return notify_fail("你现在的修为不足以提高华山气功了。\n");
       }
        else return notify_fail("华山气功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"huashan-qigong/" + func;
}

mapping exercise_msg(object me)
{
	return ([
            "status_msg" : WHT + me->name()+"盘膝正坐，引导内息在全身游走。"NOR,
            "start_my_msg" : WHT"你凝神静气，盘坐下来，运一口内家真气游走全身。\n"NOR,
            "start_other_msg" : WHT + me->name() +"坐了下来，双手捏了个剑诀，开始修炼内力。\n"NOR,
            "halt_msg" : WHT"$N忽然强运一口真气，双眼一睁，缓缓站了起来。\n"NOR,
            "end_my_msg" : WHT"你将内息游走全身，但觉全身舒畅，内力充沛无比。\n"NOR,
            "end_other_msg" : WHT""+me->name()+"轻轻呼了口气，微微一笑，站了起来。\n"NOR
	]);
}
