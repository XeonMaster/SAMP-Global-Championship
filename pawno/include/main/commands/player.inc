//Player Commands

CMD:spawn(playerid){
	if(PlayerData[playerid][event_active] != AREA_NONE) return SendClientMessage(playerid,COLOR_RED,"You can't respawn during the tournament");
	SpawnPlayer(playerid);
	return 1;
}