//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	//CPU
	{" ",		"DWM-CPU",		        10,			0},
	//RAM
	{"",		"DWM-Memory",		    10,			0},
	//Brightness
	{"",		"DWM-Brightness",	    0,			1},
	//Battery
	{"",		"DWM-Battery",		    60,			0},
	//WIFI
	{"Wifi ",	    "DWM-Network",		    100,		0},
	//Volume
	{"",		"DWM-Volume",	        0,		    2},
	// udpates
	{"Pkg ",		"checkupdates | wc -l",	86400,		    3},
	//Date
	{"",		"DWM-Date",		        21600,		0},
	//Time
	{"",		"DWM-Time",		        60,			0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
