// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// Room: /d/changan/duchang2
// by system_3cat 7/5/1997
inherit ROOM;


void create()
{
  set ("short", "骨骰房");
  set ("long", @LONG

这里摆着一个八仙桌，中间摆着一个银盘。赌客们正聚精会神地下赌。
正席是一位胖子，手里不断玩弄着一对玉骰，他就是这里的庄东。

墙上挂有一个匾，上面写着：
    头彩（骰数由每次开盘前确定）      ：一赢三十六
    双对（两骰号相同，且为偶数）      ：一赢十二
    七星（两骰之和为七）              ：一赢六
    散星（两骰之和为三，五，九，十一）：一赢三

匾角有一个牌子(paizi)。

LONG);

  set("item_desc",([
    "paizi" : "押头彩骰： gutou tc <amount> <money>\n"+ 
              "押双对骰： gutou sd <amount> <money>\n"+ 
              "押七星骰： gutou qx <amount> <money>\n"+ 
              "押散星骰： gutou sx <amount> <money>\n" 
  ])); 

  set("exits", ([ /* sizeof() == 1 */
    "east" : __DIR__"chat-dc1",
  ]));

  setup();
}
//是镜像
int is_mirror() { return 1; }
