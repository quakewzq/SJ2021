// /u/jpei/thd/kefang.c

inherit ROOM;
#include <ansi.h>
void create()
{
        set("short","客房");
        set("long",@LONG
这是招待客人住宿的房间。室内陈设精雅，两床相对，枕衾雅洁。
LONG
);
        set("exits",([
                "west" : __DIR__"jicui",
        ]) );
        set("no_clean_up", 0);
        set("sleep_room", 1);
        setup();
}

