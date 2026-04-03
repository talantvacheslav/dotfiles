#pragma once

#if GAPS
#include "gaps/gaps.c"
#endif

#if XRDB
#include "xrdb/xrdb.c"
#endif

#if FULLSCREEN
#include "fullscreen/fullscreen.c"
#endif

#if EWMH_TAGS
#include "ewmh_tags/ewmh_tags.c"
#endif

#if WARP_TO_CLIENT
#include "warptoclient/warptoclient.c"
#endif

#if ENHANCED_TOGGLE_FLOATING
#include "etf/etf.c"
#endif

#if BETTER_RESIZE
#include "betterresize/betterresize.c"
#endif

#if WINDOWMAP
#include "windowmap/windowmap.c"
#endif

#if INFINITE_TAGS
#include "infinitetags/infinitetags.c"
#endif

#if MOVE_RESIZE_WITH_KEYBOARD
#include "moveresizekbd/moveresizekbd.c"
#endif

#if DIRECTIONAL_FOCUS
#include "directionalfocus/directionalfocus.c"
#endif

#if DIRECTIONAL_MOVE
#include "directionalmove/directionalmove.c"
#endif

#if AUTOSTART
#include "autostart/autostart.c"
#endif

#if EXTERNAL_BARS
#include "externalbars/externalbars.c"
#endif
