import NetMessages
from Helpers import Struct

# Helbreath Packet definitions

REQUEST_REGISTER_GAMESERVER_MAP = Struct(
	(
		('map_name', '11s'), # Shouldn't it be like 10s? Stupid koreans...
	)
)

REQUEST_REGISTER_GAMESERVER = Struct(
	(
		('MsgID', 'I'),
		('MsgType', 'H'),
		('server_name', '10s'),
		('address', '16s'),
		('port', 'H'),
		('received_configs', '?'), # Do we have configs?
		('map_count', 'B'),
		('server_id', 'H'),
		('maps', REQUEST_REGISTER_GAMESERVER_MAP, 'map_count')
	),
	MsgID = NetMessages.MSGID_REQUEST_REGISTERGAMESERVER,
	MsgType = NetMessages.DEF_LOGRESMSGTYPE_CONFIRM
)

RESPONSE_REGISTER_GAMESERVER = Struct(
	(
		('server_id', 'H'),
	)
)

REQUEST_PLAYERDATA = Struct(
	(
		('MsgID', 'I'),
		('MsgType', 'H'),
		('char_name', '10s'),
		('account_name', '10s'),
		('account_password', '10s'),
		('address', '15s'),
		('account_status', 'x') # From the old 2.20 days, I think. Now obsolete.
	),
	MsgID = NetMessages.MSGID_REQUEST_PLAYERDATA,
	MsgType = NetMessages.DEF_MSGTYPE_CONFIRM, 
)

PLAYERDATA_ITEM = Struct(
	(
		('name', '20s'),
		('count', 'i'),
		('type', 'h'),
		('id1', 'i'),
		('id2', 'i'),
		('id3', 'i'),
		('color', 'B'),
		('effect1', 'h'),
		('effect2', 'h'),
		('effect3', 'h'),
		('lifespan', 'h'),
		('attribute', 'I'),
		('equip', '?'),
		('x', 'h'),
		('y', 'h'),
		('item_id', 'I'),
	)
)

PLAYERDATA_SKILL_MASTERY = Struct(
	(
		('mastery', 'B'),
	)
)

PLAYERDATA_SKILL_SSN = Struct(
	(
		('ssn', 'I'),
	)
)

PLAYERDATA_BANKITEM = Struct(
	(
		('name', '20s'),
		('count', 'i'),
		('type', 'h'),
		('id1', 'i'),
		('id2', 'i'),
		('id3', 'i'),
		('color', 'B'),
		('effect1', 'h'),
		('effect2', 'h'),
		('effect3', 'h'),
		('lifespan', 'h'),
		('attribute', 'I'),
		('item_id', 'I'),
	)
)

RESPONSE_PLAYERDATA = Struct(
	(
		('char_name', '10s'),
		('account_status', 'x'), # Outdated?
		('guild_status', 'x'), # Outdated?
		('map_name', '10s'),
		('x', 'h'),
		('y', 'h'),
		('sex', 'B'),
		('skin', 'B'),
		('hair_style', 'B'),
		('hair_color', 'B'),
		('underwear', 'B'),
		('guild_name', '20s'),
		('guild_rank', 'b'),
		('hp', 'I'),
		('level', 'H'),
		('str', 'B'),
		('vit', 'B'),
		('dex', 'B'),
		('int', 'B'),
		('mag', 'B'),
		('chr', 'B'),
		('luck', 'B'),
		('exp', 'I'),
		('magic_mastery', '100s'),
		('skill_mastery', PLAYERDATA_SKILL_MASTERY, 24),
		('location', '10s'),
		('mp', 'I'),
		('sp', 'I'),
		('lu_pool', 'x'),
		('ek_count', 'I'),
		('pk_count', 'I'),
		('reward_gold', 'I'),
		('skill_ssn', PLAYERDATA_SKILL_SSN, 24),
		('padding1', '4x'), #
		('hunger_status', 'B'),
		('admin_user_level', 'B'),
		('timeleft_shutup', 'I'),
		('timeleft_rating', 'I'),
		('rating', 'i'),
		('guild_guid', 'i'),
		('down_skill_index', 'b'),
		('char_id', 'I'),
		('char_idnum1', 'I'),
		('char_idnum2', 'I'),
		('char_idnum3', 'I'),
		('block_date', '20s'),
		('questnum', 'h'),
		('questcount', 'h'),
		('questrewtype', 'h'),
		('questrewammount', 'i'),
		('contribution', 'i'),
		('questid', 'i'),
		('questcompleted', 'B'),
		('leftforcerecalltime', 'i'),
		('leftfirmstaminartime', 'i'),
		('eventid', 'i'),
		('leftsac', 'h'),
		('fightnum', 'B'),
		('fightdate', 'i'),
		('fightticket', 'B'),
		('leftspecialtime', 'i'),
		('warcon', 'i'),
		('lockedmapname', '10s'),
		('lockedmaptime', 'i'),
		('crujob', 'B'),
		('cruconstructpoint', 'i'),
		('cruid', 'i'),
		('leftdeadpenaltytime', 'i'),
		('partyid', 'i'),
		('gizonitemupgradeleft', 'h'),
		('item_count', 'B'),
		('items', PLAYERDATA_ITEM, 'item_count'),
		('items_pad', 'x'),
		('bankitem_count', 'B'),
		('bank_items', PLAYERDATA_BANKITEM, 'bankitem_count'),
		('profile', '10s')
	)
)

