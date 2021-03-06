// shang_gp.c
// Created by Numa 19991022

#include <ansi.h>
inherit F_MASTER;
inherit NPC;

void create()
{
  set_name("上官鹏", ({ "shangguan peng", "peng","shangguan"}));
  set("long", "只见他长手长脚，双目精光灿烂，甚有威势。\n");
  set("title",HIY"日月神教  "HIR"监狱总管"NOR);
  set("gender", "男性");
  set("age", 40);
  set("attitude", "peaceful");
  set("shen_type", -1);
  set("str", 22);
  set("int", 25);
  set("con", 21);
  set("dex", 30);
        
  set("max_qi", 3000);
  set("max_jing", 2200);
	set("eff_jingli", 2200);
  set("jiali", 50);
  set("combat_exp", 1800000);
  set("shen", -5000);

	set_temp("apply/attack", 40);
	set_temp("apply/defence", 40);

	set_skill("cuff",200);
	set_skill("leg",200);
  set_skill("dodge",200);
	set_skill("ding-dodge", 200);
	set_skill("literate", 120);
	set_skill("force", 200);
	set_skill("tianmo-gong", 200);
	set_skill("parry", 200);
	set_skill("tianmo-zhang", 200);
	set_skill("tianmo-shou", 200);

  map_skill("dodge", "ding-dodge");
  map_skill("force", "tianmo-gong");
	map_skill("parry", "tianmo-zhang");
	map_skill("strike", "tianmo-zhang");
	prepare_skill("strike", "tianmo-zhang");
	create_family("日月神教",9,"弟子");

        setup();
        
	carry_object("/clone/misc/cloth")->wear();        
}
