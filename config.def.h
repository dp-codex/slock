/* user and group to drop privileges to */
static const char *user  = "nobody";
static const char *group = "deepakpatel";

static const char *colorname[NUMCOLS] = {
	[BACKGROUND] =   "black",     /* after initialization */
	[INIT] =   "#2d2d2d",     /* after initialization */
	[INPUT] =  "#005577",   /* during input */
	[FAILED] = "#CC3333",   /* wrong password */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 0;

/* insert grid pattern with scale 1:1, the size can be changed with logosize */
static const int logosize = 75;
static const int logow = 12;	/* grid width and height for right center alignment*/
static const int logoh = 6;

static XRectangle rectangles[9] = {
	/* x	y	w	h */
  // d
	{ 1,	2,	1,	3 },
	{ 2,	2,	2,	1 },
	{ 1,	4,	8,	1 },
	{ 4, -1,	1,	5 },
  //p
	{ 6,	2,	1,	6 },
	{ 7,	2,	2,	1 },
	{ 9,	2,	1,	3 },
	{ 7,	4,	2,	1 },
};
