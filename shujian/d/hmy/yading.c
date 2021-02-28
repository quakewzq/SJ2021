// /d/hmy/shiwu.c
#include <ansi.h>

#define	SHIP_TO	__DIR__"ryping"

inherit ROOM;

void create()
{
	set("short", HIW"崖顶"NOR);
	set("long", @LONG
崖顶当中安放着一巨大的绞索绞盘，绞盘吊着一只大竹篓（lou)，看来是
上下黑木崖的主要工具。日光从东射来，照上面前一座汉白玉的巨大牌楼，金
壁辉煌，刹是壮观。
LONG
	);
	set("exits", ([ 
	  	"east" : __DIR__"pailou",
	]));
	set("item_desc",([
	  "lou" : "一个巨大的竹篓，你大喊(yell)一声，可以供你下崖(xiaya)。\n",
	]));
	set("outdoors", "黑木崖");
	setup();
}

void init()
{
	add_action("do_yell", "yell");
	add_action("do_zong", "zong");
}

int do_yell(string arg)
{
	object me = this_player();
	object room;
	
	if (!arg) return 0;

	if (arg == "xiaya") arg = "下崖";
	if (arg != "下崖") arg = "哇";
	if (me->query("age") < 16  )
		message_vision("$N使出吃奶的力气喊了一声：“" + arg + "”\n", me);
	else if (me->query("neili") > 500)
		message_vision("$N吸了口气，一声“" + arg + "”，声音中正平和地远远传了出去。\n", me);
	else
		message_vision("$N鼓足中气，长啸一声：“" + arg + "！”\n", me);
	if (arg == "下崖") {
		if( !(room = find_object(__DIR__"zhulou")))
			room = load_object(__DIR__"zhulou");
		if( room = find_object(__DIR__"zhulou")) 
			if(!room->query("start")) 
				room->arrive("yading");
			else
				message_vision("崖下远远传来一阵回声：“等等啊，这就来了～～～”\n", me);
			return 1;
	}
	else
		message_vision("崖下远远传来一阵回声：“" + arg + "～～～”\n", me);
	return 1;
}

int valid_leave(object me, string dir)
{
	if(query("exits/enter") && dir == "enter")
		me->set_temp("side", "yading");
	return ::valid_leave(me, dir);
}

int do_zong()
{
        object me = this_player();
        object room;
        int cost = 1200;
        
        if( !(room = find_object(__DIR__"zhulou")) )
		room = load_object(__DIR__"zhulou");
        if (!living(me)) return 0;
        
        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着呢！\n");
        if (me->query_skill("dodge") < 300)
                return notify_fail("你的修为不够！\n");
        if (me->query("max_neili") < 4000)
                return notify_fail("你的内力修为不够，怎能支持！？\n");
        if (me->query("neili") < 1500)
                return notify_fail("你的真气不够了！\n");
        if (me->query("jingli") < 1000)
                return notify_fail("你的精力不够了！\n");

        if (me->query_encumbrance()/100 > me->query("neili") + cost)
                return notify_fail("你带这么重的包袱，走路都成问题，别说飞了！\n");

        if (query("exits/enter"))
        	return notify_fail("有竹篓就坐上去吧。\n");    
        
	if (!objectp(room = find_object(__DIR__"zhulou") ))
		return notify_fail("糟糕，竹篓不见了！快通知巫师。\n");
            
	if((int)room->query("exits/out"))
		return notify_fail("峭壁实在太陡了，如果没有中途借力的地方根本没法纵身下去！\n"); 

	me->receive_damage("neili", 600);
	me->receive_damage("jingli", 200);
	tell_room(environment(me), HIC+me->name()+"紧了紧随身物品，身形一晃，纵身向下窜去！\n" NOR, ({me}));
	write("你一提内息，看准了崖间竹篓位置，使出「纵字诀」，想要飞身下崖。\n");
	me->move(__DIR__"zhulou");
	me->start_busy(3);
	if(me->query_encumbrance()/100 > me->query("neili") + cost
	 || me->query("neili") < 800 || me->query("jingli") < 500) {
		write("你还想提气，却发现力不从心了。\n");
		tell_room(environment(me), HIC+me->name()+"长袖飘飘，从崖上飞跃过来，站在竹篓中，大口大口喘着气！\n" NOR, ({me}));
		return 1;
	}
	tell_room(environment(me), HIC+me->name()+"长袖飘飘，从崖上飞跃过来，在竹篓上一点，又向下纵出！\n" NOR, ({me}));
	write("你在崖间竹篓上轻轻一点，又提气飞纵向下。\n");
	me->move(SHIP_TO);
	tell_room(environment(me), HIC"只见"+me->name()+"长袖飘飘从崖上跃来，姿态潇洒地落在地上。\n"NOR, ({me}));
	me->receive_damage("neili", 600);
	me->receive_damage("jingli", 200);
	return 1;
}
