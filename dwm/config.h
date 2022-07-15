/* See LICENSE file for copyright and license details. */
#include<X11/XF86keysym.h>
/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 12;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "OCRA:size=10", "AppleColorEmoji:size=10"};
static const char dmenufont[]       = "OCRA:size=10";
static const char col_gray1[]       = "#282c34";
static const char col_gray2[]       = "#353b45";
static const char col_gray3[]       = "#3e4451";
static const char col_white[]       = "#abb2bf";
static const char col_blue[]        = "#61afef";
static const char col_red[]         = "#e06c75";
static const char col_yellow[]      = "#e5c07b";
static const char col_gray4[]       = "#ffb86c";
static const char col_cyan[]        = "#282a36";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_gray1, col_gray3 },
	[SchemeSel]  = { col_white, col_gray2,  col_blue  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Example",        NULL,       NULL,       1 << 8,     0,          -1 },
	{ "st",             NULL,       NULL,       1 << 8,     1,          -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *rofiRuncmd[] = { "rofi", "-show", "run", "-monitor", "-1"};
static const char *rofiWindowcmd[] = { "rofi", "-show", "window"};
static const char *termcmd[]  = { "alacritty", NULL };
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *lockcmd[]  = { "slock", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
        { 0,                      	    XF86XK_AudioLowerVolume,    spawn,    	   SHCMD("Volume-Ctl -d") },
	{ 0,                       	    XF86XK_AudioMute,           spawn, 	           SHCMD("Volume-Ctl -t") },
	{ 0,                       	    XF86XK_AudioRaiseVolume,    spawn, 	           SHCMD("Volume-Ctl -i") },
        { 0,                      	    XF86XK_KbdBrightnessUp,     spawn,    	   SHCMD("BackLight -i") },
        { 0,                      	    XF86XK_KbdBrightnessDown,   spawn,    	   SHCMD("BackLight -d") },
	{ 0,                      	    XF86XK_MonBrightnessDown,   spawn,    	   SHCMD("Brightness -d") },
	{ 0,                      	    XF86XK_MonBrightnessUp,     spawn,    	   SHCMD("Brightness -i") },
	{ MODKEY,                       XK_p,      spawn,          {.v = rofiRuncmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = rofiWindowcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = lockcmd } },
	{ MODKEY,                       XK_s,      spawn,          SHCMD("tdrop -am -x 1% -y 5% -w 98% -h 45% -n 0 st") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	//{ ClkTagBar,            0,              Button1,        view,           {0} },
	//{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	//{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	//{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
