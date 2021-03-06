//      File    :  /adm/daemons/explored.c
//
inherit F_DBASE;

#define SRCH_DIR "/d/"
#include <ansi.h>
#include <explore.h>
#include <get_place.h>
#include <dbase.h>
int explore_level = EXPLORE_LEVEL;
int Check_Illgeal_Target(object target);
int Start_Job(object me, object ob);
int check(object ob);

void create()
{
        set("channel_id", "江湖传闻");
        CHANNEL_D->do_channel( this_object(), "sys", "探险系统已经启动。\n");
//      Start_Job();
}

// 设置杀手技能水平
void Copy_Skill(object me, object ob)
{
        return;
}

mapping *corpse_des = ({
([      "shen"      :     "-1",
        "content"   :     ({
        ([
                 "name" : "黑风双煞",
                 "des"   : "\n你仔细端详了尸首半天，忽然发现尸体的头颅上赫然有五个血洞。\n",
                 "tar" : "你心中一惊：莫不是黑风双煞所为？！赶紧闪呼！！",
        ]),
        ([
                 "name" : "萧远山",
                 "des"   : "\n你仔细端详了尸首半天，只见他脸上肌肉僵硬不动，身手去摸他手掌，但觉颇有凉意，再探他鼻息，早已气绝多时。他胸间吃了人一记掌重手，肋骨齐断，五脏破裂。很显然，此人是突遭重手，顿时毙命。\n",
                 "tar"  : "你心中一惊：莫不是降龙掌的雷霆掌力，哪一个还有如此之威？！",
        ]),}),
]),
([      "shen"      :     "1",
        "content"   :     ({
        ([
                "name"  : "赵半山",
                "des"   : "\n你仔细端详了尸首半天，看来方死不过半个时辰,看起死前来筋骨脱力,竟似被活活累死的一般\n",
                "tar"   : "你心中一惊：莫不是赫赫有名的武当云手所为？！",
        ]),
        ([
                "name"  : "高老者",
                "des"   : "\n你仔细端详了尸首半天，死者脸上红班点点，脸色苍白得骇人。似是被一种奇特内功所为\n",
                "tar"   : "你心中一惊：莫不是名镇天下的紫霞神功的混元无极掌力？！",
        ]),
        }),
]),
});

int Check_Npc(object obj)
{
        int i;
        string name;
        string *banned_name= ({ "小和尚","木人","朱聪","白无常","褚万里","平威",
                           "青鬏龟童","黑无常","白髯老人","巫师","沈老板",
                           "孟婆","当铺老板","岳不群","宋远桥","查老学士"});

        name = obj->query("name");

        if( member_array(name, banned_name)!=-1 ) {
                return 0;
        }

 	write(sprintf("%d ",clonep(obj)));
        if( !obj->is_character()
        ||  userp(obj)
        ||  obj->query("race")!="人类" )
                return 0;

	return 1;
}

int Check_Illgeal_Target(object target)
{
        // 禁止死亡对象的NAME相同。
        if(target->query("name") == this_object()->query("last_target"))
                return 0;

        return 1;
}

string Check_Family(string npcfile)
{
        string family;
        family = npcfile->query("title");
        if(!family) family="";
        return family;
}

string Check_Family1(string npcfile)
{
        string family;
        family = npcfile->query("family/family_name");
        if(!family) family="";
        return family;
}

string Get_Npc()
{
        string family, times, npcfile;
        int i, size;
        object target;
        object *living;


        living=filter_array(livings(), (: Check_Npc :));
	write(sprintf("总NPC:%d ",sizeof(livings())));
        size=sizeof(living);
	write(sprintf("\n过滤后NPC:%d\n",size));
        i=random(size);

        while(1) {
                target=living[i];
                if( Check_Illgeal_Target(target)) {
                        npcfile=file_name(target);
                        printf("Npc:%s\n", npcfile);
                        return npcfile;
                }
                i++;
                if ( i >= size ) i=0;
                if ( i == size ) break;
        }

}

void get_corpse(string npc_file, string file_name, object me)
{

        int i, k, p;
        object *inv;
        object corpse, room, victim;

        if(!(victim = find_object(npc_file)))
             victim = load_object(npc_file);
        if(!(room = find_object(file_name)))
             room = load_object(file_name);
        corpse = new(EXPLORE_OB);
        corpse->move(file_name);
//      corpse->set("dead_message","");
//      corpse->die();        
        corpse->set_name( victim->name(1) + "的尸体", ({ "corpse" }) );
        corpse->set("age", victim->query("age"));
        corpse->set("gender", victim->query("gender"));
        corpse->set("victim_name", victim->name(1));
        corpse->set("victim_id", victim->query("id"));
        corpse->set("victim_exp", victim->query("combat_exp"));
        corpse->set("victim_shen", victim->query("shen"));
        corpse->set_weight( victim->query_weight() );   
        corpse->set_max_encumbrance( victim->query_max_encumbrance() );
//      corpse->move(file_name);
        if( !wizardp(victim) ) {
                inv = all_inventory(victim);
                inv -= ({ 0 });
                i = sizeof(inv);
                while(i--) {
                        if( (string)inv[i]->query("equipped")=="worn" ) {
                                inv[i]->move(corpse);
                                if( !inv[i]->wear() ) inv[i]->move(environment(victim));
                        }
                        else inv[i]->move(corpse);
                }
        }
        corpse->set("long", victim->long(1)
                + "然而，" + gender_pronoun(victim->query("gender")) 
                + "已经死了，只剩下一具尸体静静地躺在这里。\n");        
        
        

        if( (int)me->query("shen") < 0) k=0;
        if( (int)me->query("shen") > 0) k=1;
        p=sizeof(corpse_des[k]["content"]);
        p=random(p);
        corpse->set("corpse_des", corpse->query("long")+corpse_des[k]["content"][p]["des"]);
        
        return;
}

