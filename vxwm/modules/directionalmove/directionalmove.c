void
movedir(const Arg *arg)
{
        if (selmon->lt[selmon->sellt]->arrange != tile) return;
        Client *s = selmon->sel, *f = NULL, *c, *next;
        if (!s)
                return;
        unsigned int score = -1;
        unsigned int client_score;
        int dist;
        int dirweight = 20;
        int isfloating = s->isfloating;
        next = s->next;
        if (!next)
                next = s->mon->clients;
        for (c = next; c != s; c = next) {
                next = c->next;
                if (!next)
                        next = s->mon->clients;
                if (!ISVISIBLE(c) || c->isfloating != isfloating)
                        continue;
                switch (arg->i) {
                case 0: // left
                        dist = s->x - c->x - c->w;
                        client_score =
                                dirweight * MIN(abs(dist), abs(dist + s->mon->ww)) +
                                abs(s->y - c->y);
                        break;
                case 1: // right
                        dist = c->x - s->x - s->w;
                        client_score =
                                dirweight * MIN(abs(dist), abs(dist + s->mon->ww)) +
                                abs(c->y - s->y);
                        break;
                case 2: // up
                        dist = s->y - c->y - c->h;
                        client_score =
                                dirweight * MIN(abs(dist), abs(dist + s->mon->wh)) +
                                abs(s->x - c->x);
                        break;
                default:
                case 3: // down
                        dist = c->y - s->y - s->h;
                        client_score =
                                dirweight * MIN(abs(dist), abs(dist + s->mon->wh)) +
                                abs(c->x - s->x);
                        break;
                }
                if (((arg->i == 0 || arg->i == 2) && client_score <= score) || client_score < score) {
                        score = client_score;
                        f = c;
                }
        }
        if (!f || f == s)
                return;

        Client *ps = NULL, *pf = NULL, *p;
        for (p = s->mon->clients; p; p = p->next) {
                if (p->next == s) ps = p;
                if (p->next == f) pf = p;
        }

        if (s->next == f) {
                if (ps) ps->next = f; else s->mon->clients = f;
                s->next = f->next;
                f->next = s;
        } else if (f->next == s) {
                if (pf) pf->next = s; else s->mon->clients = s;
                f->next = s->next;
                s->next = f;
        } else {
                if (ps) ps->next = f; else s->mon->clients = f;
                if (pf) pf->next = s; else s->mon->clients = s;
                Client *tmp = s->next;
                s->next = f->next;
                f->next = tmp;
        }

        focus(s);
#if WARP_TO_CLIENT && WARP_TO_CENTER_OF_WINDOW_AFFECTED_BY_FOCUSSTACK
        warptoclient(f);
#endif
        arrange(s->mon);
}
