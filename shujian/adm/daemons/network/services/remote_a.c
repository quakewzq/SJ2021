/*
 * File    : remote_a.c
 * Creator : ken@XAJH
 * When    : 98-1-15
 *
 * This protocol is used to send a intermud emote request.
 */
#undef DEBUG

inherit F_CLEAN_UP;
inherit F_DBASE;

#include <net/dns.h>
#include <net/macros.h>

void create() {
	seteuid(ROOT_UID);
	set("channel_id", "网路频道");
}

void incoming_request(mapping info)
{
	object ob;
	string msg;
	mapping minfo;

	if (! ACCESS_CHECK(previous_object())) return;

	minfo = (mapping) DNS_MASTER->query_mud_info(info["NAME"]);
	if (! minfo) return;

	if (stringp(info["PORTUDP"]) && stringp(info["HOSTADDRESS"])) 
	{
#ifdef DEBUG
	message("wizard",sprintf("%s %s回复本地emote请求。\n",info["HOSTADDRESS"],info["PORTUDP"]),users() ); 
#endif
		if (info["NAME"] == Mud_name())	return;		
		if (! DNS_MASTER->dns_mudp(info["NAME"]))
			PING_Q->send_ping_q(info["HOSTADDRESS"], info["PORTUDP"]);
		ob = find_player(lower_case(info["SOURCE_ID"]));
		if (! ob) return;		
		msg = EMOTE_D->do_emote(ob, lower_case(info["MSG"]), info["TARGET"], 4,
                                        info["NAME"]);		
		if (! stringp(msg) || ! strlen(msg))
			return;
		if (! userp(ob)) return;
#ifdef DEBUG
	message("wizard",sprintf("呼叫channeld 发送信息。\n"),users() ); 
#endif
		CHANNEL_D->do_remote_channel(ob, info["CHANNEL"], msg);
	}
}
