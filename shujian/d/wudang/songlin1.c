// /d/wudang/songlin1.c 松林
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIG"松林"NOR);
        set("long", @LONG
这里是松林的边缘地带，树木还不太茂密，阳光透射而入，松针
遍地。往西是返回大道的路。
LONG
        );
        set("exits", ([
                "east" :__DIR__"songlin2",
                "west" :__DIR__"sldadao",
        ]));

        set("objects",([
                __DIR__"npc/yetu" : 1,

        ]));
        
        set("coor/x",30);
  set("coor/y",0);
   set("coor/z",30);
   setup();

}
