//hclu-3.c 荒草路

inherit ROOM;


void create()
{
	set("short", "荒草路");
	set("long", @LONG
你走一条荒芜的小路上，两旁荒草齐膝，荆棘遍地，似乎罕有人至。山石壁立，
遮天蔽日，鸟兽全无，四周笼罩在一片阴暗之中，使这里看起来格外深隧幽静。
LONG
	);

	set("exits", ([
"southeast" : __DIR__"hclu-2",
"northup" : __DIR__"hclu-4",
]));

	set("no_clean_up", 0);
        set("outdoors", "tiezhang");
	set("coor/x",-350);
  set("coor/y",-170);
   set("coor/z",40);
   setup();
}
int valid_leave(object me, string dir)
{
        if ((dir != "northup") && (dir != "southeast"));
        if (dir == "northup"){
            me->receive_damage("qi", 100);       
            write("你的双腿被荆棘刺破，鲜血流了出来。\n");
        }

        if (dir == "southeast"){
            me->receive_damage("qi", 100);       
            write("你的双腿被荆棘刺破，鲜血流了出来。\n");
        }
        return 1;
}
