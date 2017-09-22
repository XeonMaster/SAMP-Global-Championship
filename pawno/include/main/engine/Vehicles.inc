//Functions/Callbacks for vehicle

/*
T3D:function SAOI_OnVehicleCreated(vehicleid){
	
	return 1;
}

T3D:function SAOI_OnVehicleDestroyed(vehicleid){
	
	return 1;
}
*/

public OnVehicleSpawn(vehicleid){

	return 1;
}

public OnVehicleDeath(vehicleid, killerid){

	return 1;
}

public OnVehicleMod(playerid,vehicleid,componentid){

	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger){

	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid){

	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid){

	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2){

	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid){

	return 1;
}

public OnVehicleArmed(playerid,vehicleid){

	switch(GetVehicleModel(vehicleid)){
		case 564: { //rc tiger
			ToggleVehicleRhinoMissile(vehicleid,1);
		}
		case 553: { //nevada
			ToggleVehicleBomberMissile(vehicleid,1);
			SetVehicleBomberMissileSpeed(vehicleid,40.0);
		}
		case 592: { //andromada
			ToggleVehicleBomberMissile(vehicleid,1);
			SetVehicleBomberMissileSpeed(vehicleid,60.0);
			SetVehicleBomberMissileReload(vehicleid,500);
		}
		case 520: { //hydra
			ToggleVehicleBomberMissile(vehicleid,1);
			SetVehicleBomberMissileSpeed(vehicleid,80.0);
			SetVehicleBomberMissileReload(vehicleid,500);
			
			ToggleVehicleHeavyMissile(vehicleid,1);
			SetVehicleHeavyMissileSpeed(vehicleid,90.0);
			SetVehicleHeavyMissileKey(vehicleid,KEY_CROUCH);
			
			ToggleVehicleCongreve(vehicleid,1);
			SetVehicleCongreveSpeed(vehicleid,100.0);
			SetVehicleCongreveKey(vehicleid,KEY_NO);
			SetVehicleCongreveSpread(vehicleid,15.0);
			SetVehicleCongreveSalvo(vehicleid,8);
		}
		case 425: { //hunter
			ToggleVehicleMiniMissile(vehicleid,1);
			SetVehicleMiniMissileSpeed(vehicleid,130.0);
			SetVehicleMiniMissileKey(vehicleid,KEY_CROUCH);
			SetVehicleMiniMissileReload(vehicleid,1000);
			
			ToggleVehicleBomberMissile(vehicleid,1);
			SetVehicleBomberMissileSpeed(vehicleid,80.0);
			SetVehicleBomberMissileReload(vehicleid,500);
		}
		case 476: { //rustler
			ToggleVehicleMiniMissile(vehicleid,1);
			SetVehicleMiniMissileSpeed(vehicleid,80.0);
			
			ToggleVehicleBomberMissile(vehicleid,1);
			SetVehicleBomberMissileSpeed(vehicleid,80.0);
			SetVehicleBomberMissileReload(vehicleid,500);
		}
		case 548, 497, 469, 447: { //Cargobob, Police Maverik, Sparrow, Sea Sparrow
			ToggleVehicleMiniMissile(vehicleid,1);
			SetVehicleMiniMissileSpeed(vehicleid,40.0);
			
			ToggleVehicleBomberMissile(vehicleid,1);
			SetVehicleBomberMissileSpeed(vehicleid,40.0);
		}
		case 512: { //Cropduster
			ToggleVehicleBomberMissile(vehicleid,1);
			SetVehicleBomberMissileSpeed(vehicleid,40.0);
		}
		case 513: { //stuntplane
			ToggleVehicleBomberMissile(vehicleid,1);
			SetVehicleBomberMissileSpeed(vehicleid,40.0);
		}
		case 519: { //shamal
			ToggleVehicleMiniMissile(vehicleid,1);
			SetVehicleMiniMissileSpeed(vehicleid,80.0);
		}
		case 432, 430: { //rhino, predator
			
			ToggleVehicleMortarMissile(vehicleid,1);
			SetVehicleMortarMissileSpeed(vehicleid,50.0);
			SetVehicleMortarMissileHeight(vehicleid,VEHICLE_MISSILE_HEIGHT_MORTAR);
			SetVehicleMortarMissileDistance(vehicleid,VEHICLE_MISSILE_DISTANCE_MORTAR);
			
			/*
			ToggleVehicleMegaMissile(vehicleid,1);
			SetVehicleMegaMissileSpeed(vehicleid,50.0);
			SetVehicleMegaMissileHeight(vehicleid,VEHICLE_MISSILE_HEIGHT_MEGA);
			SetVehicleMegaMissileDistance(vehicleid,VEHICLE_MISSILE_DISTANCE_MEGA);
			*/
		}
	}
	return 1;
}