inherit ROOM;

void create()
{
	set("short", "ʯ��·");
	set("long", @LONG
    ������һ��������ʯ��·�ϣ����Թ������죬��������������
·���������룬�����˺ó�ʱ�䣬Ҳ������һ���ˡ�
LONG	);
	set("exits", ([ /* sizeof() == 2 */
   "west" : __DIR__"shanlu-4",
  "east" : __DIR__"shanlu-2",

   
]));
	set("no_clean_up", 0);
	set("outdoors", "tianlongsi");

	set("coor/x",-440);
  set("coor/y",-320);
   set("coor/z",30);
   setup();
}