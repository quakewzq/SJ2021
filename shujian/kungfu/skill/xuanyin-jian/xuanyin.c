#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        int lvl, j,i;
	object weapon;
	lvl = me->query_skill("xuanyin-jian", 1);

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target)
	|| !necessary(target) )
		return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ����������\n");

	if( me->query_skill("xuanyin-jian", 1) < 160 )
		return notify_fail("�����������������죬�޷�ʩչ����������\n");

	weapon = me->query_temp("weapon");

	if ( ! weapon 
	|| weapon->query("skill_type") != "sword"
	|| me->query_skill_mapped("sword") != "xuanyin-jian"
	|| me->query_skill_mapped("parry") != "xuanyin-jian" )
		return notify_fail("�������޷�ʩչ����������\n");

	if ( me->query_skill("jiuyin-zhengong", 1) < 160)
		return notify_fail("��ľ����湦��򲻹����޷�ʩչ����������\n");

	if ( me->query_skill("jiuyin-shenfa", 1) < 160)
		return notify_fail("��ľ���������򲻹����޷�ʩչ����������\n");

	if ( me->query("max_neili") < 2000)
		return notify_fail("��������������޷�ʩչ����������\n");

	if ( me->query("neili") < 1000)
		return notify_fail("��������������޷�ʩչ����������\n");

	if ( me->query("jingli") < 1000)
		return notify_fail("��ľ����������޷�ʩչ����������\n");

	message_vision(HIB"$Nʹ������������������Ѹ���ޱȵĹ���$n��\n"NOR,me, target);

	j = lvl /2;

	if ( lvl > 200 )
		j = to_int(lvl/200.0 * lvl/2.0);

        me->add_temp("apply/attack", j/6);
	me->add_temp("apply/sword", j);//ԭ����1
	me->add_temp("apply/damage", j);//ԭ����2 action@sj

        message_vision(HIB"$N����������һ����һ��������\n"NOR,me,target);
        i=0;
       
        if ((random(me->query_con()) > target->query_con()/3)
                                                                )
        {
        	message_vision(HIB"$n�������ˣ�����һƬ����֮�У�����˵�����ˡ�\n"NOR,me,target);
        	i=1;
        target->set_temp("must_be_hit",1);
        }
        else
        message_vision(HIB"$n�������ˣ������������ѣ�����˵�����ˡ�\n"NOR,me,target);
target->start_busy(2);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        
	if ( me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	if ( me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

        me->add_temp("apply/attack", -j/6 );
        me->add_temp("apply/sword", -j);//ԭ����1
        me->add_temp("apply/damage",-j);//ԭ����2

        me->start_perform(3+random(2), "����������");
	me->add("neili", -400);
	me->add("jingli", -150);
	if(i==1) target->start_busy( lvl/50 ); 
        target->delete_temp("must_be_hit");
	return 1;
}

string perform_name(){ return HIB"������"NOR; }

int help(object me)
{
        write(HIB"\n��������֮������������"NOR"\n\n");
        write(@HELP
        Ҫ��  ��ǰ���� 1000 ���ϣ�
                ������� 2000 ���ϣ�
                ��ǰ���� 1000 ���ϣ�
                ���������ȼ� 160 ���ϣ�
                �����湦�ȼ� 160 ���ϣ�
                ���������ȼ� 160 ���ϣ�
                ��������Ϊ����������
                �����м�Ϊ����������
                ���ֱֳ�����

HELP
        );
        return 1;
}