PLAYERCHARACTERCONTENTS = Struct(
	(
		('MsgID', 'I'),
		('MsgType', 'H'),
		('hp', 'I'),
		('mp', 'I'),
		('sp', 'I'),
		('defense_ratio', 'I'),
		('hit_ratio', 'I'),
		('level', 'I'),
		('str', 'I'),
		('int', 'I'),
		('vit', 'I'),
		('dex', 'I'),
		('mag', 'I'),
		('chr', 'I'),
		('lu_pool', 'h'),
		('var', 'x'), # cVar (?)
		('unknown0', '4x'), # Unknown vars
		('exp', 'I'),
		('ek_count', 'I'),
		('pk_count', 'I'),
		('reward_gold', 'I'),
		('location', '10s'),
		('guild_name', '20s'),
		('guild_rank', 'i'),
		('leftsac', 'B'),
		('fightzone_number', 'i'),
	),
	MsgID = NetMessages.MSGID_PLAYERCHARACTERCONTENTS,
	MsgType = NetMessages.DEF_MSGTYPE_CONFIRM
)


PLAYERITEMLISTCONTENT_ITEM = Struct(
	(
		('name', '20s'),
		('count', 'i'),
		('type', 'B'),
		('equip_pos', 'B'),
		('equipped', '?'),
		('level_limit', 'H'),
		('gender_limit', 'B'),
		('lifespan', 'H'),
		('weight', 'H'),
		('sprite', 'H'),
		('sprite_frame', 'H'),
		('color', 'B'),
		('effect2', 'B'),
		('attribute', 'I')
	)
)

PLAYERITEMLISTCONTENT_BANKITEM = Struct(
	(
		('name', '20s'),
		('count', 'i'),
		('type', 'B'),
		('equip_pos', 'B'),
		('level_limit', 'H'),
		('gender_limit', 'B'),
		('lifespan', 'H'),
		('weight', 'H'),
		('sprite', 'H'),
		('sprite_frame', 'H'),
		('color', 'B'),
		('effect2', 'B'),
		('attribute', 'I')
	)
)

PLAYERITEMLISTCONTENT = Struct(
	(
		('MsgID', 'I'),
		('MsgType', 'H'),
		('item_count', 'B'),
		('items', PLAYERITEMLISTCONTENT_ITEM, 'item_count'),
		('bankitem_count', 'B'),
		('bankitems', PLAYERITEMLISTCONTENT_BANKITEM, 'bankitem_count'),
		('magicmastery', '100s'), # TODO: rewrite as 100 bool
		('skills', PLAYERDATA_SKILL_MASTERY, 24) # Array of single byte
	),
	MsgID = NetMessages.MSGID_PLAYERITEMLISTCONTENTS,
	MsgType = NetMessages.DEF_MSGTYPE_CONFIRM
)

ENTERGAME_CONFIRM = Struct(
	(
		('MsgID', 'I'),
		('MsgType', 'H'),
		('account_name', '10s'),
		('account_password', '10s'),
		('server_name', '10s'),
		('client_ip', '16s'),
		('level', 'I')
	),
	MsgID = NetMessages.MSGID_ENTERGAMECONFIRM,
	MsgType = NetMessages.DEF_MSGTYPE_CONFIRM
)