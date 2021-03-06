// fengyun.c
// Modified by Lane@SJ 2005/4/14

#include <ansi.h>

int exert(object me)
{
	int improve;

	if( me->query("class") != "bonze" && me->query("family/generation") > 3)
		return notify_fail("你不是出家人，无法领会临济十二庄的「风云」字决！\n");
        
	if( (int)me->query_skill("linji-zhuang", 1) < 90 )
		return notify_fail("你的临济十二庄修为还不够。\n");

	if((int)me->query("neili") < 400 )
		return notify_fail("你的真气不够。\n");
        
	if( me->query_temp("ljz/fengyun") )
		return notify_fail("你正在运用临济十二庄的「风云」字决！\n");

	tell_object(me,MAG"你暗运风云两庄，心思浮云飘空之悠闲缓慢，默想狂风荡地之迅速紧急一股丹田热气分注四肢百骸，但觉身手敏捷了许多。\n"NOR, me);
	tell_room(environment(me), MAG"只见"+me->name()+"微闭双眼，身旁凝起一圈白雾，瞬息间一股旋风卷过，身形又复清晰。\n"NOR,({ me }));
	improve = (int)me->query("dex") ;
	me->add_temp("apply/dexerity", improve);
	me->set_temp("ljz/fengyun", improve);  
	me->add("neili", - 150);    
	me->start_exert(1 , "「风云」字决");
	call_out("remove_effect", 1, me, (int)me->query_skill("dodge")/3 );
	return 1;
}

void remove_effect(object me,int count)
{
	int i;
	if(!me || !me->query_temp("ljz/fengyun")) return;
	if( count < 1){
		i = me->query_temp("ljz/fengyun");
		me->add_temp("apply/dexerity", -i);
		me->delete_temp("ljz/fengyun");
		if ( living(me) && ! me->is_ghost()) 
			tell_object(me, HIR"你风云行功已久，略觉步履沉重了一些。\n"NOR);
		return;
	}
	call_out("remove_effect", 1, me,count - 1);
}

string exert_name(){ return MAG"风云字决"NOR; }

int help(object me)
{
        write(MAG"\n临济十二庄「风云字诀」："NOR"\n\n");
        write(@HELP
        要求：  当前内力 400 以上；
                临济十二庄等级 90 以上；
                出家或俗家三代弟子。
HELP
        );
        return 1;
}
