//guangchang.c �㳡

inherit ROOM;

void create()
{
	set("short", "�㳡");
	set("long", @LONG
ɽ·�е������Ȼ��ÿ���������ǰ������һƬ�ܴ�Ĺ㳡��һЩ����
��ĵ������ش�������䣬�Եú�æµ���ڹ㳡����Χ�кܶ���ʯ���ķ��ӡ�
�������������Եøߴ���ΰ������ķ����в�ʱ��ӿ��������������仹��
���Źķ��������
LONG
	);

	set("exits", ([ 
"south" : __DIR__"shanlu-2.c",
"west" : __DIR__"lgfang",
"east" : __DIR__"guajia",
"northup" : __DIR__"wztang",
]));

    set("objects", ([
__DIR__"npc/mayi4" : 1,
__DIR__"npc/huiyi" : 2,
    ]));

        set("valid_startroom", 1);
	set("no_clean_up", 0);
	set("outdoors", "tiezhang");

	set("coor/x",-330);
  set("coor/y",-260);
   set("coor/z",0);
   setup();
        "/clone/board/tiezhang_b"->foo();
}