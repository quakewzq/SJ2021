// wht-cloth.c thd 三代弟子穿

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIW"白色长袍"NOR, ({ "cloth" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","这是一件白色的长袍。\n");
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 20);
        }
        setup();
}
