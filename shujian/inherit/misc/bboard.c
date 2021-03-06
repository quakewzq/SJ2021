// bboard.c modify by XiaoYao 01/10/2000
// modify by linux 10/17/2003 增加留言回复
// Modified by Ciwei@SJ 5/8/2004 与bbs连接

inherit ITEM;
inherit F_SAVE;

#include <ansi.h>
#include <board.h>
#include <mudlib.h>

#define BOARD_CAPACITY query("capacity")
#define TEXT_LINE "───────────────────────────────────"
#ifndef BBS_ADDR
#define BBS_ADDR "http://bbs.mymud.com"
#endif
#define BBS_OK(x) sprintf(WHT"%s发表到论坛完成。\n"NOR,x)
#define BBS_URL(x) sprintf(CYN"详情请浏览：%s/viewthread.php?tid=%d。\n"NOR,BBS_ADDR,x)

void setup()
{
        string loc;

        ::setup();
        if( stringp(loc = query("location")) )
                move(loc);
        set("no_sac", 1);
        set("no_get", 1);
        restore();
        set("location", loc);
}

void init()
{
        add_action("do_post", "post");
        add_action("do_read", "read");
        add_action("do_list", "list");
        add_action("do_discard", "discard");
        add_action("do_re", "re");
}

string query_save_file()
{
        string id;

        if( !stringp(id = query("board_id")) ) return 0;
        return DATA_DIR + "board/" + id;
}

string short()
{
        mapping *notes;
        int i, unread, last_read_time;

        notes = query("notes");
        if( !pointerp(notes) || !sizeof(notes) )
                return ::short() + " 「 没有任何留言 」";

        if( this_player() ) {
                last_read_time = (int)this_player()->query("board_last_read/" + (string)query("board_id"));
                for(unread = 0, i=sizeof(notes)-1; i>=0; i--, unread ++)
                        if( notes[i]["time"] <= last_read_time ) break;
        }
        if( unread )
                return sprintf("%s 「 %d 张留言，"HIY"%d "NOR"张"HIR"未读"NOR" 」", ::short(), sizeof(notes), unread);
        else
                return sprintf("%s 「 %d 张留言 」", ::short(), sizeof(notes));
}

string long()
{
        return ::long() + @LONG
留言版的使用方法：
list [留言编号|new]     : 查看留言标题
post <标题>             : 留言
read <留言编号|new|next>: 查看留言内容
discard <留言编号>      : 删除留言
LONG;
}

nosave int op;

void post_ok(mixed ret)
{
	mapping *notes;
	
	if(environment()) tell_room(environment(),BBS_OK("留言"));
	notes = query("notes");
	if(!notes || !sizeof(notes)) return;
	if(op != sizeof(notes)-1) return;//have somebody change it
	if(!ret || !sizeof(ret)) return;
	notes[op]["tid"] = ret[0][0];
	if(environment()) tell_room(environment(),BBS_URL(ret[0][0]));
	save();
}

// This is the callback function to process the string returned from the
// editor defined in F_EDIT of player object.
void done_post(object me, mapping note, string text)
{
        mapping *notes;

        note["time"] = time();
        note["msg"] = text;
        //转换特殊字符
        note["title"] = specialchars(note["title"]);
        text = specialchars(text);
        //转换特殊字符结束
        if(query("board_id") && !undefinedp(BOARD_FID[query("board_id")]))
		BBS_D->bbs_post(BOARD_FID[query("board_id")],wizardp(me)?me->query("id"):me->query("id")+"@"+lower_case(INTERMUD_MUD_NAME),note["title"],"发表于"+CHINESE_MUD_NAME+::short() + "\n\n" + text,0,0,0,this_object(),"post_ok" );
        
        notes = query("notes");
        if( !pointerp(notes) || !sizeof(notes) )
                notes = ({ note });
        else
                notes += ({ note });
	
	op = sizeof(notes)-1;
        // Truncate the notes if maximum capacity exceeded.
        if( sizeof(notes) > BOARD_CAPACITY )
                notes = notes[BOARD_CAPACITY / 2 .. BOARD_CAPACITY];

        set("notes", notes);
        save();
        note = copy(note);
        note["msg"] = "来自 " + ::short() + "\n" + text;
        "/clone/board/post_b"->done_post(me, note);

        tell_object(me, TEXT_LINE + WHT"[ E n d ]\n"NOR);
        tell_object(me, "留言完毕。\n");        
        me->add_busy(1);
}

