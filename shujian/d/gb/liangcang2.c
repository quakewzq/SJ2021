inherit ROOM;

void create()
{
	set("short", "�в�");
	set("long", @LONG
�����ɹŴ���Ķ���֮������ν����δ�����������У��������ʳ�Ͳ���
�ѻ���ɽ��һ�Ӷ�Ѳ�߱������������䱸ɭ�ϡ�
LONG);
	set("outdoors","�ƺ�");

	set("exits", ([
		"north" : __DIR__"liangcang1",
		"south" : __DIR__"liangcang3",
		"east"  : __DIR__"liangcang4",
		"west"  : __DIR__"liangcang5",
	]));
	set("objects", ([
		__DIR__"obj/liangdun" : 1,
		__DIR__"npc/yuanbing" : 1,
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	object ob;

	ob = present("yuan bing",environment(this_player()) );
	if(ob)
		return notify_fail("Ԫ��һ�ѽ�����ס�������ܣ�\n" );
	return ::valid_leave(me, dir);
}