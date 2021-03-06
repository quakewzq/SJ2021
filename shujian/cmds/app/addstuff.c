// adstuff.c
// by snowman@SJ 20/05/1999

#include <ansi.h>
inherit F_CLEAN_UP;
int help(object me);

int main(object me, string arg)
{
	object ob;
	mapping obs;
	string *name;
	int num = 1;

	if (!arg) {
		obs = TASK_D->query_stuffs();
		if (sizeof(obs) < 1)
			return notify_fail("没有任何物品。\n");
		name = keys(obs);
		foreach (string item in name)
			write(sprintf("%-40s %4d\n", item+"("+obs[item]["id"]+") ", obs[item]["reward"]));
		return 1;
	}
	if (sscanf(arg, "%d %s", num, arg) != 2)
		return help(me);

	if (num <= 0) {
		if (TASK_D->delete_stuff(arg))
			return notify_fail("你将 "+arg+" 从 task_stuffs 里删除....Ok。\n");
		return notify_fail("将 "+arg+" 从TASKD.C 中删除失败。\n");
	}

	if (!objectp(ob = present(arg, environment(me))))
		if( !objectp(ob = present(arg, me)))
		       return notify_fail("这里没有这个物品。\n");

	if (ob->is_character())
		return notify_fail("看清楚一点，那可是生物哦。\n");

	if (file_size(base_name(ob)+".c") <= 0 )
		return notify_fail("对不起，此物品的源文件已经不存在了。\n");

	if (TASK_D->set_stuff(ob->query("name"), ([ "id" : ob->query("id"), "reward" : num ]) ))
		return notify_fail("你将"+ob->name()+"("+ob->query("id")+") ，EXP = "+num+" 加入到 task_stuffs 里....Ok。\n");

	return notify_fail("TASK_D 中已经有了此件物品，如要更改请先删。\n");
}

int help(object me)
{
write(@HELP
指令格式：

adstuff <奖励> <物品>

奖励为所值之EXP。
如果奖励为零，将删除此物品。

by snowman@SJ 20/05/1999

HELP
    );
    return 1;
}

