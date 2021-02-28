// zongzi.c 棕子

inherit ITEM;
//inherit F_FOOD;

void create()
{
       set_name("粽子", ({"zong zi","zongzi", "zong"}));
       set_weight(150);
       if (clonep())
               set_default_object(__FILE__);
       else {
               set("long", "一个香喷喷的棕子，据说第一个吃的人会减少1％经验值。\n");
               set("unit", "个");
               set("value", 100);
               //set("food_remaining", 3);
               //set("food_supply", 30);
       }
}

void init()
{
       add_action("do_drink", ({"eat","chi"}) );
}

int do_drink(string arg)
{
        object me = this_player();
        object ob = this_object();

        if (!arg || !id(arg))
                return 0;	
        message_vision("$N将粽子吃得干干净净。\n",me);
        me->add("food", 500);
	me->add("water",500);
	destruct(ob);
	return 1;
}