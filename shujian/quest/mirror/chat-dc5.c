inherit ROOM;

void create()
{
  set ("short", "赛龟房");
  set ("long", @LONG

一排紫色的镂空檀香靠背椅沿着屋子四周放了一圈，坐着聚精会神的
客人。中间是一雕花石座，上面放着一个长长的紫檀龟台。一位扎着
青鬏的龟童正围着龟台转来转去。龟房的墙上挂着牌子(paizi)。

LONG);

  set("item_desc",([
    "paizi" : "押长寿龟： sai cs <amount> <money>\n"+ 
              "押千年龟： sai qn <amount> <money>\n"+ 
              "押不老龟： sai bl <amount> <money>\n", 
  ])); 

  set("exits", ([ /* sizeof() == 1 */
    "north" : __DIR__"chat-dc4",
  ]));
  setup();
}
//是镜像
int is_mirror() { return 1; }