// book1.c �����˲�6
#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIW"��¥��ƪ"NOR, ({"jialouluo pian", "shu","book"}));
	set_weight(80);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "���������˲���֮��--��¥��ƪ��\n");
		set("unit", "��");
	     }
}
