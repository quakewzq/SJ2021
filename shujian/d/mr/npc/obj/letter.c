#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY"亲笔信函"NOR, ({ "xuanci letter","letter" }));
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "封");
                set("long",
                        "这是一封当今少林寺方丈的亲笔信函。\n");
                set("value", 0);
                set("no_get", 0);
                set("no_drop", 0);
         }
}

