// shoes2.c
//
// This is the basic equip for players just login.

#include <armor.h>
#include <ansi.h>
inherit BOOTS;

void create()
{
        set_name(HIC"�ֲ�Ь"NOR, ({ "shoes" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "˫");
                set("material", "boots");
		set("armor_prop/dodge", 1);
       }
        setup();
}
