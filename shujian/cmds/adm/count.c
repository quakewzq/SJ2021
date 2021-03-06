// count.c

#include <ansi.h>
#define SYNTAX  "指令格式：count [all | a-z]\n"

inherit F_CLEAN_UP;

private int do_count_players(string letter);

int main(object me, string arg)
{
	if (me != this_player(1) || wiz_level(me) < wiz_level("(arch)"))
		return notify_fail("你没有权力使用这个指令。\n");

	if( !arg )
		return notify_fail(SYNTAX);
	
	if( arg != "all" ){
		if( arg[0] < 'a' || arg[0] > 'z' )
			return notify_fail(SYNTAX);
	}
	
	return do_count_players(arg);

	return 1;
}

private int do_count_players(string letter)
{
	int i, j, k = 0, x = 0;
	string *dir, name;
	mixed *info;

	seteuid(getuid());
	write("\n*** 整理玩家储存档中，请稍候.... ***\n");
	
	if( letter == "all" ){
		dir = get_dir(DATA_DIR + "login/");
	
		for(i=0; i<sizeof(dir); i++) {
			reset_eval_cost();
			x = 0;
			info = get_dir(DATA_DIR + "login/" + dir[i] + "/", -1);
			j = sizeof(info);
			while (j--) {
				if (sscanf(info[j][0]+"$", "%s.o$", name)==1 ) 
					x++;
			}
			k += x;
			write(" " + dir[i] + " : " + x + " 位。\n");
			flush_messages();
		}
		write("\n\n总共有 " + k + " 位使用者。\n");
	}
	
	else {
		info = get_dir(DATA_DIR + "login/" + letter + "/", -1);
		j = sizeof(info);
		while (j--) {
			if (sscanf(info[j][0]+"$", "%s.o$", name)==1 ) 
				k++;
		}
		write("\n以 " + letter + " 字母打头的总共有 " + k + " 位使用者。\n");
	}
	
	return 1;
}
