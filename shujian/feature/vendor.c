// vendor.c 卖主

// Modify by tiantian@sj

// Modify by augx@sj  9/4/2001

// Modify by LinuX@SJ 3/2/2004

#include <dbase.h>



int query_goods_value(string goods, int number)

{

	object me = this_player();

	int value, trade_level;

	int cur;



	value = ((object)goods)->query("value");

	trade_level = me->query_skill("trade", 1) / 5;

	if (trade_level > 40) trade_level = 40;

	value = value * (140 - trade_level) / 100;



	cur=query_temp("vendor_goods/"+goods);

	if( cur!=number )

		value += value*cur/number;

	

	if(me->query("quest/wxbjiebai") && query("name")=="韦小宝" )

		value = value * 9 /10;//结拜兄弟打个折		

	if(value<0) value = 1;

	return value;

}



string is_vendor_good(string arg)

{

	mapping *goods;

	int i;



	if (arrayp(goods = query("vendor_goods")))

		for (i = 0; i < sizeof(goods); i++)

			if (goods[i]["name"]->id(arg) &&

				goods[i]["number"] != query_temp("vendor_goods/"+goods[i]["name"]))

				return goods[i]["name"];

	return "";

}



void reset()

{

	this_object()->delete_temp("vendor_goods");

}



int do_list(string arg)

{

	mapping *goods;

	int i;

	object me = this_player();



	if (!living(this_object()))

	{

		tell_object(me,"还是等对方醒来再说吧。\n");

		return 1;

	}



	if (!(int)query("move_seller") && base_name(environment()) != query("startroom"))

	{	

		command("say 这……我这次是出来游玩的，你下次来吧。");

		return 1;

	}

	



	if (arrayp(goods = query("vendor_goods")))

	{

		write(query("name") + "目前出售以下货物：\n");

                write("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");

		write("┃  货  物                          价  格                        库存/总量 ┃\n");

		write("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");

		for (i = 0; i < sizeof(goods); i++)

                   write(sprintf("┃%-30s%-34s%4d/%4d ┃\n", goods[i]["name"]->short(),
				MONEY_D->price_str(query_goods_value(goods[i]["name"], goods[i]["number"])),

				goods[i]["number"]-query_temp("vendor_goods/"+goods[i]["name"]),

				goods[i]["number"])

			);

		write("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

		return 1;

	}

}



int do_buy(string arg)

{

	int i, improve;

	string ob_file;

	object ob;

	object me = this_player();

	mapping goods;



	if (!living(this_object()))

	{

		tell_object(me,"还是等对方醒来再说吧。\n");

		return 1;

	}



	if (me->is_busy() || me->is_fighting()){

		tell_object(me,"你正忙着呢。\n");

		return 1;

	}



	if (query_temp("busy")){

		tell_object(me,"哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");

		return 1;

	}



	if (!(int)query("move_seller") && base_name(environment()) != query("startroom")){	

		command("say 这……我这次是出来游玩的，你下次来吧。");

		return 1;

	}

	

	if (!arg) {	

		command("say "+me->name(1)+",你想买什么？");

		return 1;

	}



	if ((ob_file = is_vendor_good(arg)) == "")

	{	

		command("say 你想买的东西我这里没有。");

		return 1;

	}



	goods=query("vendor_goods");

	for(i=0;i<sizeof(goods);i++)

		if(goods[i]["name"]==ob_file)

			break;



	ob = new(ob_file);

	if (query("name") == "韦小宝"){

		if (query_goods_value(ob_file,goods[i]["number"]) > me->query("balance"))	

		{

		tell_object(me,"您没有这么多存款。\n");

		return 1;

		}



		if (!ob->move(me)) {

			destruct(ob);

			return 0;

		}

		if(me->query("quest/wxbjiebai") && query("name")=="韦小宝" )

		message_vision("$N哈哈大笑，自家兄弟便宜点卖了。\n",this_object());

		message_vision("$N以"+MONEY_D->price_str(query_goods_value(ob_file,goods[i]["number"]))+"的价格从$n那里买下了一" + ob->query("unit") +

			ob->name() + "，该钱直接从银行存款扣除。\n", me, this_object());

			CHANNEL_D->do_channel( this_object(), "rumor",

		sprintf("听说有人从韦小宝那里买了一%s！", ob->query("unit")+ob->name()));

		me->add("balance",-query_goods_value(ob_file,goods[i]["number"]));

		improve = 40 - me->query("pur");

		me->improve_skill("trade", improve + random(improve));

		add_temp("vendor_goods/"+ob_file,1);

		

		

	}

	else{



	switch(MONEY_D->player_pay(me, i = query_goods_value(ob_file,goods[i]["number"]))) {

	case 0:

		destruct(ob);

		command("say 穷光蛋，一边呆着去！");

		return 1;

	case 2:

		destruct(ob);

		command("say 您的零钱不够了，银票又没人找得开。");

		return 1;

	default:

		if (!ob->move(me)) {

			destruct(ob);

			return 0;

		}

		message_vision("$N以"+MONEY_D->price_str(i)+"的价格从$n那里买下了一" + ob->query("unit") +

			ob->name() + "。\n", me, this_object());

		improve = 40 - me->query("pur");

		me->improve_skill("trade", improve + random(improve));

		add_temp("vendor_goods/"+ob_file,1);

	}

	}

	set_temp("busy", 1);

	call_out("delete_temp", 1, "busy");



	return 1;

}

