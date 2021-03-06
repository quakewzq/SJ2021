// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// Room: /d/changan/duchang1
// by system_3cat 7/5/1997
inherit ROOM;


void create()
{
  set ("short", "押签房");
  set ("long", @LONG

一群人围着紫檀木大桌而坐，首席座着一位精瘦的签客，正在一本
正经地从镶金黑盒里慢悠悠一根一根往外抽出乾坤签，码在桌面上。

墙上有一匾写着：
    大乾签（全部五根皆为乾签）：一赢三十二
    大坤签（全部五根皆为坤签）：一赢三十二
    小乾签（连续四根皆为乾签）：一赢十六
    小坤签（连续四根皆为坤签）：一赢十六
      乾签（任意三根皆为乾签）：一赢二
      坤签（任意三根皆为坤签）：一赢二

匾角有一个牌子(paizi)。

LONG);

  set("item_desc",([
    "paizi" : "押大乾签： qian dqq <amount> <money>\n"+ 
              "押大坤签： qian dkq <amount> <money>\n"+ 
              "押小乾签： qian xqq <amount> <money>\n"+ 
              "押小坤签： qian xkq <amount> <money>\n"+ 
              "押乾签：   qian qq <amount> <money>\n"+ 
              "押坤签：   qian kq <amount> <money>\n",
  ])); 
  set("exits", ([ /* sizeof() == 1 */
    "south" : __DIR__"chat-dc1",
  ]));

  setup();
}
//是镜像
int is_mirror() { return 1; }