// mine.c 矿石
//Modified By ChinaNet
//By 2004/1/11

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR"神秘陨铁"NOR, ({"yuntie"}));
       
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("unit", "块");
                set("weight", 800);
                set("long",HIR"一块极其神秘的陨铁，据说从天而降。\n"NOR);
                set("no_get","这块矿石这么重，你搬不起来。\n");
                set("no_drop","别乱扔石头，砸到人怎么办？\n");
                set("material", "stone");
                set("value",10000+random(5000));
        }
        setup();
}
