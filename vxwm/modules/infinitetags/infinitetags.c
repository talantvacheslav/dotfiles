int
getcurrenttag(Monitor *m) {
    unsigned int i;
    for (i = 0; i < LENGTH(tags) && !(m->tagset[m->seltags] & (1 << i)); i++);
    return i < LENGTH(tags) ? i : 0;
}

void
homecanvas(const Arg *arg) {
    Client *c;
    int tagidx = getcurrenttag(selmon);
    int cx = selmon->canvas[tagidx].cx;
    int cy = selmon->canvas[tagidx].cy;
    
    for (c = selmon->clients; c; c = c->next) {
        if (c->tags & (1 << tagidx)) {
            c->x -= cx;
            c->y -= cy;
            XMoveWindow(dpy, c->win, c->x, c->y);
        }
    }
    
    selmon->canvas[tagidx].cx = 0;
    selmon->canvas[tagidx].cy = 0;
    drawbar(selmon); 
    XFlush(dpy);
}

void
movecanvas(const Arg *arg)
{
	if (selmon->lt[selmon->sellt]->arrange != NULL)
		return;
  if (selmon->sel && selmon->sel->isfullscreen)
    return;

	int tagidx = getcurrenttag(selmon);
	int dx = 0, dy = 0;
	
#ifndef MOVE_CANVAS_STEP
#define MOVE_CANVAS_STEP 120
#endif

	switch(arg->i) {
    case 0: dx = -MOVE_CANVAS_STEP; break;
		case 1: dx =  MOVE_CANVAS_STEP; break;
    case 2: dy = -MOVE_CANVAS_STEP; break;
		case 3: dy =  MOVE_CANVAS_STEP; break;
	}

	selmon->canvas[tagidx].cx -= dx;
	selmon->canvas[tagidx].cy -= dy;

	Client *c;
	for (c = selmon->clients; c; c = c->next) {
		if (ISVISIBLE(c)) {
			c->x -= dx;
			c->y -= dy;
			XMoveWindow(dpy, c->win, c->x, c->y);
		}
	}

	drawbar(selmon);
}

void
manuallymovecanvas(const Arg *arg) {
    if (selmon->lt[selmon->sellt]->arrange != NULL)
      return;
    if (selmon->sel && selmon->sel->isfullscreen)
      return;
    int start_x, start_y;
    Window dummy;
    int di;
    unsigned int dui;
    int tagidx = getcurrenttag(selmon);
#if LOCK_MOVE_RESIZE_REFRESH_RATE
    Time lasttime = 0;
#endif

    if (!XQueryPointer(dpy, root, &dummy, &dummy, &start_x, &start_y, &di, &di, &dui))
        return;
    
    if (XGrabPointer(dpy, root, False, MOUSEMASK, GrabModeAsync, GrabModeAsync,
        None, cursor[CurMove]->cursor, CurrentTime) != GrabSuccess)
        return;
    
    XEvent ev;
    do {
        XMaskEvent(dpy, MOUSEMASK|ExposureMask|SubstructureRedirectMask, &ev);
        
        switch (ev.type) {
        case MotionNotify:
        {
#if LOCK_MOVE_RESIZE_REFRESH_RATE
            if ((ev.xmotion.time - lasttime) <= (1000 / refreshrate))
                continue;
            lasttime = ev.xmotion.time;
#endif
            int nx = ev.xmotion.x - start_x;
            int ny = ev.xmotion.y - start_y;
            
            for (Client *c = selmon->clients; c; c = c->next) {
                if (c->tags & (1 << tagidx)) {
                    c->x += nx;
                    c->y += ny;
                    XMoveWindow(dpy, c->win, c->x, c->y);
                }
            }
            
            selmon->canvas[tagidx].cx += nx;
            selmon->canvas[tagidx].cy += ny;
            drawbar(selmon); 
            start_x = ev.xmotion.x;
            start_y = ev.xmotion.y;
        }   break;
        }
    } while (ev.type != ButtonRelease);
    
    XUngrabPointer(dpy, CurrentTime);
}

void
save_canvas_positions(Monitor *m) {
    Client *c;
    int tagidx = getcurrenttag(m);
    
    m->canvas[tagidx].saved_cx = m->canvas[tagidx].cx;
    m->canvas[tagidx].saved_cy = m->canvas[tagidx].cy;

    for (c = m->clients; c; c = c->next) {
        if (ISVISIBLE(c)) {
            c->saved_cx = c->x + m->canvas[tagidx].cx;
            c->saved_cy = c->y + m->canvas[tagidx].cy;
            c->saved_cw = c->w;
            c->saved_ch = c->h;
            c->was_on_canvas = 1;
        }
    }
}

void
restore_canvas_positions(Monitor *m) {
    Client *c;
    int tagidx = getcurrenttag(m);

    m->canvas[tagidx].cx = m->canvas[tagidx].saved_cx;
    m->canvas[tagidx].cy = m->canvas[tagidx].saved_cy;

    for (c = m->clients; c; c = c->next) {
        if (ISVISIBLE(c) && c->was_on_canvas) {
            if (c->isfullscreen)
              continue;
            c->isfloating = 1;
            
            int target_x = c->saved_cx - m->canvas[tagidx].cx;
            int target_y = c->saved_cy - m->canvas[tagidx].cy;

            c->x = target_x;
            c->y = target_y;
            c->w = c->saved_cw;
            c->h = c->saved_ch;

            XMoveResizeWindow(dpy, c->win, target_x, target_y, c->w, c->h);

            configure(c);
        }
    }
    XSync(dpy, False);
}

void
centerwindow(const Arg *arg)
{
  Client *c = (arg && arg->v) ? (Client *)arg->v : selmon->sel;

  if (!c || !c->mon || c->mon->lt[c->mon->sellt]->arrange != NULL)
    return;

  Monitor *m = c->mon;
  int tagidx = getcurrenttag(m);

  int dx = (m->wx + m->ww - WIDTH(c)) / 2 - c->x;
  int dy = m->wy + (m->wh / 2) - (c->y + HEIGHT(c) / 2);

  if (dx == 0 && dy == 0)
    return;

  Client *tmp;
  for (tmp = m->clients; tmp; tmp = tmp->next) {
    if (ISVISIBLE(tmp)) {
      tmp->x += dx;
      tmp->y += dy;
      XMoveWindow(dpy, tmp->win, tmp->x, tmp->y);
    }
  }

  m->canvas[tagidx].cx += dx;
  m->canvas[tagidx].cy += dy;

  drawbar(m);
}
