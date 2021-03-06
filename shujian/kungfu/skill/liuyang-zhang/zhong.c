// zhong.c 种生死符
//  edit by winter 2003.4
// edit by keinxin 2003.5 增加斗转星移的反弹
#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
       object obj,tar;
       string msg;
       int assi_int;
       int me_strike;
       int target_dodge;
       int me_bmsg,tar_bmsg;
       if( !target ) target = offensive_target(me);
       if( !target || !me->is_fighting(target) )
                return notify_fail("「生死符」只能在战斗中使用。\n");       
       if(!target)
             return notify_fail("你想给谁下生死符？\n");
       if(!objectp(tar = present(target, environment(me))))
            return notify_fail("这里没有你想对付的这个人。\n");
       if(!tar->is_character())
                return notify_fail("看清楚一点，那并不是生物,你真有个性。\n");
       if(!living(tar))
               return notify_fail(tar->name()+"都这样了，还要摧残他，不觉得太狠了?\n");
       if(tar==me) return notify_fail("你要给自己下？你不是自虐狂吧！\n");
       if(me->is_busy())
             return notify_fail("你先忙完再说拼命的事。\n");
       if(environment(me)->query("no_fight"))
                return notify_fail("在这里好像施展不开！\n");
       me_bmsg=(int) me->query_skill("beiming-shengong",1);
       tar_bmsg=(int) tar->query_skill("beiming-shengong",1);
       if(me_bmsg<140)
             return notify_fail("你的北溟神功不够娴熟，不能种生死符。\n");
       if( (int)me->query_skill("liuyang-zhang", 1) < 140 )
             return notify_fail("你的天山六阳掌不够娴熟，不能种生死符。\n");
       if( (int)me->query("neili", 1) < 500 )
             return notify_fail("你现在内力太弱，不能种生死符。\n");
       if (!objectp(obj=present("jiudai", me)))
             return notify_fail("你身上没有酒袋，不能化水为冰。\n");
       msg = HIC "$N左掌掌心中暗运内功，逆转北冥真气，将掌中酒水化成七八片寒冰，向$n飕飕飕连拍三掌。\n"NOR;
       me->start_busy(1);
       me_strike=random( (int) me->query_skill("liuyang-zhang",1) );
       target_dodge=random(target->query_skill("dodge") );
       assi_int=random(me->query("int")-target->query("int"))+ random(3);
       if( assi_int>1 && me->query_int()>50 )
            me_strike = me_strike*assi_int;
       if( me_strike > target_dodge && 
           me_bmsg >= tar_bmsg && 
           (int) random(me->query_skill("liuyang-zhang",1)) > (int) tar->query_skill("liuyang-zhang",1)/4            
       ){
             msg += HIW "$p觉得肩间"HIR"“缺盆穴”"HIW"上微微一寒，跟着小腹"HIR"“天枢穴”"HIW"、大腿"HIR"“伏兔穴”"HIW"、上臂"HIR"“天泉穴”"HIW"也觉凉飕飕地。\n" NOR;
             target->set("ss_poison/level",1);
             if( (int) me->query_skill("liuyang-zhang",1)> 180 )
             {
                msg += HIY "於是$p忙催掌力抵挡，忽然间后颈"HIB"“天柱穴”"HIY"、背心"HIB"“神道穴”"HIY"、后腰"HIB"“志室穴”"HIY"三处也是微微一凉。\n"NOR;
                target->set("ss_poison/level",2);
                target->receive_wound("qi",100 + random(30));
                target->receive_wound("jing", 60);
                target->apply_condition("ss_poison",  target->query_condition("ss_poison")+ 8);
             }
             target->receive_wound("qi",80 + random(10));
             target->receive_wound("jing", 50);
             target->apply_condition("ss_poison",  target->query_condition("ss_poison")+ 10);
             me->add("neili", -100);
             me->start_busy(2+random(2));
             target->set("ss_poison/count",0);
             target->set("ss_poison/bmsg",me_bmsg);
             target->set("ss_poison/id",me->query("id"));
       } else if( me_bmsg < tar_bmsg || 
                (int) me->query_skill("liuyang-zhang",1) < (int) tar->query_skill("liuyang-zhang",1) ||
                random((int) me->query_skill("liuyang-zhang",1)) < (int) tar->query_skill("douzhuan-xingyi",1)
              ){
                        //反弹
                    msg += HIB "可是$p经验老道，潜运北冥真气于全身，用同样的手法，向$P发出三掌!\n"NOR;
                    msg += HIY "$P大叫一声“不妙!”，结果发出的寒冰尽数打在自己身上。\n"NOR;
                    me->set("ss_poison/level",2);
                    me->receive_wound("qi",200 + random(30));
                    me->receive_wound("jing", 100);
                    me->apply_condition("ss_poison",  me->query_condition("ss_poison")+ 20);
                    me->add("neili", -100);
                    me->start_busy(3+random(2));
                    me->set("ss_poison/count",0);
                    me->set("ss_poison/bmsg",tar_bmsg);
                    me->set("ss_poison/id",tar->query("id"));
                  }else
              {
                 msg += "可是$p急忙闪在一旁，躲了开去。\n" NOR;
                 me->start_busy(3);
              }
    message_vision(msg, me, target);
    target->start_busy(1 + random(2));
    return 1;
}