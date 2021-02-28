// By Spiderii@yt bt物品
#include <ansi.h>
inherit SPEC;
void create()
{
        set_name(HIW"防具材料宝盒"NOR, ({ "abox","abaohe" }) );
        set_weight(10);
                set("unit", "个");
                set("long", "一个神秘的五彩盒子。\n是传说中天神遗落凡间的宝物，它是能给人们带来幸运和厄运的魔力之盒。\n是不是经不起它的诱惑呢，那就快打开（open）它吧。。。\n");
                set("value", 0);
                set("material", "wood");
                set("no_drop", "这样贵重的东西怎么能随便乱丢呢。\n");
                set("no_get", "这样东西不能离开那儿。\n");
                set("no_beg",1);
                set("no_steal",1);
                set("no_give",1);
                set_weight(100);
                set("value",3000000);
                //set("treasure",1);
                set("degree",1);
                set("flag","spec/abaohe");
                set("desc","据说打开盒子会有防具材料出现。");
                set("credit",1200);  

       setup();
}
void init()
{
        add_action("do_open", "open");
}

int do_open(string arg)
{        
       int i,j;
       object me = this_player();
       object obj;
       if(arg!="abox" && arg!="abaohe")
                    return notify_fail("你要打开什么?\n");
      i = 7+random(4) ; 
        obj = new("/d/zhiye/obj/buliao");
        if(obj && obj->set_level(i))
        {
                obj->move(me);
                message_vision(HIW"$N从防具材料宝盒中得到了一"+obj->query("unit")+obj->name()+"。\n\n"NOR,me); 
        }
                destruct(this_object());
                return 1;
                
}
