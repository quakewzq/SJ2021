// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// Room: /d/changan/duchang3
// by system_3cat 7/5/1997
inherit ROOM;


void create()
{
  set ("short", "斗鸡房");
  set ("long", @LONG

斗鸡房里一左一右放着两个青竹鸡笼，一个鸡笼里关着一群红冠鸡，
另一个鸡笼里关着一群绿尾鸡。屋子正中是七尺见方的斗鸡场，由一
圈低低的青玉栏杆围成。一位白髯鸡仙正在张罗着斗鸡。在他的后面
墙上有一个牌子(paizi)。

LONG);

  set("item_desc",([
    "paizi" : "押红冠鸡： dou hg <amount> <money>\n"+ 
              "押绿尾鸡： dou lw <amount> <money>\n", 
  ])); 

  set("exits", ([ /* sizeof() == 1 */
    "west" : __DIR__"chat-dc1",
  ]));

  setup();
}
//是镜像
int is_mirror() { return 1; }