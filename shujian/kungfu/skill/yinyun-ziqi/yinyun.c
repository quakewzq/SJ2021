//yinyun.c
//by snowman@SJ 03/06/99

#include <ansi.h>

string exert_name(){ return HIG"氤氲内聚"NOR; }

int exert(object me)
{
        int skill;

        if (!me->is_fighting())
                return notify_fail("你必须在战斗中才能运用氤氲内聚。\n");
        if (me->query_temp("yinyun"))
                return notify_fail("你已在运用氤氲内聚了。\n");

        if (me->query_skill("yinyun-ziqi",1) < 180
            || me->query_skill("force",1) < 180
            || me->query_skill("taoism",1) < 180 )
                return notify_fail("以你目前的修为来看，还不足以运用氤氲内聚！\n");

        if (userp(me) && me->query_skill_mapped("force") != "yinyun-ziqi")
                return notify_fail("你的内功不对，根本不能使出「氤氲内聚」。\n");                                                                                     
        if (userp(me) && me->query_skill_mapped("cuff") != "taiji-quan")
                return notify_fail("太极之「氤氲内聚」诀窍必须在激发太极拳的情况下才能使用。\n");
                
        if (me->query("max_neili") < 2500)
                return notify_fail("你的内力修为不够运用氤氲内聚所需！\n");
                
        if (me->query("neili") < 500)
                return notify_fail("你的内力不够运用氤氲内聚所需！\n");

        skill = me->query_skill("yinyun-ziqi", 1) + me->query_skill("taoism", 1);

        tell_object(me, HIW "\n你默运内功，将「氤氲紫气」的极限发挥出来，内聚运转于胸口大穴之上，确保心脉不死！\n" NOR);
        message_vision(MAG"\n$N提一口「氤氲紫气」，将气息运转于全身经脉之中，脸上渐渐显出紫色的流光！\n\n" NOR, me);
if(me->query("quest/wdjiuyang/pass")) {
                                     me->set_temp("title",HIR"太极宗师"NOR);
                                  me->set("title",HIR"太极宗师"NOR); }


        me->set_temp("yinyun", skill);
        
       if(random(me->query("kar"))>=15 && !me->query("quest/wdjiuyang/pass") ){
       	                      me->set_temp("quest/wdjiuyang/pass",1);
                message_vision(HIW"$N似乎领悟到了一丝武功中以柔克刚的至理，招数使得犹如行云流水，潇洒无比。\n"NOR, me);               
                       }
      
       if( time()-me->query("char_check") > 86400
            && me->query("kar") <31 
            && me->query("int")>=35
            && !me->query("quest/wdjiuyang/pass")
            && random(me->query("kar")) >=28
            && random(15)==1)
             { 
                                      me->set("quest/wdjiuyang/pass",1);
                                      me->set_temp("title",HIR"太极宗师"NOR);
                                      me->set("title",HIR"太极宗师"NOR);
                     message_vision(HIR"$N猛地里豁然贯通，领会了太极武功中以柔克刚的至理，忍不住仰天长笑。！\n"NOR, me);
 
 
 
 
            log_file("quest/wd9y",sprintf("%-18s成功解密武当大成，福：%d，悟：%d，纯：%d。\n",
                     me->name(1)+"("+capitalize(getuid(me))+")",
                     me->query("kar"), 
                     me->query("int"),
                     me->query("pur")  ), me  );            

      }
       	
       	
       	

        call_out("checking", 1, me);
        me->add("neili", -300);
     if(me->query_skill("yinyun-ziqi",1)<=350 )  
     	                  me->start_busy(random(2));
        return 1;
}

void checking(object me)
{
        if ( !me ) return;
        
        else if (me->is_ghost() || !living(me)){
                me->delete_temp("yinyun");
                }
        
        else if (!me->is_fighting() || me->query("neili") < 500 || me->query_temp("yinyun") <= 0 ) {
                message_vision("\n$N吐出一口淤气，脸上的紫色的流光也渐渐消失了。\n\n", me);
                me->delete_temp("yinyun");
me->delete_temp("quest/wdjiuyang/pass");
        }
	
        else if((me->query("eff_qi") < me->query("max_qi")/4*3) && me->query_temp("yinyun")){
        	me->add("neili", -50);
                me->receive_curing("qi", (me->query_skill("medicine",1)/3*2) + 10);
                me->add_temp("yinyun",-1);
                message_vision("$N全身紫光流动，将伤口处的流血自动止住了！\n", me);
                call_out("checking", 3, me);
        }
        
        else call_out("checking", 3, me);
        return;
}  

int help(object me)
{
	write(HIM"\n氤氲紫气「氤氲内聚」："NOR"\n");
	write(@HELP
	一羽不能加，蝇虫不能落，人不知我，我独知人。英雄所向无敌，盖皆由此
	而及也。氤氲内聚，以先天一口真气护身，乃道家一绝也！
	
	要求：	内功等级 180 以上；
		氤氲紫气等级 180 以上；
		道学心法等级 180 以上；
		最大内力 2500 以上；
		内力 500 以上。
           有一定几率"临时"触发武当“冲虚圆通”心法效果。
		有一定几率可以领悟武当“冲虚圆通”心法真谛。
		
		
		
HELP
	);
	return 1;
}

