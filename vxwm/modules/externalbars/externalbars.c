static ExternalBarStrut *ebarstruts = NULL;
static Atom eb_atom_strut         = None;
static Atom eb_atom_strut_partial = None;

void
externalbars_init_atoms(void)
{
    if (eb_atom_strut == None)
        eb_atom_strut         = XInternAtom(dpy, "_NET_WM_STRUT", False);
    if (eb_atom_strut_partial == None)
        eb_atom_strut_partial = XInternAtom(dpy, "_NET_WM_STRUT_PARTIAL", False);
}

int
externalbars_read(Window w, ExternalBarStrut *out)
{
    Atom real;
    int fmt;
    unsigned long n, extra;
    unsigned char *p = NULL;

    externalbars_init_atoms();
    memset(out, 0, sizeof *out);
    out->win = w;

    if (XGetWindowProperty(dpy, w, eb_atom_strut_partial, 0L, 12L, False,
            XA_CARDINAL, &real, &fmt, &n, &extra, &p) == Success && p) {
        if (n >= 4) {
            long *s = (long *)p;
            out->left   = (int)s[0];  out->right  = (int)s[1];
            out->top    = (int)s[2];  out->bottom = (int)s[3];
            if (n >= 12) {
                out->left_start_y    = (int)s[4];  out->left_end_y      = (int)s[5];
                out->right_start_y   = (int)s[6];  out->right_end_y     = (int)s[7];
                out->top_start_x     = (int)s[8];  out->top_end_x       = (int)s[9];
                out->bottom_start_x  = (int)s[10]; out->bottom_end_x    = (int)s[11];
            } else {
                out->left_start_y    = 0; out->left_end_y      = sh;
                out->right_start_y   = 0; out->right_end_y     = sh;
                out->top_start_x     = 0; out->top_end_x       = sw;
                out->bottom_start_x  = 0; out->bottom_end_x    = sw;
            }
            XFree(p);
            if (out->left == 0 && out->right == 0 &&
                out->top  == 0 && out->bottom == 0)
                return 0;
            return 1;
        }
        XFree(p);
        p = NULL;
    }

    if (XGetWindowProperty(dpy, w, eb_atom_strut, 0L, 4L, False,
            XA_CARDINAL, &real, &fmt, &n, &extra, &p) == Success && p) {
        if (n >= 4) {
            long *s = (long *)p;
            out->left   = (int)s[0];  out->right  = (int)s[1];
            out->top    = (int)s[2];  out->bottom = (int)s[3];
            out->left_start_y    = 0; out->left_end_y      = sh;
            out->right_start_y   = 0; out->right_end_y     = sh;
            out->top_start_x     = 0; out->top_end_x       = sw;
            out->bottom_start_x  = 0; out->bottom_end_x    = sw;
            XFree(p);
            if (out->left == 0 && out->right == 0 &&
                out->top  == 0 && out->bottom == 0)
                return 0;
            return 1;
        }
        XFree(p);
    }
    return 0;
}

int
externalbars_hasstrut(Window w)
{
    ExternalBarStrut tmp;
    return externalbars_read(w, &tmp);
}

void
externalbars_register(Window w)
{
    ExternalBarStrut tmp, *sw;

    if (!externalbars_read(w, &tmp))
        return;

    for (sw = ebarstruts; sw; sw = sw->next) {
        if (sw->win == w) {
            ExternalBarStrut *nxt = sw->next;
            *sw = tmp;
            sw->next = nxt;
            externalbars_reapply_all();
            return;
        }
    }

    sw = ecalloc(1, sizeof(ExternalBarStrut));
    *sw = tmp;
    sw->next = ebarstruts;
    ebarstruts = sw;
    externalbars_reapply_all();
}

void
externalbars_unregister(Window w)
{
    ExternalBarStrut **prev = &ebarstruts, *sw;

    while ((sw = *prev)) {
        if (sw->win == w) {
            *prev = sw->next;
            free(sw);
            externalbars_reapply_all();
            return;
        }
        prev = &sw->next;
    }
}

void
externalbars_apply(Monitor *m)
{
    ExternalBarStrut *s;
    int top = 0, bottom = 0, left = 0, right = 0;

    for (s = ebarstruts; s; s = s->next) {
        if (s->top > 0) {
            if (s->top_start_x < m->mx + m->mw && s->top_end_x > m->mx) {
                int local = s->top - m->my;
                if (local > 0)
                    top = MAX(top, MIN(local, m->mh));
            }
        }
        if (s->bottom > 0) {
            if (s->bottom_start_x < m->mx + m->mw && s->bottom_end_x > m->mx) {
                int local = s->bottom - (sh - (m->my + m->mh));
                if (local > 0)
                    bottom = MAX(bottom, MIN(local, m->mh));
            }
        }
        if (s->left > 0) {
            if (s->left_start_y < m->my + m->mh && s->left_end_y > m->my) {
                int local = s->left - m->mx;
                if (local > 0)
                    left = MAX(left, MIN(local, m->mw));
            }
        }
        if (s->right > 0) {
            if (s->right_start_y < m->my + m->mh && s->right_end_y > m->my) {
                int local = s->right - (sw - (m->mx + m->mw));
                if (local > 0)
                    right = MAX(right, MIN(local, m->mw));
            }
        }
    }

    m->strut_top    = top;
    m->strut_bottom = bottom;
    m->strut_left   = left;
    m->strut_right  = right;
}

void
externalbars_reapply_all(void)
{
    Monitor *m;

    for (m = mons; m; m = m->next) {
        externalbars_apply(m);
        updatebarpos(m);
    }
    if (selmon)
        arrange(NULL);
}
