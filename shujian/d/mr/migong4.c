// /d/mr/migong4.c

inherit ROOM;

void create()
{
	set("short","�Թ�");
	set("long",@LONG
�����ǹ���Ľ�ݵĵ����Թ�����Ȼ��ͨ��һ����Ҫ�ĵط������ܵ�ǽ����
����¶ˮ�������κ������ǣ���һ�߽�������ʧ�˷���
LONG);

	set("exits",([
		"east" : __DIR__"migong4",
		"west" : __DIR__"migong1",
		"north" : __DIR__"migong4",
		"south" : __DIR__"migong3",
	]));

	setup();
}

#include "migong.h"