int Start_Job(object me, object ob)
{
        mapping my, tmp_my;
        string dir_name, file_name, chinese_name, npcfile, name, family;
        int exp, num;
        object shashou/*, corpse, room*/;
        object *living, target1, target2, objwhere;
        int i,j;
        string str;

        seteuid(getuid());

	//取得一个系统内的NPC

        living=filter_array(livings(), (: Check_Npc :));
	write(sprintf("总NPC:%d ",sizeof(livings())));
	write(sprintf("\n过滤后NPC:%d\n",sizeof(living)));
        i=random(sizeof(living));

        while(1) {
                target1=living[i];
                if( Check_Illgeal_Target(target1)) {
                        npcfile=file_name(target1);
                        printf("Npc:%s\n", npcfile);
                        break;
                }
                i++;
                if ( i >= sizeof(living) ) i=0;
                if ( i == sizeof(living) ) break;
        }
        
        
//        dir_name = Get_Dir();
//        file_name = Get_File(dir_name);
//        chinese_name = Chinese_Dir(dir_name);
	//取得一个系统内的地点               
	living = livings();
	for (i=0;i < sizeof(living);i++){
		j = random(sizeof(living));
		if (!j || j == sizeof(living) -1) continue;
		if(check(living[j]) ){
			target2 = living[j];
			objwhere = environment(target2);
			str = objwhere->query("short");
			if (!sizeof(objwhere->query("exits"))
			|| str == "武僧堂"
			|| str == "僧舍"
			|| str == HIR"心禅堂"NOR
			|| str == "金刚伏魔圈" ) continue;
			if( get_place(base_name(environment(target2))) != "" ) break;
		}
	}

	if( !target2 ){
		write("暂时没有任务需要做，你过一会儿再来吧。");
		return 1;
	}
		
        family = Check_Family(npcfile);
        name = objwhere->query("short");
        if( explore_level > EXPLORE_LEVEL ) {
                remove_call_out("Start_Job");
                return 1;
        }
        write("地点："+base_name(objwhere)+"\n");
        get_corpse(npcfile, base_name(objwhere), me);
        this_object()->set("last_target", npcfile->query("name"));
        CHANNEL_D->do_channel( this_object(), "chat", sprintf(HIC"听说 "+HIW + "◤"+ HIY +"%s的%s%s" + HIW + "◢ " + HIC + "前些日子在 " + HIW + "◤%s的%s"+ HIW + "◢"+ HIC + " 丢了性命，哪位英雄能探得究竟，将不胜感激！"NOR, 
        get_place(base_name(environment(target1))),family,target1->query("name"),get_place(base_name(objwhere)),name));
//call_out("Start_Job", 150, this_object());
        return 1;

//      if( exp > 20000 ) {  // exp 大于 20k 就可以做Job

              shashou = new("/d/city/npc/xiaoer"); // 出现一个杀手

// 开始设置shashou技能水平
//              Copy_Skill(me, ob);
// 结束设置镖头或者镖师的技能水平

              shashou->set("catch_user_id",me->query("id"));
              shashou->move(environment(me));

//      }

}

int set_explore(int level)
{
        if( geteuid(previous_object()) != ROOT_UID )
                return 0;
        explore_level = level;
        return 1;
}

int check(object ob)
{
	object room;
	string room_name;

	if(!objectp(ob)
	 || !ob->query("startroom")      // add by Yuj@SJ to void job NPC
	 || ob->query("env/invisibility")
	 || ob->query("no_quest")
	 || userp(ob)
	 || ob->query("attitude")=="aggressive"
	 || ob->query("have_master")
	 || !objectp(room=environment(ob))
	 || room->query("no_fight")
	 || room->query("outdoors") == "昆仑翠谷"
	 || strsrch(room_name = file_name(room),"/d/") != 0
	 || strsrch(room_name, "/d/wizard/") == 0
	 || strsrch(room_name, "/d/wuguan/") == 0
	 || strsrch(room_name, "/d/death/") == 0
	 || strsrch(room_name, "/d/group/") == 0
	 || strsrch(room_name, "/d/mingjiao/lsd/") == 0
	 || strsrch(room_name, "/d/mingjiao/bhd/") == 0
	 || strsrch(room_name, "/d/changle/") == 0
	 || strsrch(room_name, "/d/city/") == 0
	 || strsrch(room_name, "/d/shaolin/fumoquan") == 0
	 || strsrch(room_name, "/d/baituo/") == 0)
		return 0;
	return 1;
}
