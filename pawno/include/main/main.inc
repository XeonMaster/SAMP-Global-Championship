public OnGameModeInit(){
	
	printf("Load GameMode...");
	
	if(!GetADMKey()){
		printf("Cannot Get ADM Key.");
		SendRconCommand("exit");
		return 0;
	}
	
	ChangeRconPassword();
	
	//SAM Config
	ToggleUseTeamKnifeShoot(true);
	ToggleUseTeamMagicShoot(true);
	ToggleKnifeShootForAll(false);
	ToggleMissileAutoDisarm(true);
	
	UpdateNickCharacters();
	
	//Plugins Config
	Streamer_TickRate(50);
	Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT,800,-1);
	YSF_EnableNightVisionFix(true);
	
	//Server Config
	SetGameModeText("Championship 2017");
	SendRconCommand("language English");
	new MapName[64];
	format(MapName,sizeof(MapName),"mapname Championship v" #GMVERSION);
	SendRconCommand(MapName);
	
	//SA:MP Config
	UsePlayerPedAnims();
	DisableInteriorEnterExits();
	EnableStuntBonusForAll(false);
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_GLOBAL);
	SetObjectsDefaultCameraCol(0);
	
	for(new skinid = 0; skinid <= 311; skinid++){
		if(skinid != 74){
			AddPlayerClass(skinid,ClassSpawn[T3D:X],ClassSpawn[T3D:Y],ClassSpawn[T3D:Z],ClassSpawn[T3D:A],0,0,0,0,0,0);
		}
	}

	printf("Connect to database...");
	if(!ConnectDataBase()){
		SendRconCommand("exit");
		return 0;
	}
	
	return 1;
}

public OnGameModeExit(){
	
	if(MySQLConn){
		mysql_close(MySQLConn);
	}
	return 1;
}

public OnRuntimeError(code, &bool:suppress){

	return 1;
}

public Streamer_OnPluginError(error[]){

	return 1;
}

public OnPlayerRequestClass(playerid, classid){

	return 1;
}

public OnPlayerRequestSpawn(playerid){

	return 1;
}

public OnPlayerEnterGangZone(playerid, zoneid){

	return 1;
}

public OnPlayerLeaveGangZone(playerid, zoneid){

	return 1;
}

public OnPlayerConnect(playerid){
	new version[10], PlayerName[32], p_country[64], p_isp[100], p_city[64];
	
	//Reset Variables
	PlayerData[playerid] = ConstructPlayerData();
	
	DisableConsoleMSGsForPlayer(playerid);
	GetPlayerName(playerid,PlayerName,sizeof(PlayerName));
	GetPlayerVersion(playerid,version,sizeof(version));
	GetPlayerIp(playerid,PlayerData[playerid][cp_ip],20);
	gpci(playerid,PlayerData[playerid][cp_gpci],50);
	
	GetPlayerCountry(playerid,p_country);
	GetPlayerISP(playerid,p_isp);
	GetPlayerCity(playerid,p_city);
	
	if(ContainsIP(PlayerName)){
		BanEx(playerid,"[HD] Advertisement");
		return 0;
	}
	
	Streamer_ToggleIdleUpdate(playerid,1);
	SetPlayerTeam(playerid,NO_TEAM);
	
	if(Firewall_CheckPlayer(playerid,PlayerName,PlayerData[playerid][cp_ip],PlayerData[playerid][cp_gpci],version)) return 0;
	
	if(!IsPlayerNPC(playerid)){
		printf("[GPCI] [%s](%d)%s '%s' '%s'",PlayerData[playerid][cp_ip],playerid,GetPlayerNick(playerid),PlayerData[playerid][cp_gpci],version);
		printf("[LOCATION] [%s](%d)%s '%s' '%s' '%s'",PlayerData[playerid][cp_ip],playerid,GetPlayerNick(playerid),p_country,p_isp,p_city);
	}
	
	//code
	
	PlayerData[playerid][uglyRejoinHack] = true;
	
	return 1;
}

public OnPlayerDisconnect(playerid, reason){
	if(!PlayerData[playerid][uglyRejoinHack]) return 1;

	TogglePlayerConqueror(playerid,false);
	
	//code
	
	PlayerData[playerid][uglyRejoinHack] = false;
	return 1;
}

public OnPlayerSpawn(playerid){

	TogglePlayerConqueror(playerid,false);
	PlayerData[playerid][last_missile_player] = INVALID_PLAYER_ID;
	DisableRemoteVehicleCollisions(playerid,0);
	
	SelectPlayerArea(playerid,GlobalAreaSelected);
	
	return 1;
}
	
