stock GetPlayerNick(playerid){
	new pnick[MAX_PLAYER_NAME];
	GetPlayerName(playerid,pnick,sizeof(pnick));
	return pnick;
}

stock GetPlayerID(name[]){
	for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++){
		if(IsPlayerConnected(i)){
			if(!strcmp(name,GetPlayerNick(i),false)) return i;
		}
	}
	return INVALID_PLAYER_ID;
}


stock GetPlayerIP(playerid){
	new szIP[16];
	GetPlayerIp(playerid,szIP,sizeof szIP);
	return szIP;
}

stock UpdateNickCharacters(){
	AllowNickNameCharacter('{',true);
	AllowNickNameCharacter('}',true);
	AllowNickNameCharacter('>',true);
	AllowNickNameCharacter('<',true);
	AllowNickNameCharacter('!',true);
	AllowNickNameCharacter('#',true);
	AllowNickNameCharacter(':',true);
	AllowNickNameCharacter('*',true);
	AllowNickNameCharacter('~',true);
}

stock PlaySound(playerid,soundid,bool:pVectorInc = false){
	new pVector[Vectors3D];
	if(pVectorInc){
		GetPlayerPos(playerid,pVector[T3D:X],pVector[T3D:Y],pVector[T3D:Z]);
	}
	PlayerPlaySound(playerid,soundid,pVector[T3D:X],pVector[T3D:Y],pVector[T3D:Z]);
}

stock RemovePlayerWeapon(playerid,weaponid){
	new plyWeapons[12], plyAmmo[12];
	for(new slot = 0; slot < 12; slot++){
		new wep,ammo;
		GetPlayerWeaponData(playerid,slot,wep,ammo);
		if(wep != weaponid)
			GetPlayerWeaponData(playerid,slot,plyWeapons[slot],plyAmmo[slot]);
		}
		ResetPlayerWeapons(playerid);
		for(new slot = 0; slot < 12; slot++){
		GivePlayerWeapon(playerid,plyWeapons[slot],plyAmmo[slot]);
	}
}

stock fcreate(const name[]){
	if(!fexist(name)){
		new File:cfile = fopen(name,io_readwrite);
		fwrite(cfile,"");
		fclose(cfile);
		return 1;
	}
	return 0;
}

//Conqueror Shield "green bar :D"
stock TogglePlayerConqueror(playerid,bool:toggle){
	if(PlayerData[playerid][ConquerorBar] != INVALID_PLAYER_BAR_ID){
		DestroyPlayerProgressBar(playerid,PlayerData[playerid][ConquerorBar]);
	}
	if(toggle){
		PlayerData[playerid][ConquerorHealth] = CONQUEROR_SHIELD;
		PlayerData[playerid][ConquerorBar] = CreatePlayerProgressBar(playerid,548.5,57.5,57.8,5.0,0x00FF00FF,CONQUEROR_SHIELD);
		SetPlayerProgressBarValue(playerid,PlayerData[playerid][ConquerorBar],PlayerData[playerid][ConquerorHealth]);
		ShowPlayerProgressBar(playerid,PlayerData[playerid][ConquerorBar]);
		SetPlayerAttachedObject(playerid,0,373,1,0.26,-0.01,-0.17,70.0,25.0,33.0,1.05,1.05,1.05,.materialcolor1 = 0xFF00FF00,.materialcolor2 = 0xFF00FF00);
		SetPlayerAttachedObject(playerid,9,1559,1, 2.0,0.0,0.0, 0.0,90.0,0.0, 1.0,1.0,1.0, 0xFF00FF00);
		SetPlayerHealth(playerid,100000.0);
	} else {
		RemovePlayerAttachedObject(playerid,0);
		RemovePlayerAttachedObject(playerid,9);
		PlayerData[playerid][ConquerorHealth] = 0.0;
		SetPlayerHealth(playerid,100.0);
	}
	PlayerData[playerid][ConquerorStatus] = toggle;
	return 1;
}

T3D:function Countdown(val,Float:distance,isFreeze,playerid){
	new buffer[30], F4[Float3D];

	switch(val){
		case 0: format(buffer,sizeof(buffer),"_~n~_~n~~g~~h~~h~GO");
		case 1: format(buffer,sizeof(buffer),"_~n~_~n~~y~%d",val);
		case 2: format(buffer,sizeof(buffer),"_~n~_~n~~r~~h~~h~%d",val);
		case 3: format(buffer,sizeof(buffer),"_~n~_~n~~r~%d",val);
		default: format(buffer,sizeof(buffer),"_~n~_~n~%d",val);
	}
	
	F4[T3D:VW] = GetPlayerVirtualWorld(playerid);
	F4[T3D:INT] = GetPlayerInterior(playerid);

	foreach(new i : Player){
		if(GetPlayerInterior(i) == F4[T3D:INT] && GetPlayerVirtualWorld(i) == F4[T3D:VW]){
			if((distance == 0.0) || (GetDistanceBetweenPlayers(playerid,i) <= distance)){
				GameTextForPlayer(i,buffer,1000,6);
				PlayerPlaySound(i,val>0?1056:1057,0.0,0.0,0.0);
				if(isFreeze){
					if(val > 0) TogglePlayerControllable(i,false);
					if(val <= 0) TogglePlayerControllable(i,true);
				}
			}
		}
	}
	if(val > 0) SetTimerEx("Countdown",900,false,"dfdd",val-1,distance,isFreeze,playerid);
	return 1;
}
//EOF