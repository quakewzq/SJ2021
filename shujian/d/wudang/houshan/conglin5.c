// Room : /d/wudang/conglin5.c ����
// By lius 99/8

#include <ansi.h>
#include "conglin.h"
inherit ROOM;

void create()
{
	set("short",YEL"��Ҷ����"NOR);
	set("long", @LONG
����һƬ��Ҷ���֣��紵Ҷ�䣬���������ֺ���������Ҷ�ϣ���������һ
˿�㼣���ܿ����ͷ�����ʧ���Լ��ķ���
LONG                           
        );

	set("exits", ([               
		"east" : __DIR__"conglin"+(random(12)+1),
		"west" : __DIR__"conglin"+(random(12)+1),
		"south" : __DIR__"conglin"+(random(8)+1),
		"north" : __DIR__"conglin"+(random(8)+1),
		"northeast" : __DIR__"conglin"+(random(4)+1),
		"northwest" : __DIR__"conglin6",
		"southeast" : __DIR__"conglin4",
		"southwest" : __DIR__"conglin"+(random(4)+1),
	]));

	set("outdoors", "�䵱");

	set("objects", ([
		__DIR__"../npc/yezhu" : 1, 
		__DIR__"../npc/snake" : 1,
	]));
	set("caiyao_room", 1);

	setup();
}

void reset()
{
	::reset();
	set("caiyao_room", 1);
}

void init()
{
	add_action("do_zhao", ({"zhao","find"}));
}