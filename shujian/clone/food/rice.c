// rice.c 大米饭

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("米饭",({"mi fan", "rice", "fan" }));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "一碗刚从锅里盛出来的大米饭，还冒着热气～～～\n");
		set("unit", "碗");
		set("value", 0);
		set("food_remaining", 5);
		set("food_supply", 40);
	}
}
