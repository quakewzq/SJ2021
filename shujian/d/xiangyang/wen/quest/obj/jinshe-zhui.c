inherit ITEM;
#include "/inherit/item/embed.h"
void create()
{
        set_name(HIY "金蛇锥" NOR, ({ "jinshe zhui", "zhui" }));

        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("damage", 3);
                set("embed", 1);
                set("unit", "枚");
             //   set("throw_msg", HIW"$N袖袍一挥，一枚冰魄银针自袖底飞出直向$n急射而去！\n"NOR);
                set("long", "这是一枚两寸来长，成蛇形的暗器。\n");
                set("unique", 20);
                set("value", 20000);
        }
        setup();
}



