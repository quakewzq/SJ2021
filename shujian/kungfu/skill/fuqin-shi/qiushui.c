// qiufeng.c 白水秋风式
// Created by snowman@SJ 08/03/2001

#include <ansi.h>

inherit F_SSERVER;

int is_pfm() { return 1;}

#define PFM_NAME 	"白水秋风式"

string perform_name(){ return WHT+PFM_NAME+NOR; }

int perform(object me, object target)
{
      	if( !me->is_fighting() )
      		return notify_fail(PFM_NAME + "只能在战斗中对对手使用。\n");      

	tell_object(me, HIG"\n你凝神聚气，试图施展娥嵋绝迹「" + PFM_NAME + "」！\n"NOR);
	call_out("main", 1 + random(3), me, target);
	me->start_perform(4 , PFM_NAME);
	return 1;
}

int main(object me, object target)
{
	object weapon;
	
	if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) || !living(target) 
        || environment(target) != environment(me) )
                return notify_fail("你目前无法使用「" + PFM_NAME + "」！\n");   
      		
      	if( (int)me->query_skill("fuqin-shi",1) < 200 )
      		return notify_fail("你的抚琴式不够娴熟，不能使用「" + PFM_NAME + "」！\n");
      
      	if( (int)me->query_skill("whip",1) < 200 )
      		return notify_fail("你的基本鞭法等级不够，不能使用「" + PFM_NAME + "」！\n");  
      
      	if( (int)me->query_skill("sancheng-gong", 1) < 180 )
      		return notify_fail("你的三乘功法等级不够，不能使用「" + PFM_NAME + "」！\n");

      	if( (int)me->query("max_neili") < 3500 )
      		return notify_fail("你的内力太弱，不能使用「" + PFM_NAME + "」！\n");
      
      	if( (int)me->query("neili") < 1000 )
      		return notify_fail("你的内力太少了，无法使用出「" + PFM_NAME + "」！\n");   
                                                                                 
      	if( me->query_skill_mapped("force") != "sancheng-gong")
      		return notify_fail("你现在的内功无法支持使用「" + PFM_NAME + "」进行攻击。\n");
      		
        weapon = me->query_temp("weapon");
        if (!weapon || weapon->query("skill_type") != "whip"
       	|| me->query_skill_mapped("whip") != "fuqin-shi")
      		return notify_fail("你手里没有鞭，无法使用「" + PFM_NAME + "」！\n");   
      		
      	tell_object(me, HIG"你感觉体内真气一震，好了！\n"NOR);
      	me->set_temp("pfm/qiushui", 1);
	call_other( __DIR__"baishui", "main", me, target);
	if( me->query("neili") > 500 )
		call_other( __DIR__"qiufeng", "main", me, target);
		
	else tell_object(me, HIG"你再想跟着出秋风抚琴式，可发觉自己的内力不够用了！\n"NOR);
	me->delete_temp("pfm/qiushui");
      	me->start_perform(6 , PFM_NAME);
      	return 1;
}

int help(object me)
{
	write(WHT"\n抚琴式「" + PFM_NAME + "」："NOR"\n");
	write(@HELP
	娥嵋万年寺的山景四季宜人，尤其是秋天，每逢金秋，峨眉山下夏暑尚存，
	金顶三峰已初飘白雪，而位于中山地区的万年古刹，正处在一年中的黄金
	季节。寺内一池，名白水池，传为“唐李白听蜀僧浚弹琴处。”此地秋色
	格外有情，明方孝孺有“林放到池月，风吹入户云”的诗句，是娥嵋十景
	之一，名为「白水秋风」。当年郭襄女侠游山至此，观景有悟，创下了集
	动静刚柔为一体的「白水秋风式」两招。既可分使，也可和用。
	
	要求：	
		「秋风抚琴式」：
			抚琴式等级 100 以上；
			基本鞭法等级 100 以上；
			三乘功法等级 80 以上；
			最大内力 800 以上； 
			内力 300 以上；    
		「白水抚琴式」：
			抚琴式等级 120 以上；
			基本鞭法等级 120 以上；
			三乘功法等级 100 以上；
			最大内力 1200 以上； 
			内力 500 以上；    
		「白水秋风式」：
			抚琴式等级 200 以上；
			基本鞭法等级 200 以上；
			三乘功法等级 180 以上；
			最大内力 3500 以上； 
			内力 1000 以上；    
HELP
	);
	return 1;
}

