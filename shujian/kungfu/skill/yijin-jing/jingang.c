// snowman 04/01/99
// Modified by snowman@SJ 28/09/2000
// Modified by olives@SJ 5/2/2001
// for exert jingang 的百毒不侵的bug
// By Spiderii增强效果，毕竟书里很NB的force
// By Server Fix 连续 Exert bug
#include <ansi.h>
void remove_effect(object me,int count);

int exert(object me)
{    
      if ( !me->is_fighting()||(me->query_skill("yijin-jing", 1)<=250))
                return notify_fail("你只能在战斗中使用「金刚不坏体神功」！\n");

      if( (int)me->query_skill("yijin-jing", 1) < 199 )
                return notify_fail("你的易筋经内功修为不够，无法使用「金刚不坏体神功」！\n");

      if (me->query_skill_mapped("force") != "yijin-jing")
                return notify_fail("其它内功有「金刚不坏体神功」吗？\n");

      if( (int)me->query_con() < 40 )
                return notify_fail("你的根骨太低，根本无法使用「金刚不坏体神功」！\n");
 
      if( (int)me->query("neili") < 1000 )
                return notify_fail("你目前的内力太少了，无法使用「金刚不坏体神功」！\n");   
    
      if( (int)me->query("max_neili") < 3800 )
                return notify_fail("你的内力修为这么差，还想使用「金刚不坏体神功」？\n");   
                                                                                
      if( me->query_temp("fanzhen"))
                return notify_fail("你正在运用「金刚不坏体神功」！\n");
       
      message_vision(HIY"\n$N突然深吸一口气，目露慈光，面带微笑，内力运转，竟使全身上下宝光流动，是「金刚不坏体神功」！\n\n" NOR, me);
      me->start_busy(1);
      me->set_temp("fanzhen", me->query_skill("yijin-jing", 1)/2);
      me->set_temp("yjj/jg", me->query_skill("yijin-jing", 1)/2);
      me->set_temp("no_skill_hit_ob", 1);
      me->add_temp("apply/armor", me->query_skill("yijin-jing", 1)/2); 
      me->add_temp("apply/parry", me->query_skill("yijin-jing", 1)/2);
      me->add_temp("apply/attack", me->query_skill("yijin-jing", 1)/2);
      me->add("neili", -500);    
      call_out("remove_effect", 1, me, me->query_skill("yijin-jing", 1)/2+20);
      me->start_exert(2,"「金刚不坏体神功」");
      return 1;
}

void remove_effect(object me,int count)
{
        if( !me) return;
                if(me->query_temp("yjj/jg")) {
        if( count < 1 ){
            me->delete_temp("fanzhen");
            me->delete_temp("no_skill_hit_ob");
            me->start_exert(2,"「金刚不坏体神功」");
            me->add_temp("apply/parry", -me->query_skill("yijin-jing", 1)/2);
            me->add_temp("apply/attack",-me->query_skill("yijin-jing", 1)/2);
            me->add_temp("apply/armor", -me->query_skill("yijin-jing", 1)/2);
            message_vision(HIR"\n$N双手合十，散去了凝聚于全身上下的「金刚不坏体神功」。\n"NOR, me);    
            return;
        }
        else {
            call_out("remove_effect", 1, me,count -1);
            return;
        }
      }
}

int help(object me)
{
        write(HIY"\n易筋经之「金刚不坏体神功」："NOR"\n");
        write(@HELP
        金刚，坚利之意，历百劫千生，流转六道，而觉性不坏。即以金刚之坚，喻
        般若体；以金刚之利，喻般若用。金刚不坏体神功为少林第一大绝技，以易
        筋经为本，使神、体、气三者相融，循序渐进，持之以恒，便能抵御心魔，
        抗击外力。
        
        要求：  易筋经等级 200 以上；
                根骨 40 以上；
                最大内力 3800 以上；
                内力 1000 以上。
HELP
        );
        return 1;
}
