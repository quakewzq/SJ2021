// gangdao.c

#include <weapon.h>
inherit BLADE;

void create()
{
	set_name("�ֵ�", ({ "blade" }));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�����λεĸֵ��������쳣������\n");
		set("value", 1000);
                set("rigidity", 1);
		set("material", "steel");
		set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
		set("unwield_msg", "$N�����е�$n��ص��ʡ�\n");
	}
	init_blade(30);
	setup();
}