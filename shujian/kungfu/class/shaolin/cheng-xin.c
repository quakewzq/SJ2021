// Npc: /kungfu/class/shaolin/cheng-xin.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;


void create()
{
	set_name("����", ({
		"chengxin luohan",
		"chengxin",
		"fuhu",
		"luohan",
	}));
	set("long",
		"����һλ�뷢���׵���ɮ������һϮ��ߺڲ����ġ��������ݸߣ�\n"
		"̫��Ѩ�߸߹����ƺ����������书��\n"
	);

	set("nickname", "�����޺�");
	set("gender", "����");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 60);
	set("shen", 5000);
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 25);
	set("max_qi", 2500);
	set("max_jing", 1000);
	set("neili", 2500);
	set("max_neili", 2500);
	set("jiali", 100);
	set("combat_exp", 600000);
    set("unique", 1);

	set_skill("force", 100);
	set_skill("yijin-jing", 100);
	set_skill("dodge", 100);
	set_skill("shaolin-shenfa", 100);
	set_skill("hand", 100);
	set_skill("qianye-shou", 100);
	set_skill("parry", 100);
	set_skill("buddhism", 100);
	set_skill("literate", 100);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("hand", "qianye-shou");
	map_skill("parry", "qianye-shou");

	prepare_skill("hand", "qianye-shou");

	create_family("������", 37, "����");

	setup();

        carry_object("/d/shaolin/obj/cheng-cloth")->wear();
}


#include "/kungfu/class/shaolin/cheng.h"
