//by daidai
//木匣

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "木匣" NOR, ({"muxia", "mu xia", "xie"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
              set("unit", "个");
              set("long", HIG "这是一个檀木制成的小盒子，用来保存珍贵书籍。\n");
              set("value", 10000);
              set("unique", 1);
              set("treasure",1);
//              set("no_drop", 1);
              set("no_get", 1);
        }
        setup();
}


