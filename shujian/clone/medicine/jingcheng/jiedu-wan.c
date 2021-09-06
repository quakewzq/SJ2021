#include <ansi.h>
inherit ITEM;

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name("解毒丸", ({"jiedu wan", "wan"}));
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("value", 3000);
                set("unit", "颗");
                set("long", "这是一颗解毒丸，可以有效的克制各种毒素。\n");
        }
}

int do_eat(string arg)                             
{
        object me = this_player();
        if (!id(arg))
                return notify_fail("你要吃什么？\n");
        if (me->is_busy())
                return notify_fail("你正忙着呢。\n");
        me->clear_conditions_by_type("poison");
        message_vision(HIY"$N吃下一颗解毒丸，体内所中之毒得到了缓解。\n"NOR, me);
        me->start_busy(1);
        destruct(this_object());
        return 1;
}