public OnPlayerDeath(playerid, killerid, reason){
	if(IsPlayerNPC(playerid)) return 1;
	
	new bool:no_missile = true;
	if(PlayerData[playerid][last_missile_player] != INVALID_PLAYER_ID && reason > 46 && playerid != killerid){
		if(GetTickCount()-PlayerData[playerid][last_missile_shot] < 2000){
			no_missile = false;
			killerid = PlayerData[playerid][last_missile_player];
			reason = 51;
		}
	}
	if(killerid != INVALID_PLAYER_ID){
		if(no_missile && reason == 51){
			reason = PlayerData[killerid][lastWeaponUsed];
		}
	}
	
	ResetPlayerWeapons(playerid);
	if(killerid == INVALID_PLAYER_ID){
		switch(reason){
			case 0..34: {
				new buffer[200];
				format(buffer,sizeof buffer,"[HACK DETECT] [%s](%d)%s used FakeKill Reason: %d",GetPlayerIP(playerid),playerid,GetPlayerNick(playerid),reason);
				WriteLog(buffer,LOG_FILE_HACK);
				MsgToAdmins(COLOR_RED,buffer,LEVEL_ADMIN);
				BanEx(playerid,"[HD] FakeKill");
			}
		}
	}
	
	if(reason != 53 && reason != 47 && reason != 255){
		SendDeathMessage(killerid, playerid, reason);
	}
	
	return 1;
}

public OnPlayerText(playerid, text[]){

	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate){

	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid){

	return 1;
}

public OnPlayerEnterCheckpoint(playerid){

	return 1;
}

public OnPlayerPickUpDynamicPickup(playerid, pickupid){
	CheckPlayerWeaponPickup(playerid,pickupid);

	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid){

	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys){

	if(Tryg3D_KeyPressed(KEY_FIRE)){
		PlayerData[playerid][lastWeaponUsed] = GetPlayerWeapon(playerid);
	}
	
	//Marica Mortar Control
	if(IsToggleVehicleMegaMissile(GetPlayerVehicleID(playerid))){
		if(Tryg3D_KeyPressed(KEY_ANALOG_UP)){
			new vid = GetPlayerVehicleID(playerid), Float:val = GetVehicleMegaMissileDistance(vid), buf[128];
			val += 5.0;
			if(val > 800.0) val = 800.0;
			SetVehicleMegaMissileDistance(vid,val);
			format(buf,sizeof buf,"Mortar Distance: ~g~%.0f",val);
			GameTextForPlayer(playerid,buf,1000,4);
		} else if(Tryg3D_KeyPressed(KEY_ANALOG_DOWN)){
			new vid = GetPlayerVehicleID(playerid), Float:val = GetVehicleMegaMissileDistance(vid), buf[128];
			val -= 5.0;
			if(val < 50.0) val = 50.0;
			SetVehicleMegaMissileDistance(vid,val);
			format(buf,sizeof buf,"Mortar Distance: ~g~%.0f",val);
			GameTextForPlayer(playerid,buf,1000,4);
		} else if(Tryg3D_KeyPressed(KEY_ANALOG_RIGHT)){
			new vid = GetPlayerVehicleID(playerid), Float:val = GetVehicleMegaMissileHeight(vid), buf[128];
			val += 5.0;
			if(val > 400.0) val = 400.0;
			SetVehicleMegaMissileHeight(vid,val);
			format(buf,sizeof buf,"Mortar Height: ~g~%.0f",val);
			GameTextForPlayer(playerid,buf,1000,4);
		} else if(Tryg3D_KeyPressed(KEY_ANALOG_LEFT)){
			new vid = GetPlayerVehicleID(playerid), Float:val = GetVehicleMegaMissileHeight(vid), buf[128];
			val -= 5.0;
			if(val < 25.0) val = 25.0;
			SetVehicleMegaMissileHeight(vid,val);
			format(buf,sizeof buf,"Mortar Height: ~g~%.0f",val);
			GameTextForPlayer(playerid,buf,1000,4);
		}
	} else if(IsToggleVehicleMortarMissile(GetPlayerVehicleID(playerid))){
		if(Tryg3D_KeyPressed(KEY_ANALOG_UP)){
			new vid = GetPlayerVehicleID(playerid), Float:val = GetVehicleMortarMissileDistance(vid), buf[128];
			val += 5.0;
			if(val > 600.0) val = 600.0;
			SetVehicleMortarMissileDistance(vid,val);
			format(buf,sizeof buf,"Mortar Distance: ~g~%.0f",val);
			GameTextForPlayer(playerid,buf,1000,4);
		} else if(Tryg3D_KeyPressed(KEY_ANALOG_DOWN)){
			new vid = GetPlayerVehicleID(playerid), Float:val = GetVehicleMortarMissileDistance(vid), buf[128];
			val -= 5.0;
			if(val < 50.0) val = 50.0;
			SetVehicleMortarMissileDistance(vid,val);
			format(buf,sizeof buf,"Mortar Distance: ~g~%.0f",val);
			GameTextForPlayer(playerid,buf,1000,4);
		} else if(Tryg3D_KeyPressed(KEY_ANALOG_RIGHT)){
			new vid = GetPlayerVehicleID(playerid), Float:val = GetVehicleMortarMissileHeight(vid), buf[128];
			val += 5.0;
			if(val > 300.0) val = 300.0;
			SetVehicleMortarMissileHeight(vid,val);
			format(buf,sizeof buf,"Mortar Height: ~g~%.0f",val);
			GameTextForPlayer(playerid,buf,1000,4);
		} else if(Tryg3D_KeyPressed(KEY_ANALOG_LEFT)){
			new vid = GetPlayerVehicleID(playerid), Float:val = GetVehicleMortarMissileHeight(vid), buf[128];
			val -= 5.0;
			if(val < 25.0) val = 25.0;
			SetVehicleMortarMissileHeight(vid,val);
			format(buf,sizeof buf,"Mortar Height: ~g~%.0f",val);
			GameTextForPlayer(playerid,buf,1000,4);
		}
	}
	
	return 1;
}


