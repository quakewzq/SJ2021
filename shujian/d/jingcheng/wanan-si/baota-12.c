#define FLOOR 12
#define SAVE_NPC "宋远桥"
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "宝塔十二层");
        set("long","这里是万安寺内宝塔的第十二层，戒备森严，一看就知道关押着重要人物。\n");
        set("exits", ([
                "down" : __DIR__"baota-11",
                "up" : __DIR__"baota-13"
        ]));
        setup();
}

#include "baota.h"