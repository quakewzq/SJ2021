inherit ITEM;
#include <ansi.h>
void create()
{
       set_name(RED"呕血谱"NOR, ({ "ouxue pu", "pu", "ouxue" }) );
       set_weight(100);
       if( clonep() )
               set_default_object(__FILE__);
      else {
               set("unit", "本");
                 set("long", "这是一本呕血谱，是梅庄黑白子最想得到的东西。\n");
               set("value", 100000);
               set("no_give",1);
               set("treasure",1);
               set("no_put",1);
               set("no_drop",1);
               set("material", "jade");
       }
       setup();
}