void re_ok(mixed ret)
{
	if(environment()) tell_room(environment(),BBS_OK("回复"));
	if(ret && sizeof(ret)) if(environment()) tell_room(environment(),BBS_URL(ret[0][0]));
}

void done_re(object me, mapping report, int project, string text)
{
	mapping *notes, *reports;
	int i;
        string *lines;

        if (! stringp(text))
                return;

        if (strlen(text) > 64 * 1024)
        {
                tell_object(me, "你的留言太长了，请略去一些不必要的。\n");
                return;
        }

        lines = explode(text, "\n");
        i = sizeof(lines);
        if (i > 2000)
        {
                tell_object(me, "你的留言太长了，请略去一些不必要的。\n");
                return;
        }

        if (i > 20 && strlen(text) / i < 10)
        {
                tell_object(me, "你的留言中短句太多了，请调整一下以便他人阅读。\n");
                return;
        }

        while (i--)
        {
                // scan all lines
                if (strlen(lines[i]) > 300)
                {
                        tell_object(me, "你留言中有些行太长了，请分行以便他人阅读。\n");
                        return;
                }
        }

        wizardp(me)?report["msg"] = HIG+text+NOR:report["msg"] = text;
	notes = query("notes");
	reports = notes[project]["re"];
	
	report["title"] = specialchars(report["title"]);
	text = specialchars(text);
	
	text = "发表于"+CHINESE_MUD_NAME+::short() + "\n\n" + text;
	if(query("board_id") && !undefinedp(BOARD_FID[query("board_id")]) && !undefinedp(notes[project]["tid"]) && notes[project]["tid"] )
		BBS_D->bbs_post(BOARD_FID[query("board_id")],wizardp(me)?me->query("id"):me->query("id")+"@"+lower_case(INTERMUD_MUD_NAME),report["title"],text,notes[project]["tid"],0,0,this_object(),"re_ok" );
	
	if( !arrayp(reports) )	reports = ({ report });
	else reports += ({ report });

	notes[project]["re"] = reports;
	notes[project]["time"] = time();

	set("notes", notes);
	tell_object(me,"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━[ 回复结束 ]\n");

	save();
	return;
}
int do_post(string arg)
{
        mapping note;
        int i;
        object me;

        if( !arg ) return notify_fail("留言请指定一个标题。\n");

        me = this_player();
        if (me->is_busy())
                return notify_fail("你正忙着呢。\n");
        i = strlen(arg);
        if( !wizardp(me) ){
                if (i < 4 || i > 24 || i%2) {
                        write("对不起，标题必须是 2 到 12 个中文字。\n");
                        return 0;
                }

                while(i--)
                        if (i%2==0 && !is_chinese(arg[i..<1])) {
                                write("对不起，请您用「中文」取标题。\n");
                                return 0;
                        }
        }
        else if( i > 24 )
                return notify_fail("你的标题太长了，请缩短你的标题。\n");

        note = allocate_mapping(4);
        note["title"] = arg;
        note["author"] = me->query("name") + "(" + me->query("id") + ")";        
        me->edit( (: done_post, me, note :) );
        return 1;
}

int do_read(string arg)
{
        int num,j;
        mapping *notes, last_read_time;
        string myid;
        string msg = "";

        last_read_time = this_player()->query("board_last_read");
        myid = query("board_id");
        notes = query("notes");

        if( !pointerp(notes) || !sizeof(notes) )
                return notify_fail("留言板上目前没有任何留言。\n");

        if( !arg ) return notify_fail("指令格式：read <留言编号>|new|next\n");
        if( arg=="new" || arg=="next" ) {
                if( !mapp(last_read_time) || undefinedp(last_read_time[myid]) )
                        num = 1;
                else
                        for(num = 1; num<=sizeof(notes); num++)
                                if( notes[num-1]["time"] > last_read_time[myid] ) break;

        } else if( !sscanf(arg, "%d", num) )
                return notify_fail("你要读第几张留言？\n");

        if( num < 1 || num > sizeof(notes) )
                return notify_fail("没有这张留言。\n");
        num--;
        
        if(notes[num]["tid"])
        	msg += "\n"+ BBS_URL(notes[num]["tid"]);
                
        if (sizeof(notes[num]["re"])) {
				for (j=0;j<sizeof(notes[num]["re"]);j++) {
					msg+=sprintf(
					"\n%s 于 %s 回复如下："NOR" %s\n"
					TEXT_LINE +"\n"
					"%s\n",
					notes[num]["re"][j]["author"]+"("+
					notes[num]["re"][j]["owner"]+")",
					ctime(notes[num]["re"][j]["time"])[0..15],
					notes[num]["re"][j]["title"],
					notes[num]["re"][j]["msg"],);
				}
			}		
			
        this_player()->start_more(sprintf(HIW"编号："NOR"%-4d "HIW"作者："NOR"%-35s"HIW"时间："NOR"%s\n"HIW"标题："NOR"%s\n%s\n%s",
        num + 1, notes[num]["author"], ctime(notes[num]["time"]),
        notes[num]["title"], TEXT_LINE +"──────", notes[num]["msg"] + msg + TEXT_LINE + "[ 本 篇 完 ]\n"));

        // Keep track which post we were reading last time.
        if( !mapp(last_read_time) )
                this_player()->set("board_last_read", ([ myid: notes[num]["time"] ]) );
        else
                if( undefinedp(last_read_time[myid]) || notes[num]["time"] > last_read_time[myid] )
                        last_read_time[myid] = notes[num]["time"];

        return 1;
}

