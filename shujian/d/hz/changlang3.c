// /u/beyond/hz/ changlang1.c 长廊
 
 
inherit ROOM;
void create()
{
        set("short","长廊");
        set("long", @LONG
你走进长廊，看到长廊上面全是一幅幅工笔彩画，当真是妙不可言。每
一幅都栩栩如生，看的你都入迷了，连原来的路都找不到了。
LONG
        );
        set("exits", ([
            "south" : __FILE__,
            "west" : __FILE__,
            "north" : __FILE__,
            "east" : __DIR__"changlang4",
            
]));
        set("coor/x",50);
  set("coor/y",-310);
   set("coor/z",0);
   setup();
}
