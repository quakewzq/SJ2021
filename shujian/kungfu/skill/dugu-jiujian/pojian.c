// pojian.c �ƽ�ʽ

#include <ansi.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, weapon2, target;
        int skill, ap, dp, damage;

//        if(me->query("family/master_id") != "feng qingyang"
//        && userp(me))
//           return notify_fail("�㲻�Ƿ�����ĵ��ӣ�����ʹ�þ��У�\n");

     
        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("lonely-sword",1);

        if( !(me->is_fighting() ))
            return notify_fail("���ƽ�ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
            return notify_fail("��ʹ�õ��������ԡ�\n");

        if (!objectp(weapon2 = target->query_temp("weapon"))
        || (string)weapon2->query("skill_type") != "sword")
            return notify_fail("�Է�û��ʹ�������ò��ˡ��ƽ�ʽ����\n");

        if( skill < 50)
            return notify_fail("��Ķ��¾Ž��ȼ�����, ����ʹ�á��ƽ�ʽ����\n");

        if( me->query("neili") < 50 )
            return notify_fail("��������������޷����á��ƽ�ʽ����\n");

        msg = HIC "$N�ٽ�������ĬǱ���¾Ž�֮���ƽ�ʽ��, ���ལ�⣬����
�̵�Ϯ��$n��\n";
        message_combatd(msg, me, target);

        damage = 10 + random(skill / 2);
        ap = me->query_skill("sword") + skill;
        dp = target->query_skill("sword") / 2;
        if( dp < 1 )
            dp = 1;
        if( random(ap) > dp )
        {
            if(userp(me))
                 me->add("neili",-50);
            msg = "$n��ʱ������ǰһ��������һ�飬����";
            msg += weapon2->name();
            msg += "���ֶ�����\n" NOR;
            me->start_busy(1);
            target->receive_damage("qi", damage);
            target->start_busy(1);
            weapon2->move(environment(me));
            if (weapon2->query("ownmake")==1)
            {
                weapon2->move(target);
                msg += "�ǿ���$n�������һ$n��һ�콫���������\n" NOR;
            }
		message_combatd(msg, me, target);
		COMBAT_D->report_status(target);
        }
        else
        {
            if(userp(me))
                 me->add("neili",-30);
            msg = "����$n������$N�Ľ�·�����̽�����" + weapon2->name()+
"��÷��겻͸��ʹ$N�ġ��ƽ�ʽ��û�������á�\n"NOR;
            me->start_busy(2);
		message_combatd(msg, me, target);
        }

        return 1;
}