int do_re(string arg)
{
	int num;
	string title;
	mapping note, *notes;
	object me=this_player();
	
	if (!wizardp(me)) return 0;

	if(!arg || sscanf(arg, "%d.%s", num, title)<1)
		return notify_fail("指令格式：re <贴子编号>.<回复标题>\n");

	notes = query("notes");
	if( !arrayp(notes) || num < 1 || num > sizeof(notes) )
		return notify_fail("没有这个贴子。\n");

	if (strlen(title) > 30)
		return notify_fail("这个回复标题太长了，请换一个简洁一点的。\n");


	if (!title) title="Re: "+notes[num-1]["title"];

	note = allocate_mapping(5);
	note["title"] = title;
	note["owner"] = me->query("id");
	note["author"] = me->name(1);
	note["time"] = time();
	me->edit( (: done_re, me, note, num-1 :) );
	return 1;
}
int do_discard(string arg)
{
        object me=this_player(1);
        mapping *notes;
        int num;

        if( !arg || sscanf(arg, "%d", num)!=1 )
                return notify_fail("指令格式：discard <留言编号>\n");
        notes = query("notes");
        if( !arrayp(notes) || num < 1 || num > sizeof(notes) )
                return notify_fail("没有这张留言。\n");
        num--;
        if (notes[num]["author"] != me->query("name") + "("+me->query("id")+")"
        && SECURITY_D->get_status(me) != "(admin)"
        && SECURITY_D->get_status(me) != "(assist)"
        && SECURITY_D->get_status(me) != "(arch)")
                return notify_fail("这个留言不是你写的。\n");

        notes = notes[0..num-1] + notes[num+1..<1];
        set("notes", notes);
        save();
        write("删除第 " + (num+1) + " 号留言....Ok。\n");
        return 1;
}

int do_list(string arg)
{
        mapping *notes, last_read_time = 0;
        int num, i, last_time_read, width;
        string msg = "", myid;

        notes = query("notes");
        last_read_time = this_player()->query("board_last_read");
        myid = query("board_id");
        if ( !arg || sscanf(arg, "%d", num)!=1 || num < 1 ) num = 1;
        if ( arg == "new") {
                arg = 0;
                if( !mapp(last_read_time) || undefinedp(last_read_time[myid]) )
                        num = 1;
                else
                        for(num = 1; num<=sizeof(notes); num++)
                                if( notes[num-1]["time"] > last_read_time[myid] ) break;
        };

        if (num > sizeof(notes)) return notify_fail("没有您要的留言。\n");

        if (mapp(last_read_time)) last_time_read = last_read_time[myid];

        width = strlen(sizeof(notes)+"");
        for(i = num-1; i < sizeof(notes); i++) {
                if (arg == "me"
                        && strsrch(notes[i]["author"], "("+this_player()->query("id")+")") < 0)
                        continue;
                if (arg && !sscanf(arg, "%*d") && arg != "me" && strsrch(notes[i]["author"], arg) < 0)
                        continue;
                msg += sprintf("%s[%*d]" NOR,
                        notes[i]["time"] > last_time_read ? HIY: "",
                        width, i+1);
                msg += (sprintf("     %-=39s %18s (%s)\n",
                        notes[i]["title"], notes[i]["author"],
                        ctime(notes[i]["time"])[3..15] ))[4..<0];
        }
        this_player()->start_more(msg);
        return 1;
}
