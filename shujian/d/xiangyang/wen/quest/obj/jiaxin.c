// Room: /d/huashan/jinshe/obj/xinjian1.c
// Date: Look 99/03/25

#include <ansi.h>
inherit F_UNIQUE;
inherit ITEM;
void setup()
{}
void create()
{
        set_name( "家信", ({ "xin jian"}));
        set_weight(200);
  set("treasure",1);
        set("unit", "封");
        set("long",RED
"\n“这是一封金蛇郎君留给妻子的家信，
\n恳请有缘人将此信交给吾至爱:温仪.
\n她住在襄阳城温家堡吟淼阁此事切勿让除
\n她之外的人知晓,要紧要紧。
\n得我金蛇锥交付与她,即可证明汝之身份
\n移动夹层(move ancheng)可以开启铁合上层，得到金蛇锥。”\n"
"\n"NOR);

                set("value", 1000);
                set("material", "paper");
                set("no_get", "这样东西不能离开那儿。\n");
        
}

