// Room: /d/city/duchang4.c
// This is a room made by roommaker. write by Fan. :)
inherit ROOM;
void create()
{
	set("short", "�ĳ�");
	set("long", @LONG
����Χ�ź�ѹѹ�Ķ�ͽ��ߺ��������̾����������������������Ц��������
ž��������ʹ��Ķ��伸���޷����ܣ������Ե�ǽ������һ��ֽ(paper)��
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"chatroom",
  "west" : __DIR__"chat-dc3",
  "east" : __DIR__"chat-dc4",
]));

    set("item_desc", ([
                "paper": @TEXT
    ���ӵĶķ���
    bet <����> <����> <��������>
    ���ࣺ��������������������
    ������      ��С    ��  ����������  һ��һ
    ����        �Ĵ�    ��������������  һ��һ
    ������      ��Χ��  ����������ͬ�㣩һ����ʮ��
    ��������    �ĵ���                  һ����
    ���ӣ�
    bet 0 50 silver  ѹ��ʮ��������С��
TEXT
        ]) );

	setup();
}
//�Ǿ���
int is_mirror() { return 1; }