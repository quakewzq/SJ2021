// Room: /u/zqb/tiezhang/shanlu-8.c

inherit ROOM;

void create()
{
	set("short", "山路");
	set("long", @LONG
你走在一条崎岖的山路上，道旁山峰壁立，长草过腰，中间一条羊肠小路，
仅容一人勉强过去。
LONG
	);

	set("exits", ([
"southdown" : __DIR__"dezj",
"northup" : __DIR__"shanlu-9",
]));

	set("no_clean_up", 0);
	set("outdoors", "tiezhang");

	set("coor/x",-330);
  set("coor/y",-130);
   set("coor/z",60);
   setup();
}
