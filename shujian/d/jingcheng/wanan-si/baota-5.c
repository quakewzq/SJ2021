#define FLOOR 5
#define SAVE_NPC "唐文亮"
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "宝塔五层");
        set("long","这里是万安寺内宝塔的第五层，戒备森严，一看就知道关押着重要人物。\n");
        set("exits", ([
                "down" : __DIR__"baota-4",
                "up" : __DIR__"baota-6"
        ]));
        setup();
}

#include "baota.h"