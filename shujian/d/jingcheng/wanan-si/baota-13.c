#define FLOOR 13
#define SAVE_NPC "空闻大师"
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "宝塔顶层");
        set("long","这里是万安寺内宝塔的第十三层，戒备森严，一看就知道关押着重要人物。\n");
        set("exits", ([
                "down" : __DIR__"baota-12",
        ]));
        setup();
}

#include "baota.h"