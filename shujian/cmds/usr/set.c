// set.c
//增加了kill_msg可以加上颜色 LINUX@SJ 2003.0908

#include <ansi.h>
#include <database.h>

#define MAX_ENV_VARS 20

int help();

string *wiz_only = ({"invisibility", "immortal", "no_fight", "msg_min", "msg_mout", "msg_clone", "msg_dest"});
string *color_setting = ({"kill_msg","protect_msg"});

int main(object me, string arg)
{
	string term, *terms;
	mixed data;
	mapping env;


	env = me->query("env");

	if (!arg) {
		if (!sizeof(env))
			write("你没有设定任何环境变量。\n");
		else {
			write("你目前设定的环境变量有：\n");
			terms = sort_array(keys(env), 1);
			foreach (string item in terms)
				write(sprintf("%-20s %O\n", item, env[item]));
		}
		return 1;
	}

	if (sscanf(arg, "%s %s", term, data) != 2) {
		term = arg;
		data = "YES";
	}

	term = replace_string(term, "/", "");
	if (term != "") {
		if( mapp(env) && undefinedp(env[term]) && sizeof(env) >= MAX_ENV_VARS )
			return notify_fail("你设的环境变量太多了，请先用 unset 删掉几个吧。\n");
		if (strlen(term) > 20)
			return notify_fail("你设的环境变量太长了。\n");
		if (!wiz_level(me) && member_array(term, wiz_only) != -1)
			return notify_fail("只有巫师能用这个设定。\n");
		if(member_array(term, wiz_only) != -1  && data || member_array(term, color_setting) != -1) {
			data = replace_string(data, "$RED$", RED);
			data = replace_string(data, "$GRN$", GRN);
			data = replace_string(data, "$YEL$", YEL);
			data = replace_string(data, "$BLU$", BLU);
			data = replace_string(data, "$MAG$", MAG);
			data = replace_string(data, "$CYN$", CYN);
			data = replace_string(data, "$WHT$", WHT);
			data = replace_string(data, "$HIR$", HIR);
			data = replace_string(data, "$HIG$", HIG);
			data = replace_string(data, "$HIY$", HIY);
			data = replace_string(data, "$HIB$", HIB);
			data = replace_string(data, "$HIM$", HIM);
			data = replace_string(data, "$HIC$", HIC);
			data = replace_string(data, "$HIW$", HIW);
			data = replace_string(data, "$NOR$", NOR);
			data = data + NOR;
		}
		sscanf(data, "%d", data);
		if(strlen(data) > 80)
			return notify_fail("对不起，你设定的变量值太长了，请短一点。\n");
		/*if (term == "kill_msg")
			BBS_D->add_Bbs_Up_Map(WEB_DB_NAME, "
			INSERT INTO mud_nick (utime, content, name, userid, type, site) 
			values (
			'" + time() +"',
			'" + data + "',
			'" + me->query("color") + me->query("name") +"',
			'" + me->query("id") + "',
			'kill_msg',
			'"+ lower_case(INTERMUD_MUD_NAME) + "')");*/			
		if (data)
			me->set("env/" + term, data);
		else
			me->delete("env/" + term);
		write(sprintf("设定环境变量：%s = %O\n", term, data));
		return 1;
	}
	return help();
}

int help()
{
	write(@TEXT
指令格式：set <变量名> [<变量值>]

这个指令让你设定一些环境变量，不加参数时会显示你目前设定的环境变量，不指定
变量值，则内定值为 "YES"。

取消变量设定请用 unset 指令。

至於有哪些环境变量可以设定，请见 help settings。
TEXT
);
	return 1;
}
