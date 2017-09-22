
//first dialog_id = ProtDialog !
enum dialogs_id {
	DIALOG_LOGIN = ProtDialog,
	DIALOG_EXAMPLE_1,
	DIALOG_EXAMPLE_2,
	DIALOG_EXAMPLE_3
}

enum e_PlayerData {
	allowedLevel,		//Admin Level from database
	adminLevel,			//Admin Level OnLogin
	p_money,			//Player Money
	p_score,			//Player Score
	bool:isRcon,		//logged in as rcon
	
	bool:DialogIsUse,
	bool:uglyRejoinHack,
	
	area_active,
	event_active,
	
	PlayerBar:ConquerorBar,
	Float:ConquerorHealth,
	bool:ConquerorStatus,
	
	last_missile_player,
	last_missile_shot,
	lastWeaponUsed,
	
	cp_gpci[50],
	cp_ip[20]
}
