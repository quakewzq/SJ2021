//edit by rock
//2008.10.16
//本文件不会被克隆

#include <ansi.h>
#include <localtime.h>
//#include "/quest/smy/sys/list.h"

#define MAX_ROOM_INDEX 200
#define MIRROR_MEMORY  "/quest/smy/sys/memory"
#define MAX_KILLER_INDEX 200
//全局变量
int make_room_index;
int ob_time;
//函数声明
string* mirror_maps=({
		"/quest/smy/smyfuben",
});
int mirror(object leader);
void mirror_ok(object me);
//函数：查询现有量镜像数量
int query_room_amount() { return make_room_index; }
int delete_room_amount() { return make_room_index--; }
//NPC调用，创造镜像世界 单人副本可以不要object* player参数
int mirror(object leader)
{
	object maps,memory,start_room;
	int i,size,j,index;
	mixed time;
	string fileName;

	if(!leader || make_room_index >= MAX_ROOM_INDEX ) return 0;

	//创建内存
	if(!memory = new(MIRROR_MEMORY)) 
	{
		tell_object(leader,HIR"生成内存memory对象失败！\n"NOR);
		return 0;
	}
	//tell_object(leader,HIR"生成内存memory对象成功！\n"NOR);
	memory->set("leader",leader);
	//判断玩家是否符合要求

		if(!leader || !userp(leader) || !living(leader) )
		{
			destruct(memory);
			tell_object(leader,HIR"生成内存memory对象失败，并摧毁这个对象！\n"NOR);
			return 0;//continue;
		}

		memory->set("user_id/1",leader->query("id"));
		memory->set("user/1",leader);
		//tell_object(leader,memory->query("user_id/1")+"\n");
		//tell_object(leader,memory->query("user/1")+"\n");
		leader->set_temp("mirror/mirror_memory",memory);
		tell_object(leader,HIY"【战颂摩崖】正在为你制造镜像，请稍候......\n"NOR);
		//leader->disable_player("<进入镜像中>");
		//leader->set_temp("block_msg/all",1);
	
	
	//制造世界
	size = sizeof(mirror_maps);
	
	for(j=0;j<size;j++)
	{
		maps = new(mirror_maps[j]);
		if(maps)
		{
			//所有地图进memory
			memory->set(sprintf("maps/%d",j),maps);
			sscanf(mirror_maps[j],"/quest/smy/%s",fileName);
			memory->set(fileName,maps);
			maps->set("memory",memory);
			if(maps->query("short") == HIM"颂摩崖"NOR)
			{
				start_room = maps;
				
			}
			//tell_object(leader,maps->query("short")+"\n");
			index ++;
		}
		//tell_object(find_player("rock"),sprintf("new_mirror: %d\n",j));
	}
	/*if (objectp(start_room))
	{
		tell_object(leader,HIW"start_room is :"+start_room->query("short")+"\n"NOR);
	}*/
	if(index < 1 || !start_room)
	{
		leader->enable_player();
		leader->delete_temp("block_msg");
		tell_object(leader,HIW"Error: 镜像制造失败，请联系巫师。\n"NOR);
			
		memory->delete_map();
		destruct(memory);
		time = localtime(time());
		log_file("mirror",sprintf("%d月%d日 %d:%d  虚拟空间创建失败。\n",1+time[LT_MON],time[LT_MDAY],time[LT_HOUR],time[LT_MIN]));
		//log_file("mirror", sprintf("%O %O\n", me, environment()));
		return 0;
	}
	else
	{
		make_room_index ++;
		//tell_object(leader,HIW"set leader start_room.\n"NOR);
		leader->set_temp("mirror/start_room",start_room);
		call_out("mirror_ok",2,leader);
			
		memory->set("mirror_time",time()+1320); //副本销毁时间 暂时设定时22分钟
		memory->set("open_time",time());        //任务开始时间
		//memory->len_exits(); //连通地图(小心)
		memory->heart(1);  //启动心跳
		//call_out("make_killer",60,leader);   //一分钟后开始刷怪
	}
}

void mirror_ok(object me)
{
	object start_room,memory;
	int i,size;
	mapping user_id;

	if(!me) return;

	start_room = (object)me->query_temp("mirror/start_room");
	memory = (object)me->query_temp("mirror/mirror_memory");

	me->enable_player();
	me->delete_temp("block_msg");

	//没有开始房间
	if(!start_room)
	{
		tell_object(me,"坐标错误，你没能进入镜像。\n");
		user_id = (mapping)memory->query("user_id");
		size = sizeof(user_id);

		for(i=0;i<size;i++)
		{
			if(user_id[sprintf("%d",i)] == me->query("id"))
			{
				memory->set(sprintf("user_id/%d",i),0);
				memory->set(sprintf("user/%d",i),0);
				break;
			}
		}
		return;
	}
	else
	{
		//tell_object(me,(string)memory->query("user_id/1")+"\n");
		//tell_object(me,(string)memory->query("user/1")+"\n");
		//me->move(start_room);
		tell_object(me,HIY"【战颂摩崖】请英雄做好准备,尽快赶往颂摩崖，西夏一品堂武士即将入侵大宋。\n"NOR); //广告
	}
}


