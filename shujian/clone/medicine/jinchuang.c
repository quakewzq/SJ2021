// jinchuang.c 金创药

inherit COMBINED_ITEM;

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name("金创药", ({"jinchuang yao", "jin", "jinchuang", "yao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("value", 3000);
                set("unit", "些");
                set("long", "这是武林人士必备的金创药。\n");
                set("base_value", 5000);
                set("base_unit", "包");
                set("base_weight", 30);
        }
        set_amount(1);
}

int do_eat(string arg)
{
        if (!id(arg))
                return notify_fail("你要吃什么药？\n");
    if (this_player()->is_busy() || this_player()->is_fighting())
        return notify_fail("你正忙着呢。\n");
        if ((int)this_player()->query("eff_qi") == 
            (int)this_player()->query("max_qi"))
                return notify_fail("你现在不需要用金创药。\n");
        else {
       	        if( this_player()->query_condition("medicine")>0 )
	        	return notify_fail("你上一次服药的药性还没有过呢！\n");

                this_player()->receive_curing("qi", 50);
                message_vision("$N吃下一包金创药，气色看起来好多了。\n", this_player());
                add_amount(-1);
                this_player()->apply_condition("medicine",3);
        	this_player()->start_busy(1);
                return 1;
        }
}
