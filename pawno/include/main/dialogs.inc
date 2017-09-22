public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]){
	if(IsPlayerNPC(playerid)) return 1;
	if(!PlayerData[playerid][DialogIsUse]) return 1;
	PlayerData[playerid][DialogIsUse] = false;
	
	
	
	return 1;
}