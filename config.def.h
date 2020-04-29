/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=20" };
static const char dracula_fg[] = "#f8f8f2";
static const char dracula_bg[] = "#282a36";
static const char dracula_purple[] = "#bd93f9";
static const char dracula_line[] = "#44475a";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { dracula_fg , dracula_bg, dracula_line },
	[SchemeSel]  = { dracula_fg, dracula_bg,  dracula_purple  },
	[SchemeStatus] = { dracula_fg, dracula_bg, dracula_purple },
	[SchemeTagsSel] = { dracula_bg, dracula_purple, dracula_purple },
	[SchemeTagsNorm] = { dracula_fg , dracula_bg, dracula_line },
	[SchemeInfoNorm] = { dracula_fg , dracula_bg, dracula_line },
	[SchemeInfoSel]  = { dracula_fg, dracula_bg,  dracula_purple  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "st-256color", NULL, "/home/thomas/scripts/ncspot", 1 << 7, 0, -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

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
#define TERM "st"
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *checkmail[] = { "/home/thomas/scripts/checkmail" };

// Applications
#define OPENTERMAPP(app) { TERM, "-e", app, NULL }
static const char *browser[] = { "firefox", NULL };
static const char *todocmd[] = OPENTERMAPP("calcurse");
static const char *mailcmd[] = OPENTERMAPP("neomutt");
static const char *musiccmd[] = OPENTERMAPP("/home/thomas/scripts/ncspot");
static const char *termcmd[]  = OPENTERMAPP("/bin/fish");
static const char *filemanagercmd[] = OPENTERMAPP("/bin/nnn");

// Sounds and music
/* #define MASTERVOL(change) { "amixer", "set", "Master", change, NULL } */
/* static const char *volup[] = MASTERVOL("1db+"); */
/* static const char *voldown[] = MASTERVOL("1db-"); */
/* static const char *voltoggle[] = MASTERVOL("toggle"); */

#define PLAYER(action) { "playerctl", action, NULL }
static const char *playerpause[] = PLAYER("play-pause");
static const char *playernext[] = PLAYER("next");
static const char *playerprevious[] = PLAYER("previous");

#include "movestack.c"
static Key keys[] = {
	/* modifier						key			function		argument */
	{ MODKEY,						XK_p,		spawn,			{.v = dmenucmd } },
	{ 0, 							XK_Menu,	spawn,			{.v = dmenucmd } },
	{ MODKEY,						XK_t,		spawn,			{.v = todocmd } },
	{ 0, 							XF86XK_Mail,	spawn,		{.v = mailcmd } },
	{ MODKEY, 						XF86XK_Mail,	spawn,		{.v = checkmail } },
	{ 0, 							XF86XK_HomePage,	spawn,	{.v = browser } },
	{ 0, 							XF86XK_AudioRaiseVolume,	spawn,	SHCMD("amixer set Master 1db+") },
	{ 0, 							XF86XK_AudioLowerVolume,	spawn,	SHCMD("amixer set Master 1db+") },
	{ 0, 							XF86XK_AudioMute,	spawn,	SHCMD("amixer set Master toggle") },
	{ 0, 							XF86XK_AudioPlay,	spawn,	{.v = playerpause } },
	{ 0, 							XF86XK_AudioNext,	spawn,	{.v = playernext } },
	{ 0, 							XF86XK_AudioPrev,	spawn,	{.v = playerprevious } },
	{ MODKEY,						XK_Return, spawn,			{.v = termcmd } },
	{ MODKEY,						XK_m, spawn,				{.v = musiccmd } },
	{ MODKEY,						XK_f, spawn,				{.v = filemanagercmd } },
	{ MODKEY,						XK_b,      togglebar,      {0} },
	{ MODKEY,						XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,						XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,						XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,						XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,						XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,						XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,				XK_Return, zoom,           {0} },
	{ MODKEY,						XK_Tab,    view,           {0} },
	{ MODKEY,						XK_x,      killclient,     {0} },
	{ MODKEY|ShiftMask,				XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,				XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,				XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,				XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,				XK_space,  togglefloating, {0} },
	{ MODKEY,						XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,				XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,						XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,						XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,				XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,				XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
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
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

