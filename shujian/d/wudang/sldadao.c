// /d/wudang/sldadao.c 松林大道
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIG"松林大道"NOR);
        set("long", @LONG
你走在山腰松林中，这片松林环山生成，蔚蔚葱葱，象是贵妇人
的绿裙褊，把武当山装扮得更加婀娜多姿! 两边是茂密的松树林，偶
尔有被惊吓的山鸡从你旁边的草丛里飞出，你刚要去抓，它却又飞入
了草丛。
LONG
        );
        set("exits", ([
                "south" : __DIR__"yuzhengong",
                "east" :__DIR__"songlin1",
                "west" :__DIR__"songlin2",
                "northdown" :__DIR__"shijie2",
        ]));

        set("objects",([
                __DIR__"npc/shanji" : 1,

        ]));
        
        set("coor/x",20);
  set("coor/y",0);
   set("coor/z",30);
   setup();

}
