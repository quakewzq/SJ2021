// bing.c �ٱ�

inherit NPC;

void create()
{
        set_name("�ٱ�", ({ "guan bing", "bing" }));
        set("age", 22);
        set("gender", "����");
        set("long", "��Ȼ�ٱ������ղ��ܺ�������ʿ��ȣ��������ǽ��������˶�������\n");
        set("attitude", "peaceful");

        set("str", 24);
        set("dex", 16);
        set("combat_exp", 10000);
        set("shen_type", 1);

        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set_skill("parry", 40);
        set_skill("blade", 40);
        set_skill("force", 40);
        set_temp("apply/attack", 40);
        set_temp("apply/defense", 40);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 40);

        set("chat_chance_combat", 10);
        set("chat_msg_combat", ({
                "�ٱ��ȵ���վס����ʲô�ģ�\n",
                "�ٱ��ȵ����󵨵��񣬾����췴���ɣ�\n",
        }));
        setup();
        carry_object(BINGQI_D("gangdao"))->wield();
        carry_object(ARMOR_D("junfu"))->wear();
}

void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) && living(this_object()) &&
                (int)ob->query_condition("killer")) {
                remove_call_out("kill_ob");
                call_out("kill_ob", 0, ob);
        }
}

int accept_fight(object me)
{
        command("say ��ү����������ɱ�ţ��������㵹ù��\n");
        if (!is_killing(me->query("id")))
                me->add_condition("killer", 15);
        kill_ob(me);
        return 1;
}