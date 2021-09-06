// /d/wudang/songlin2.c 松林
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIG"松林"NOR);
        set("long", @LONG
这里是松林的边缘地带，树木还不太茂密，阳光透射而入，松针
遍地。往东是返回大道的路。
LONG
        );
        set("exits", ([
                "west" :__DIR__"songlin1",
                "east" :__DIR__"sldadao",
        ]));

        set("objects",([
                __DIR__"npc/shanji" : 1,

        ]));
        
        set("coor/x",40);
  set("coor/y",0);
   set("coor/z",30);
   setup();

}
