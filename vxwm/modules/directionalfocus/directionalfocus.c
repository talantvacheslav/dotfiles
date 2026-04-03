void
focusdir(const Arg *arg)
{
	Client *s = selmon->sel, *f = NULL, *c, *next;

	if (!s)
		return;

	unsigned int score = -1;
	unsigned int client_score;
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

#if INFINITE_TAGS
		if (selmon->lt[selmon->sellt]->arrange == NULL) {

			int s_cx = s->x + s->w / 2;
			int s_cy = s->y + s->h / 2;
			int c_cx = c->x + c->w / 2;
			int c_cy = c->y + c->h / 2;

			int dx = c_cx - s_cx;  /* positive = c is to the right */
			int dy = c_cy - s_cy;  /* positive = c is below */

			int axial, lateral;

			switch (arg->i) {
			case 0: /* left */
				if (dx >= 0) continue;
				axial   = -dx;
				lateral = abs(dy);
				break;
			case 1: /* right */
				if (dx <= 0) continue;
				axial   = dx;
				lateral = abs(dy);
				break;
			case 2: /* up */
				if (dy >= 0) continue;
				axial   = -dy;
				lateral = abs(dx);
				break;
			default:
			case 3: /* down */
				if (dy <= 0) continue;
				axial   = dy;
				lateral = abs(dx);
				break;
			}

			client_score = axial + (unsigned int)((long)lateral * lateral) / (axial + 1);
		} else
#endif
		{
			int dist;
			int dirweight = 20;
			switch (arg->i) {
        case 0:
          dist = s->x - c->x - c->w;
          client_score =
            dirweight * abs(dist) +
            abs(s->y - c->y);
          break;
        case 1:
          dist = c->x - s->x - s->w;
          client_score =
            dirweight * abs(dist) +
            abs(c->y - s->y);
          break;
        case 2:
          dist = s->y - c->y - c->h;
          client_score =
            dirweight * abs(dist) +
            abs(s->x - c->x);
          break;
        default:
        case 3:
          dist = c->y - s->y - s->h;
          client_score =
            dirweight * abs(dist) +
            abs(c->x - s->x);
        break;
			}
		}

		if (client_score < score) {
			score = client_score;
			f = c;
		}
	}

	if (f && f != s) {
		focus(f);
#if INFINITE_TAGS
		centerwindow(NULL);
#endif
#if WARP_TO_CLIENT && WARP_TO_CENTER_OF_WINDOW_AFFECTED_BY_FOCUSSTACK
		warptoclient(f);
#endif
		restack(f->mon);
	}
}
