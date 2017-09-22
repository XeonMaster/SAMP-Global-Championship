//ColAndreas.inc Config
#define MAX_CA_OBJECTS				(100) //increase if you need

#define MAX_SERVER_PLAYERS			(20)

#define MAX_IP_CONNECTIONS			(5)

//Logs.inc Config
#define EMPTY_LOG_BUFFER			"Championship Log\n"

//3DTryg.inc Config
#define ENABLE_3D_TRYG_ANIMS











#if defined MAX_PLAYERS
	#undef MAX_PLAYERS
#endif
#define MAX_PLAYERS					MAX_SERVER_PLAYERS

//EOF