// Cuff��  ��ȭ������ȭ��̫�泤ȭ������ȭ�����ֳ�ȭ���˼�ȭ
// Claw��  �������֡�С�����֡�ӥצ������צ��
// Strike�������ơ��䵱���ơ�����������

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N������̧��һ�в�ȭ�ġ������ڡ�����׼$n��$l�ͻ���ȥ",
        "force" : 420,
        "attack": 130,
        "dodge" : 45,
        "parry" : 45,
        "damage": 80,
        "damage_type":  "����"
]),
([      "action": "$Nһ������ȭ�ġ��׺����᡹������������ת�ɹ��������������ɹ��֣���\n"
                  "��һ�����죬����$n$l",
        "force" : 512,
        "attack": 145,
        "dodge" : 10,
        "parry" : 75,
        "damage": 85,
        "damage_type":  "����"
]),
([      "action": "$N����һ�ݣ�ʩչС�����ֵ��ַ���˫�ֶ���$n$l���Ĺؽ�ֱֱץȥ",
        "force" : 410,
        "attack": 170,
        "dodge" : 35,
        "parry" : 35,
        "damage": 178,
        "damage_type":  "ץ��"
]),
([      "action": "$N��ȭ��������ȭת�ۻ��ţ�һ�����ֵ����ֳ�ȭͻȻ����������������������$n",
        "force" : 460,
        "attack": 150,
        "dodge" : 62,
        "parry" : 60,
        "damage": 90,
        "lvl"   : 30,
        "damage_type":  "����"
]),
([      "action": "ֻ��$N����������ʹ���˼�ȭ�еġ��˼�����ʽ����˫�ƶ���$n��$lƽƽ��ȥ",
        "force" : 480,
        "attack": 160,
        "dodge" : 40,
        "parry" : 40,
        "damage": 85,
        "damage_type":  "����"
]),
([      "action": "$N���һ����������$n����һ����������$n���ֻ�ȥ�����ǰ����Ƶ���ʽ",
        "force" : 510,
        "attack": 155,
        "dodge" : 30,
        "parry" : 30,
        "damage": 95,
        "damage_type":  "����"
]),
([      "action": "$N�������ߣ����ֻ��أ�����һ�����������Ƶġ��ο�̽צ����Ѹ������$n$l",
        "force" : 510,
        "attack": 150,
        "dodge" : 45,
        "parry" : 45,
        "damage": 110,
        "damage_type":  "����"
]),
([      "action": "ֻ��$N������ʽ��˫�ֽ��䵱�ɵ�����ʹ���ܲ�͸�磬���в���$n��$l",
        "force" : 460,
        "attack": 155,
        "dodge" : 160,
        "parry" : 160,
        "damage": 105,
        "damage_type":  "����"
]),
([      "action": "$NͻȻ����һԾ����˫������צ״������$n��$l��Ȼץȥ����Ȼ��ӥצ������ʽ",
        "force" : 470,
        "attack": 185,
        "dodge" : 60,
        "parry" : 60,
        "damage": 155,
        "damage_type":  "ץ��"
]),
([      "action": "ֻ��$N����һ����˫�ַ������ϱ�ΪȦ��һ��̫��ȭ�����֡�ֱ��$n��$l",
        "force" : 350,
        "attack": 90,
        "dodge" : 210,
        "parry" : 230,
        "damage": 65,
        "damage_type":  "����"
]),
([      "action": "ֻ��$N��ǰһ��������һ�Ǵ������ֻ�ס���̣�����˳��һ����ʩһ��ˤ���ֻ���$n",
        "force" : 520,
        "attack": 155,
        "dodge" : 41,
        "parry" : 37,
        "damage": 103,
        "damage_type":  "����"
]),
([      "action": "$Nһ��ת������$n���������ֽ�$n���α�ס�͵ĳ�����ˤȥ����Ȼ���ɹŵ�ˤ����ʽ",
        "force" : 560,
        "attack": 185,
        "dodge" : 75,
        "parry" : 60,
        "damage": 125,
        "damage_type":  "ˤ��"
]),
});

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("���ٻ���ȭ������֡�\n");

        if (me->query("int") < 25)
                return notify_fail("�����������̫��޷�ѧϰ�ٻ���ȭ��\n");

        if (me->query("dex") < 15)
                return notify_fail("������������������޷�ѧϰ�ٻ���ȭ��\n");

        if (me->query("max_neili") < 3000)
                return notify_fail("���������ΪԶԶ���㣬������ϰ�ٻ���ȭ��\n");

        if ((int)me->query_skill("force") < 400)
                return notify_fail("����ڹ������ǳ���޷�ѧϰ�ٻ���ȭ��\n");

        if ((int)me->query_skill("cuff", 1) < 120)
                return notify_fail("���ȭ���������ޣ��޷����ٻ���ȭҪ�衣\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("baihua-cuoquan", 1))
                return notify_fail("��Ļ���ȭ������㣬�޷���������İٻ���ȭ��\n");

        return 1;
}

int valid_enable(string usage) { return usage=="cuff" ||  usage=="parry"; }  

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("baihua-cuoquan", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)me->query("jingli") < 100 )
                return notify_fail("������������������Ϣһ�������ɡ�\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("������������ˡ�\n");

        me->receive_damage("jingli", 80);

        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("baihua-cuoquan", 1);

        if (damage_bonus < 150 || lvl < 150) return 0;

        if (damage_bonus / 6 > victim->query_con())
        {
                victim->receive_wound("qi", (damage_bonus - 100) / 3, me);
                return HIR "ֻ��$n" HIR "ǰ�ء����꡹һ�����죬������"
                       "�߹Ƕ��۵�������\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"baihua-cuoquan/" + action;
}