// By Spiderii 
inherit ITEM;
#include <ansi.h>
void create()
{
       set_name(HIW"深色包袱"NOR, ({ "shense baofu", "bao fu" }) );
       set_weight(100);
       if( clonep() )
               set_default_object(__FILE__);
      else {
               set("unit", "个");
               set("long", "这是一个毫不起眼的深色包袱。\n");
               set("value", 100000);
               set("no_get",1);                 
               set("no_drop",1);
               
       }
       setup();
}
