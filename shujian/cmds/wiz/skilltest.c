//maked by wzfeng 98 10 26
#include <combat.h>
#include <weapon.h>
#include <skill.h>
#include <ansi.h>
inherit F_CLEAN_UP;
int main(object me, string arg)
{
   object ob, second, first;
   int ap,dp;
   string attack_skill, martial_skill, first_skill;
   mapping action;
   if(!arg)
           return 0;
   
   ob = present(arg, environment(me));
   if(!ob)
           return 0;
   action = me->query("actions");
   if( !mapp(action))
   {
          tell_object(me,HIR"使用动作错误\n"NOR);
           return 0;
   }
   
   attack_skill=me->query("skill_type");
   ap =  COMBAT_D->skill_power(me, attack_skill, SKILL_USAGE_ATTACK);
   

           if( me->query_temp("weapon"))
           {
           tell_object(me,HIC"使用武器    :"+me->query_temp("weapon")->query("name")+"\t"NOR);
           tell_object(me,HIR"攻击类型    :"+me->query_temp("weapon")->query("skill_type")+"\n"NOR);
           }
           if(!action["skill_name"])
           tell_object(me,HIY"招式名称    :没有\n"NOR);
           else
           tell_object(me,HIY"招式名称    :"+action["skill_name"]+"\n"NOR);
           tell_object(me,HIC"招式级别    :"+action["lvl"]+"\n"NOR);
           tell_object(me,HIW HBGRN"招式招架    :"NOR+action["parry"]+"\n");
           tell_object(me,HIW HBBLU"招式轻功    :"NOR+action["dodge"]+"\n");
           tell_object(me,HIW HBCYN"招式加力    :"NOR+action["force"]+"\n");
           tell_object(me,HIW HBMAG"招式伤害    :"NOR+action["damage"]+"\n");
           tell_object(me,HIW HBRED"伤害类型    :"NOR+action["damage_type"]+"\n");
           tell_object(me,HIW HBRED"招式描述    :"NOR+action["action"]+"\n");
           tell_object(me,HIW HBRED"攻击力    :"NOR+ap+"\n");
           
   return 1;
}
int help(object me)
{
write(@HELP
指令格式 : skilltest <某人>
用来测试武功技能的强弱。
HELP
    );
return 1;
}

