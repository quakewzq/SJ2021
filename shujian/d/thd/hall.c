// Room: /u/jpei/thd/hall.c

inherit ROOM;

string look_bagua();

void create()
{
	set("short", "方厅");
	set("long", @LONG
这是一间非常宽敞的方厅。墙上挂着许多的名人字画，个个都是海内罕见
的精品。而在门楣之上钉着八片铁片， 排作八卦(bagua)图案，却又不似寻常
的八卦那么排的整齐，疏疏落落，歪斜不称，显然与四周的布置极不协调。南
面是一座小亭子。
LONG
	);
	set("no_clean_up", 0);

	set("exits", ([
		"west" : __DIR__"zoulang1.c",
        "east" : __DIR__"shilu",
	]));

	set("item_desc", ([
		"bagua" : (: look_bagua :),
	]) );

/*	set("objects", ([
		__DIR__"npc/laoda.c":1,
	]));*/

	setup();
}

string look_bagua()
{
	int i, j, temp;
	int *bagua = ({0,1,2,3,4,5,6,7});
	string *bagua_name = ({"坤","震","坎","兑","艮","离","巽","乾"});
	string result;
	object me = this_player();

	for (i = 0; i < 8; i++)
	{
		j = random(8);
		while (j == i)
			j = random(8);
		temp = bagua[i];
		bagua[i] = bagua[j];
		bagua[j] = temp;
	}		
	for (i = 1; i < 9; i++)
		me->set_temp("bagua_" + i, bagua[i - 1]);
	result = "一个奇怪的铁八卦，上面按顺时针顺序排列着：";
	for (i = 0; i < 8; i++)
		result += bagua_name[bagua[i]];
	return result + "。\n";
}
