#define FLOOR 4
#define SAVE_NPC "张松溪"
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "宝塔四层");
        set("long","这里是万安寺内宝塔的第四层，戒备森严，一看就知道关押着重要人物。\n");
        set("exits", ([
                "down" : __DIR__"baota-3",
                "up" : __DIR__"baota-5"
        ]));
        setup();
}

#include "baota.h"