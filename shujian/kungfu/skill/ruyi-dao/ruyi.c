// ruyi.c
// action@SJ 2008/12/28
//modified by Zhuifeng@SJFY
#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	object weapon;
	int focus, i, j;

	focus = me->query_temp("ry/focus");
	weapon = me->query_temp("weapon");

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) 
	|| !living(target))
		return notify_fail("「如意六刀」绝技只能对战斗中的对手使用。\n");

	if( me->query_skill("ruyi-dao", 1) < 100 )
		return notify_fail("你的如意六刀等级不足，无法使用「如意六刀」绝技。\n");

	if( me->query_skill("blade", 1) < 100 )
		return notify_fail("你的基本刀法等级不足，无法使用「如意六刀」绝技。\n");

       	if(!wizardp(me) && (int)me->query_skill("bahuang-gong", 1) < 150 )
       	if(!wizardp(me) && (int)me->query_skill("beiming-shengong", 1) < 100 )
		return notify_fail("你的北冥神功等级不足，无法使用「如意六刀」绝技。\n");
                
	if( me->query("max_neili") < 1000 )
		return notify_fail("你的内力不足，无法使用「如意六刀」绝技。\n");

	if( me->query("neili") < 800 )
		return notify_fail("你的真气不足，无法使用「如意六刀」绝技。\n");

         

	if (!objectp(weapon = me->query_temp("weapon")) 
	|| weapon->query("skill_type") != "blade"
	|| me->query_skill_mapped("blade") != "ruyi-dao"
	)
		return notify_fail("你现在无法使用「如意六刀」绝技！\n");

	i = me->query_skill("ruyi-dao", 1);
       if(!userp(me)) i = i/3;

message_vision(HIC"\n$N一声长笑，反手将手中"+weapon->query("name")+HIC"挥出，$N只觉世间世事如意，豪气满胸，哪管什么是非荣辱，只觉飘逸非凡，心情豁达通畅！\n"NOR, me);

	j = i / 4;
        if ( i > 350 )
                j = to_int(i/ 4.0 * i/ 350.0);

	if ( focus > 15 ) focus = 15;

	j += 1 * focus;
 
  if (me->query("family/family_name") == "逍遥派") {             
	me->add_temp("apply/attack", j  );
};
  if (me->query("family/family_name") == "灵鹫宫") {             
	me->add_temp("apply/attack", j *2 );
		me->add_temp("apply/damage", j  );
};

	me->add_temp("apply/blade",  j * 2  );
	me->add_temp("apply/damage", j  );
	me->set_temp("ryd/ruyi",1);
	if(!userp(target)) target->add_busy(2);
	
		message_vision(MAG "\n$N手中"+weapon->query("name")+MAG"斜指，一招「如意拂相连」，反身一顿，一刀向$n的必救之处撩去！"NOR, me,target);
	  
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	if(me->is_fighting(target)) {
        message_vision(MAG "\n$N展身虚步，提腰跃落，一招「惟存负郭田」，刀锋一卷，拦腰斩向$n！"NOR, me,target);
	
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),  3);};

   if(me->is_fighting(target) && (int)me->query_skill("ruyi-dao", 1) > 100 ) {
        message_vision(MAG "\n$N一招「展转夜无眠」，"+weapon->query("name")+MAG"大开大阖，自上而下划出一个大弧，笔直劈向$n！\n"NOR, me,target);
	
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);};

 if (me->query("family/family_name") == "逍遥派") {
	me->add_temp("apply/attack", -j  );
};

  if (me->query("family/family_name") == "灵鹫宫") {             
	me->add_temp("apply/attack",- j *2 );
			me->add_temp("apply/damage",- j  );
};

	me->add_temp("apply/blade",  -j * 2 );
	me->add_temp("apply/damage", -j );
        me->start_perform(2+random(3), "如意六刀");
	me->add("neili", -200);
	me->add("jingli", -100);
	if( i > 220 && me->is_fighting(target)&& target->is_fighting(me) )
              call_out("perform2", random(2)+1, me, target); 
	return 1;
}

int perform2(object me, object target)
   {  
	int focus,  j;
	object weapon = me->query_temp("weapon");
	if(!me) return;
             j = me->query_skill("ruyi-dao", 1);
                   if(!userp(me)) j = j/2;
                
		focus = me->query_temp("ry/focus");
   	
	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) 
	|| !living(target))
		return notify_fail("「如意六刀」绝技只能对战斗中的对手使用。\n");


          me->add_temp("apply/attack", j / 4);
          me->add_temp("apply/blade",  j / 2 );
	  me->add_temp("apply/damage", j / 2);
	  me->set_temp("ryd/ruyi",1);
	if(!userp(target)) target->add_busy(2);
		if(me->is_fighting(target)&&!me->is_busy()) {
		message_vision(MAG "\n$N手中"+weapon->query("name")+MAG"一沉，一招「看书就枕边」，双手持刃拦腰反切，砍向$n！"NOR, me,target); 
	
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),  3);};

	   if(me->is_fighting(target)&&!me->is_busy()) {
		message_vision(MAG "\n$N一招「虚讶耳闻闲」，左脚跃步落地，"+weapon->query("name")+MAG"顺势往前，挟风声劈向$n！\n"NOR, me,target);
	
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),  3);};

     if(me->is_fighting(target) && (int)me->query_skill("ruyi-dao", 1) > 100 &&!me->is_busy()) {
		message_vision(MAG "\n$N挥舞"+weapon->query("name")+MAG"，使出一招「安车信有缘」，信手一刀，削向了$n！"NOR, me,target);
	
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);};


	me->add_temp("apply/attack", -j /4);
	me->add_temp("apply/damage", -j /2);
	me->add_temp("apply/blade",  -j /2 );

	me->add("neili", -200);
	me->add("jingli", -100);
	me->delete_temp("ryd/ruyi");
	me->start_busy(random(2));
	me->start_perform(3+random(3), "如意六刀");
}
string perform_name(){ return HIY"如意六刀"NOR; }

int help(object me)
{
        write(HIY"\n如意刀法之「如意六刀」："NOR"\n\n");
        write(@HELP
        要求：  当前内力 800 以上；
                最大内力 1200 以上；
                当前精力 500 以上；
                如意刀法等级 100 以上；
                北冥神功等级 100 以上；
                基本刀法等级 100 以上；
                激发刀法为如意刀法；
                激发招架为如意刀法；
                激发内功为北冥神功；
                且手持兵器。

HELP
        );
        return 1;
}
