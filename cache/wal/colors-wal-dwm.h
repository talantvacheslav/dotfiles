static const char norm_fg[] = "#d6d7da";
static const char norm_bg[] = "#0d0d0d";
static const char norm_border[] = "#959698";

static const char sel_fg[] = "#d6d7da";
static const char sel_bg[] = "#8B8E95";
static const char sel_border[] = "#d6d7da";

static const char urg_fg[] = "#d6d7da";
static const char urg_bg[] = "#7D8188";
static const char urg_border[] = "#7D8188";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
    [SchemeUrg] =  { urg_fg,      urg_bg,    urg_border },
};
