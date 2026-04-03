#if !RESTORE_SIZE_AND_POS_ETF
void
enhancedtogglefloating(const Arg *arg)
{
    if (!selmon->sel || selmon->sel->isfullscreen)
        return;
    Client *c = selmon->sel;
    const Layout *prevlayout = selmon->lt[selmon->sellt];
    c->isfloating = !c->isfloating;
    if (c->isfloating) {
        int w = c->sfw > 0 ? c->sfw : c->w;
        int h = c->sfh > 0 ? c->sfh : c->h;
        resize(c,
            c->mon->wx + (c->mon->ww - w) / 2,
            c->mon->wy + (c->mon->wh - h) / 2,
            w, h, 0);
    } else {
        int tiled_sellt = -1;
        for (int i = 0; i < LENGTH(layouts); i++) {
            if (selmon->lt[i]->arrange != NULL) {
                tiled_sellt = i;
                break;
            }
        }
        if (tiled_sellt != -1) {
            selmon->sellt = tiled_sellt;
            arrange(selmon);
        }
        for (int i = 0; i < LENGTH(layouts); i++) {
            if (selmon->lt[i] == prevlayout) {
                selmon->sellt = i;
                break;
            }
        }
    }
    arrange(selmon);
#if WARP_TO_CLIENT && WARP_TO_CENTER_OF_WINDOW_AFFECTED_BY_ENHANCED_TOGGLE_FLOATING
    warptoclient(selmon->sel);
#endif
}
#else
void
enhancedtogglefloating(const Arg *arg)
{
    if (!selmon->sel || selmon->sel->isfullscreen)
        return;
    Client *c = selmon->sel;
    const Layout *prevlayout = selmon->lt[selmon->sellt];
    c->isfloating = !c->isfloating;
    if (c->isfloating) {
        int w = c->sfw > 0 ? c->sfw : c->w;
        int h = c->sfh > 0 ? c->sfh : c->h;
        if (!c->wasmanuallyedited) {
            resize(c,
                c->mon->wx + (c->mon->ww - w) / 2,
                c->mon->wy + (c->mon->wh - h) / 2,
                w, h, 0);
        } else {
            resize(c, c->sfx, c->sfy, w, h, 0);
        }
        c->sfx = c->x; c->sfy = c->y;
        c->sfw = c->w; c->sfh = c->h;
    } else {
        c->sfx = c->x;
        c->sfy = c->y;
        c->sfw = c->w;
        c->sfh = c->h;
        int tiled_sellt = -1;
        for (int i = 0; i < LENGTH(layouts); i++) {
            if (selmon->lt[i]->arrange != NULL) {
                tiled_sellt = i;
                break;
            }
        }
        if (tiled_sellt != -1) {
            selmon->sellt = tiled_sellt;
            arrange(selmon);
        }
        for (int i = 0; i < LENGTH(layouts); i++) {
            if (selmon->lt[i] == prevlayout) {
                selmon->sellt = i;
                break;
            }
        }
    }
    arrange(selmon);
#if WARP_TO_CLIENT && WARP_TO_CENTER_OF_WINDOW_AFFECTED_BY_ENHANCED_TOGGLE_FLOATING
    warptoclient(selmon->sel);
#endif
}
#endif
