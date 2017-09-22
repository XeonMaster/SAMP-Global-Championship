
//Teleport to area
stock SelectPlayerArea(playerid,areaid = AREA_NONE){
	//Init Player
	ResetPlayerWeapons(playerid);
	SetPlayerHealth(playerid,100000.0);
	SetPlayerArmour(playerid,0.0);
	TogglePlayerConqueror(playerid,false);
	
	PlayerData[playerid][area_active] = areaid;
	
	switch(areaid){
		
		//todo: Abyss Morgan AREA_NONE..AREA_FOOTBALL
		case AREA_NONE: {
			//SetPlayerAbsolutePosition(playerid,Float:x,Float:y,Float:z,Float:angle,worldid,interiorid,1000);
		}
		
		case AREA_MAGICZONE: {
			//SetPlayerAbsolutePosition(playerid,Float:x,Float:y,Float:z,Float:angle,worldid,interiorid,1000);
		}
		
		case AREA_WARZONE: {
			//SetPlayerAbsolutePosition(playerid,Float:x,Float:y,Float:z,Float:angle,worldid,interiorid,1000);
		}
		
		case AREA_SIEGE: {
			//SetPlayerAbsolutePosition(playerid,Float:x,Float:y,Float:z,Float:angle,worldid,interiorid,1000);
		}
		
		case AREA_FOOTBALL: {
			//SetPlayerAbsolutePosition(playerid,Float:x,Float:y,Float:z,Float:angle,worldid,interiorid,1000);
		}
		
	}
	GameTextForPlayer(playerid,AreaNames[areaid],3500,6);
}

T3D:function OnPlayerEventStart(playerid,areaid){
	
	PlayerData[playerid][event_active] = areaid;
	
	switch(areaid){
		
		//todo: Abyss Morgan AREA_MAGICZONE..AREA_FOOTBALL
		
		case AREA_MAGICZONE: {
			//SetPlayerAbsolutePosition(playerid,Float:x,Float:y,Float:z,Float:angle,worldid,interiorid,1000);
			ToggleMagicShootForPlayer(playerid,true);
			SetPlayerHealth(playerid,100.0);
			SetPlayerArmour(playerid,100.0);
			
			switch(random(12)){
				case 0: SetMagicProjectile(playerid,18693,	90.0,0.0,0.0,	0.0,0.0,0.0);
				case 1: SetMagicProjectile(playerid,18691,	90.0,0.0,0.0,	0.0,0.0,0.0);
				case 2: SetMagicProjectile(playerid,18720,	90.0,0.0,0.0,	0.0,0.0,0.0);
				case 3: SetMagicProjectile(playerid,18728,	90.0,0.0,0.0,	0.0,0.0,0.0);
				case 4: SetMagicProjectile(playerid,18729,	0.0,90.0,180.0,	1.5,-1.5,0.0);
				case 5: SetMagicProjectile(playerid,18687,	0.0,90.0,180.0,	1.5,-1.5,0.0);
				case 6: SetMagicProjectile(playerid,18707,	90.0,0.0,0.0,	0.0,0.0,0.0);
				case 7: SetMagicProjectile(playerid,18699,	90.0,0.0,0.0,	0.0,0.0,0.0);
				case 8: SetMagicProjectile(playerid,18711,	90.0,0.0,0.0,	0.0,0.0,0.0);
				case 9: SetMagicProjectile(playerid,18709,	90.0,0.0,0.0,	0.0,0.0,0.0);
				case 10: SetMagicProjectile(playerid,18697,	90.0,0.0,0.0,	0.0,0.0,0.0);
				case 11: SetMagicProjectile(playerid,18674,	0.0,0.0,0.0,	0.0,0.0,0.0);
			}
		}
		
		case AREA_WARZONE: {
			//SetPlayerAbsolutePosition(playerid,Float:x,Float:y,Float:z,Float:angle,worldid,interiorid,1000);
		}
		
		case AREA_SIEGE: {
			//SetPlayerAbsolutePosition(playerid,Float:x,Float:y,Float:z,Float:angle,worldid,interiorid,1000);
		}
		
		case AREA_FOOTBALL: {
			//SetPlayerAbsolutePosition(playerid,Float:x,Float:y,Float:z,Float:angle,worldid,interiorid,1000);
		}
		
	}
	
	return 1;
}

T3D:function OnPlayerEventClose(playerid,areaid){
	
	PlayerData[playerid][event_active] = AREA_NONE;
	
	switch(areaid){
		
		//todo: Abyss Morgan AREA_MAGICZONE..AREA_FOOTBALL
		
		case AREA_MAGICZONE: {
			ToggleMagicShootForPlayer(playerid,false);
		}
		
		case AREA_WARZONE: {
			
		}
		
		case AREA_SIEGE: {
			
		}
		
		case AREA_FOOTBALL: {
			
		}
		
	}
	
	SpawnPlayer(playerid);
	
	return 1;
}