// ��׼ʿ�� cigarman

inherit FIGHTER;

#include <ansi.h>
#include "killer.h"
void check_fight(object me,object ob);

string *colors = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});

string *nick_first=({

        "����", "����", "����", "����", "����", "�ĺ�", "���", "��÷",
        "��Ȫ", "��Ȫ", "��Ȫ", "��Ȫ", "ŭ��", "����", "����", "��ˮ",
        "��",   "��",   "С",   "��",   "��",   "��",   "��",   "��",
        "���", "˫��", "����", "��ʤ", "�⹳", "�һ�", "�޵�", "˫��", 
        "����", "��Ů", "����", "����", "����", "��", "����", "�̹�",
        "����", "��ˮ", "ܽ��", "��Ԩ", "��ɽ", "��", "����", "����",
        "����", "��Ƥ", "��ɽ", "����", "����", "���", "�׺�", "����", 
        "����", "����", "����", "��β", "���", "���", "����", "����", 
        "����", "����", "��ͷ", "����", "ţͷ", "�л�", "����", "����", 
        "����", "�պ�", "����", "��ͷ", "�ͻ�", "���", "��ˮ", "����",
        "�޹�", "����", "���", "���", "����", "��Ʒ", "��ˮ", "��ˮ",
        "���", "�ط�", "����", "����", "����", "����", "����", "ħ��",
        "��ˮ", "��ˮ", "ħˮ", "����", "�岽", "��Ҷ", "��Ҷ", "����",
        "����", "����", "ħ��", "�˺�", "����", "�ͻ�", "��ʨ", "Х��",
        "�÷�", "����", "����", "����", "����", "����", "����", "ʨ��",
        "Ұ��", "����", "����", "����", "��ʨ", "��", "��", "��ӥ",
        "����", "����", "���", "����", "�ڷ�", "����", "����", "����",
        "��ü", "����", "����", "����", "�촽", "��", "��ָ", "�ر�",
        "����", "����", "ҹ��", "��ݺ", "����", "����", "����", "����",
        "ҹ��", "����", "����", "����", "����", "����", "����", "����",
        "����", "����", "����", "ʨ��", "�Ի�", "����", "�Ͼ�", "��ĸ",
        "����", "����", "����", "��İ", "�ݺ�", "����", "����", "���",
        "�ɰ�", "����", "���", "����", "����", "���", "ʥĸ", "�Ĳ�",
        "��ʥ", "����", "����", "����", "����", "��ѩ", "Ʈѩ", "��ѩ",
        "��ѩ", "��ѩ", "ѩ��", "����", "ϼε", "��ϼ", "����", "嫺�",
        "ĵ��", "�ٺ�", "�׺�", "����", "����", "���", "��÷", "����",
        "��˼", "����", "����", "��ҩ", "�ž�", "õ��", "�¼�", "�ļ�",
        "ܽ��", "Ǿޱ", "����", "��ʦ", "ϴ��", "����", "����", "��ħ",
        "�L�", "�L��", "���", "���", "��ޱ", "ľ��", "���F", "̫�",
        "���Q", "���Q", "���Q", "���Q", "��ޱ", "��ޱ", "��ޱ", "��ޱ",
        "��ޱ", "���", "���", "���", "���", "���", "��з", "��ţ",
        "�۹�", "����", "����", "����", "����", "����", "����", "��ɽ",
        "����", "ժ��", "̽��", "����", "����", "��Ӱ", "��ħ", "����",
        "����", "ǧ��", "����", "ǧâ", "����", "ħ��", "���", "����",
        "�Ͼ�", "��ҳ", "����", "���", "����", "����", "����", "��ͼ",
        "Ѫն", "����", "����", "��â", "����", "����", "����", "����",
        "����", "Ӱ��", "���", "����", "˫��", "��ϼ", "����", "����",
        "����", "����", "�ۺ�", "��̳", "����", "����", "�ɷ�", "����",
        "��Ȫ", "�Ϻ�", "ƽԭ", "�ɶ�", "����", "ƽ��", "����", "����",
        "Ʈѩ", "���", "����", "���", "Ϧ��", 
});

string *nick_second=({
        "����", "����", "���", "����", "��ʥ", "����", "����", "����", 
        "ħ��", "����", "���", "����", "���", "�ɺ�", "����", "����",
        "���", "�ط�", "����", "����", "��Ӱ", "�Ƽ�", "����", "����",
        "����", "����", "��Ƽ", "����", "����", "̫Ԩ", "̫��", "����",
        "����", "�׵�", "����", "���", "����", "����", "����", "����",
        "����", "����", "����", "����", "���", "�׺�", "�Ϻ�", "����",
        "�̺�", "���", "��Ӱ", "��˪", "����", "����", "�ϵ�", "���",
        "����", "���", "����", "��Ȩ", "���", "����", "ҡ��", "����",
        "���", "����", "��а", "���", "���", "���", "����", "ҹ��",
        "����", "���", "����", "����", "����", "����", "����", "��ȸ",
        "�׻�", "����", "����", "����", "����", "����", "����", "����",
        "����", "����",
        "��",   "��",   "��",   "ǹ",   "��",   "��",   "��",   "��", 
        "��",   "��",   "��",   "��",   "��",
});

string create_nick()
{
        string nick1,nick2;
        nick1=nick_first[random(sizeof(nick_first))];
        nick2=nick_second[random(sizeof(nick_second))];
        return colors[random(13)]+nick1+colors[random(13)]+nick2;
}

void create()
{
        mapping name;
        int i = random(4);
        string nickname = create_nick();
        name = RNAME_D->get_random_name(i);
        set_name(name["name"], name["id"]);
        set("nickname",nickname+NOR);
        set("meitude", "peaceful");
        set("age", random(20)+25);
        set("str", 20);
        set("int", 20);
        set("con", 20);     
        set("dex", 20);
        set("combat_exp", 5000000);    
        set("max_qi", 20000);
        set("max_jing", 2000);
        set("max_jingli", 2000);
        set("max_neili", 5000);
        set("neili", 5000);
        set("chat_chance", 20);
        set("chat_msg", ({                                                                                                                      
                (: random_move :),           
        }));
        set("max_cure",5);    
        setup();
        carry_object(ARMOR_D("cloth"))->wear();
         add_money("silver",30+random(30));
        if (clonep())
        {
          this_object()->setparty(1,500,this_object()->query("combat_exp"));
          "/cmds/skill/skills"->main(this_object());
           call_out("dest", 300);
        }
}

void dest()
{       command("say ������������һս����������Ҫ���������ʹ˱��������");
        say(name()+"�������������ݶ������۶�ȥ��\n");
        destruct(this_object());
}

