// Room: /d/meizhuang/huilang6.c
// By Lklv

inherit ROOM;

void create()
{
	set("short", "回廊");
	set("long", @LONG
这是庄内的一条回廊，地面上整齐地铺着细碎的青石，头上是精美的画梁
，回廊外四周的空地上种着一排排整齐的梅树。
LONG
	);

	set("exits", ([
		"west" : __DIR__"huashi",
		"north" : __DIR__"huilang4",
		"south" : __DIR__"huilang8",
	]));
	setup();
}