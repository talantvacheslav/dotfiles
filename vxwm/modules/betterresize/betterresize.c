void
resizemouse(const Arg *arg)
{
    Client *c;
    Monitor *m;
    XEvent ev;
#if LOCK_MOVE_RESIZE_REFRESH_RATE
    Time lasttime = 0;
#endif
    if (!(c = selmon->sel) || c->isfullscreen)
        return;

    restack(selmon);

    int orig_x = c->x;
    int orig_y = c->y;
    int orig_w = c->w;
    int orig_h = c->h;

    int rx, ry;
    Window junkwin;
    int junk_signed;
    unsigned int junk;
    if (!XQueryPointer(dpy, c->win, &junkwin, &junkwin, &junk_signed, &junk_signed, &rx, &ry, &junk))
        return;
    int left   = rx < orig_w / 3;
    int right  = rx > orig_w * 2 / 3;
    int top    = ry < orig_h / 3;
    int bottom = ry > orig_h * 2 / 3;
#if BR_CHANGE_CURSOR
    Cursor cur;
    if (top && left)         cur = cursor[CurNW]->cursor;
    else if (top && right)   cur = cursor[CurNE]->cursor;
    else if (bottom && left) cur = cursor[CurSW]->cursor;
    else if (bottom && right) cur = cursor[CurSE]->cursor;
    else if (top)            cur = cursor[CurN]->cursor;
    else if (bottom)         cur = cursor[CurS]->cursor;
    else if (left)           cur = cursor[CurW]->cursor;
    else if (right)          cur = cursor[CurE]->cursor;
    else                     cur = cursor[CurResize]->cursor; // fallback
#else 
    Cursor cur = cursor[CurResize]->cursor; 
#endif
    if (XGrabPointer(dpy, root, False, MOUSEMASK, GrabModeAsync, GrabModeAsync,
                     None, cur, CurrentTime) != GrabSuccess)
        return;
    do {
        XMaskEvent(dpy, MOUSEMASK|ExposureMask|SubstructureRedirectMask, &ev);

        if (ev.type == MotionNotify) {
#if LOCK_MOVE_RESIZE_REFRESH_RATE
            if (ev.xmotion.time - lasttime <= (1000 / refreshrate))
                continue;
            lasttime = ev.xmotion.time;
#endif
            int dx = ev.xmotion.x_root - (orig_x + rx);
            int dy = ev.xmotion.y_root - (orig_y + ry);

            int nx = orig_x;
            int ny = orig_y;
            int nw = orig_w;
            int nh = orig_h;

            if (left)   nw = orig_w - dx;
            else if (right) nw = orig_w + dx;

            if (top)    nh = orig_h - dy;
            else if (bottom) nh = orig_h + dy;

            int min_w = MAX(1, c->minw);
            int min_h = MAX(1, c->minh);
            
            if (nw < min_w) nw = min_w;
            if (nh < min_h) nh = min_h;

            if (left)   nx = orig_x + (orig_w - nw);
            if (top)    ny = orig_y + (orig_h - nh);

            int dx_final = nw - orig_w;
            int dy_final = nh - orig_h;
#if !RESIZINIG_WINDOWS_IN_ALL_LAYOUTS_FLOATS_THEM
            if (!c->isfloating && selmon->lt[selmon->sellt]->arrange &&
              (abs(dx_final) > snap || abs(dy_final) > snap)) {
#else
            if (!c->isfloating && (abs(dx_final) > snap || abs(dy_final) > snap)) {
#endif
              if (nx >= selmon->wx && nx + nw <= selmon->wx + selmon->ww &&
                ny >= selmon->wy && ny + nh <= selmon->wy + selmon->wh) {

                togglefloating(NULL);

                orig_x = c->x;
                orig_y = c->y;
                orig_w = c->w;
                orig_h = c->h;
              }
            }
#if USE_RESIZECLIENT_FUNC           
           resizeclient(c, nx, ny, nw, nh);
#else
           resize(c, nx, ny, nw, nh, 1);
#endif
           drawbar(selmon); //fix for issue 1
        }
    } while (ev.type != ButtonRelease);

    XUngrabPointer(dpy, CurrentTime);
    while (XCheckMaskEvent(dpy, EnterWindowMask, &ev));

    if ((m = recttomon(c->x, c->y, c->w, c->h)) != selmon) {
        sendmon(c, m);
        selmon = m;
        focus(NULL);
    }
#if ENHANCED_TOGGLE_FLOATING && RESTORE_SIZE_AND_POS_ETF
  c->wasmanuallyedited = 1;
  if (c->isfloating) {
    c->sfx = c->x;
    c->sfy = c->y;
    c->sfw = c->w;
    c->sfh = c->h;
  }
#endif
}
