// /clone/board/murong_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("慕容世袭图谱", ({ "board" }) );
	set("location", "/d/mr/yanziwu/yanziwu");
	set("board_id", "murong_b");
	set("long", "这是一张姑苏慕容门下世袭相传的图谱。\n" );
	setup();
	set("capacity", 60);
}
