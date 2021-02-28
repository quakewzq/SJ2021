inherit ROOM;

void create()
{
        set("short", "灵岩山");
        set("long",@long
这里因山上有状如灵芝的巨石，故名灵岩山。这里山势挺拔秀丽，奇石
嶙峋，有甚多的吴宫遗迹，享有“吴中第一峰”的美誉。
long);
set("outdoors", "suzhou");
set("objects",([
__DIR__"obj/xiao-shuzhi" : 1,
__DIR__"obj/da-shitou" : 1,
]));
set("exits",([
"south" : __DIR__"qingshidadao",
"eastup" : __DIR__"yingxiaoting",
"northwest" : __DIR__"tianpingshan",
]));
set("coor/x",120);
  set("coor/y",-290);
   set("coor/z",0);
   setup();
}
