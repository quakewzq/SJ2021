// OBJ : /d/wudang/obj/qiandai.c 铅袋
// By lius 99/8

#include <armor.h>
#include <ansi.h>

inherit BOOTS;

void create()
{
        set_name( WHT"铅袋"NOR, ({ "qian dai", "dai" }) );
        set_weight(6000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "副");
                set("long", "一副里面填充了铅块的条袋，是武当弟子练习轻功的辅具。\n");
                set("value", 6000);
                set("material", "boots");
                set("armor_prop/armor", 8);
                set("wudang",1);
set("wear_msg","$N拿出一副铅袋紧紧地绑在腿上。\n"NOR);
set("remove_msg","$N把铅袋从腿解取了下来，顿时觉得身轻如燕。\n"NOR);
        }
        setup();
}
