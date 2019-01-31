#include <armor.h>
inherit CLOTH;

void create()
{
	set_name("官服", ({ "guanfu", "cloth" }));
	set("long", "这是一件镇南王府的家将穿的青色官服，做工考究，上面用银丝绣着五彩翔云。\n");
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("material", "cloth");
		set("unit", "件");
		set("value", 0);
		set("armor_prop/armor", 10);
	}
	setup();
}
