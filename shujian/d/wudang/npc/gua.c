#include <ansi.h>
inherit ITEM;
void setup()
{}
void init()
{
        add_action("do_eat", "fu");
        add_action("do_eat", "eat");
        add_action("do_eat", "chi");
}
void create()
{
        set_name(HIG"人参果"NOR, ({"renshen guo", "guo"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("long",
                "猪八戒曾经吃过的东西，看起来象一个白白胖胖的小男孩。\n"
                "有恢复体力，增加功力的神奇效果。\n");
                set("value", 1000);
        }
        setup();
}

int do_eat(string arg)
{
        object me = this_player();
        message_vision(HIB"
$N吃下一枚人参果，糟了……假的！\n\n"NOR,me);
        destruct(this_object());
        return 1;
}