public OnPlayerUpdate(playerid){

	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid){

	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source){

	return 1;
}

public OnPlayerCommandReceived(playerid, cmdtext[]){

	return 1;
}

public OnPlayerCommandPerformed(playerid, cmdtext[], success){

	return 1;
}

public OnPlayerEnterDynamicArea(playerid,areaid){

	return 1;
}

public OnPlayerLeaveDynamicArea(playerid,areaid){

	return 1;
}

public OnPlayerEnterDynamicCP(playerid,checkpointid){

	return 1;
}

public OnPlayerLeaveDynamicCP(playerid,checkpointid){

	return 1;
}

public OnPlayerEnterDynamicRaceCP(playerid, checkpointid){

	return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ){

	return 1;
}

public OnMissileDestroy(mobid,Float:x,Float:y,Float:z,type,killerid,byplayerid){
	if(type == MISSILE_DESTROY_TYPE_DETECT && killerid != INVALID_PLAYER_ID){
		PlayerData[killerid][last_missile_shot] = GetTickCount();
		PlayerData[killerid][last_missile_player] = byplayerid;
	}
	return 1;
}

public OnMissileDetectPlayer(playerid,killerid){
	if(killerid != INVALID_PLAYER_ID){
		PlayerData[playerid][last_missile_shot] = GetTickCount();
		PlayerData[playerid][last_missile_player] = killerid;
	}
    return 1;
}

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart){

	return 1;
}

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart){
	new Float:hlpl, Float:arpl, vmodel = GetVehicleModel(GetPlayerVehicleID(playerid));
	
	GetPlayerHealth(playerid,hlpl);
	GetPlayerArmour(playerid,arpl);
	
	if(ContainInSeries(vmodel,432,425,520,476,548)){
		SetPlayerHealth(playerid,hlpl);
		SetPlayerArmour(playerid,arpl);
	}
	
	//Conqueror Shield
	if(PlayerData[playerid][ConquerorStatus]){
		if(weaponid != 38 && weaponid != 49 && weaponid != 50 && weaponid != 54){
			PlayerData[playerid][ConquerorHealth] -= amount;
		} else {
			amount = 0.0;
		}
		if(PlayerData[playerid][ConquerorHealth] <= 0.0){
			PlayerData[playerid][ConquerorHealth] = 0.0;
			TogglePlayerConqueror(playerid,false);
			SetPlayerHealth(playerid,100.0);
		} else {
			SetPlayerHealth(playerid,100000.0);
			SetPlayerProgressBarValue(playerid,PlayerData[playerid][ConquerorBar],floatabs(PlayerData[playerid][ConquerorHealth]));
		}
		if(issuerid != INVALID_PLAYER_ID){
			if(PlayerData[playerid][ConquerorHealth] > 0){
				if(weaponid != 38 && weaponid != 49 && weaponid != 50 && weaponid != 54){
					format(gstr,sizeof(gstr),"~g~%.1f Shield~n~~r~~h~~h~-%.1f Shield",PlayerData[playerid][ConquerorHealth],amount);
				} else {
					format(gstr,sizeof(gstr),"~g~%.1f Shield~n~~r~~h~~h~Defend",PlayerData[playerid][ConquerorHealth]);
				}
			} else {
				format(gstr,sizeof(gstr),"~g~0 Shield~n~~r~~h~~h~-%.1f Shield",amount);
			}
			GameTextForPlayer(issuerid,gstr,500,4);
		}
	}
	
	return 1;
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ){

	return 1;
}





