#define FLOOR 11
#define SAVE_NPC "灭绝师太"
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "宝塔十一层");
        set("long","这里是万安寺内宝塔的第十一层，戒备森严，一看就知道关押着重要人物。\n");
        set("exits", ([
                "down" : __DIR__"baota-10",
                "up" : __DIR__"baota-12"
        ]));
        setup();
}

#include "baota.h"