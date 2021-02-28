// /d/xingxiu/silk3.c
//tangfeng@SJ 2004

#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", HIM"颂摩崖"NOR);
        set("long", @LONG
颂摩崖又名黄龙碑。周围山势陡峭，两山对峙，一泓中流，两峡旁有潭，
渊深莫测。俗传有黄龙自潭飞出，因名黄龙潭。潭左侧摩崖成碑。汉隶真迹，
笔触遒劲，刀刻有力，记叙了开天井道的过程。往东南是仇池山，往西则是
石门。
LONG);
        set("outdoors", "yili");
        

        set("exits", ([
                "eastdown" : "/d/xingxiu/silk2",
                "westdown" : "/d/xingxiu/silk4",
                "north" : "/d/xingxiu/silk3a",
        ]));


   setup();
}
void init()
{

	tell_object(this_player(),HIG"你一看东边有一座高山，山势险峻，正是鲁长老所说的颂摩崖，便不再犹豫，毅然提气飞纵而上！\n"NOR);
}
//是镜像
int is_mirror() { return 1; }