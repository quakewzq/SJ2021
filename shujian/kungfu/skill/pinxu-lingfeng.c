// pinxu-lingfeng.c ƾ���ٷ�

inherit SKILL;
string *dodge_msg = ({
"$n����һ�Σ�����һŤ��һ�С��Ǻ����𡹣����ض���\n",
"$nһ�С��辡�һ��ȵ׷硹��$Nֻ����ǰһ����������$n����Ӱ��\n",
"$nһ�С�ɨ�����Ʒ粻����������΢�Σ��о����յرܿ���$N��һ�С�\n",
"ֻ��$n�������һ����һ�С�����º�Ӱ�����󵴶�������һ�ԡ�\n" ,
"$nһ�С�����Ū��Ӱ�������䷭�ɣ����$N��һ�С�\n",
"ȴ��$n�����꽭��һ�طɡ����������һ�����ۣ��������ۡ�\n",
"����$nһ������ˮ�仨��ȥҲ��������һ�ã�$N��һ�����˸��ա�\n",
"ֻ��$nһ�С����ִ���ˮ�޺ۡ����������Σ����������ת���˳����ɿ��⡣\n",
"$nϢ�����������������һ�С���������Ӱ�ڲ���������ƮȻ����\n",
});

string query_dodge_msg(object me)
{	
	return dodge_msg[random(sizeof(dodge_msg))];

}

int valid_enable(string usage)
{ 
	return usage == "dodge"; 
}

int valid_learn(object me)
{ 
	return 1; 
}

int practice_skill(object me)
{
	if( (int)me->query("jingli") < 45 )
		return notify_fail("�������̫���ˣ������������貽��\n");	
	me->receive_damage("jingli", 35);	
	return 1;
}