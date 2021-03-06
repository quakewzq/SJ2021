// Modafied by mxzhao 2003/07/20

#include "/doc/help.h"

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
string file, *option;
int i;
int showno = 0; 
int domore = 0;
object ob;

seteuid(geteuid(me));

if (!arg) 
return help(me);

option = explode(arg, " ");

for(i=0; i<sizeof(option); i++)
{
switch (option[i])
{
case "-more":
case "-m":
domore = 1;
break;
case "-n":
showno = 1;
break;
default:
arg = option[i];
break;
}
}

file = resolve_path(me->query("cwd"), arg);

if( file_size(file)<0 )
{ 
if (!(ob = present(arg, environment(me))) && !(ob = present(arg, me)))
return 0;

file = file_name(ob);

sscanf(file, "%s#%*s", file);

file += ".c";
}

if( file_size(file)<0 )
return notify_fail("没有这个文件。\n");

if (ob)
write("物件：" + ob->name() + "(" + ob->parse_command_id_list()[0] + ")\n");

write("文件：" + file + "\n");

if (domore)
{
me->start_more(read_file(file));
}
else
{
string *lines;
int size, width;
lines = explode(read_file(file), "\n");
size = sizeof(lines);
width = strlen(size + "");

write("\n");

for (i=0; i<size; i++)
{
if (showno)
{
write(sprintf("%*d: ",width , i));
}

write(lines[i] + "\n");
}
}

return 1;
}

int help(object me)
{
write(@HELP
功能　　：　显示指定文件。

指令格式: 　cam <生物ID>|<物品ID>|<完整文件名>|here [-<more|m>|<n>]

示例　　：　cam yingwu -m
　　　　　　cam cloth -n
　　　　　　cam -n /d/city/guangchang.c
　　　　　　cam here


HELP
    );
    return 1;
}
