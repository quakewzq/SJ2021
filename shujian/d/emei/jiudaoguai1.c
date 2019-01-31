// Room: /d/emei/jiudaoguai1.c 峨嵋派 九十九道拐1

inherit ROOM;
#include <ansi.h>
void create()
{
	set("short",HIW "九十九道拐" NOR);
	set("long", @LONG
这是著名的「九十九道拐」，道路纡曲陡竖，千折百回。据说过去曾有个
百余岁的疯僧至此，见一巨蟒挡路，便念咒驱蟒。但人们得知此处有巨蟒出没
后，便再也无人敢碰这里的草木，并以「龙居」名之。由此东可至千佛庵，西
达九老洞。
LONG
	);

	set("exits", ([
		"northeast" : __DIR__"qianfoan",
		"westup" : __DIR__"jiudaoguai2",
	]));

	set("outdoors", "shaolin");
	setup();
}



