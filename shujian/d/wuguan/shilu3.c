//shilu3.c by river

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "Сʯ·");
        set("long", @LONG
����һ����ʯ���̳ɵ�С·�������������񣬲�ʱ��Щ���˺�Ѿ�ߴ�����
��������ȥ�����������䳡���ܶ���ݵ����������﷢�������������߾͵���
ǰԺ��һȺ����Χ�������֪���ڿ�ʲô��
LONG);
	set("outdoors","���");

        set("exits", ([               
		   "east" : __DIR__"dayuan",
		   "west" : __DIR__"wuchang2",
        ]));          
        
        set("objects", ([
                   __DIR__"npc/qcf" : 1,
        ]));
        setup();
}