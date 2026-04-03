void
window_set_state(Display *dpy, Window win, long state)
{
	long data[] = { state, None };

	XChangeProperty(dpy, win, wmatom[WMState], wmatom[WMState], 32,
		PropModeReplace, (unsigned char*)data, 2);
}

void
window_map(Display *dpy, Client *c, int deiconify)
{
	Window win = c->win;

	if (deiconify)
		window_set_state(dpy, win, NormalState);

	XMoveResizeWindow(dpy, c->win, c->x, c->y, c->w, c->h);
	XSetInputFocus(dpy, win, RevertToPointerRoot, CurrentTime);
	XMapWindow(dpy, win);
  focus(NULL);
}

void
window_unmap(Display *dpy, Window win, Window root, int iconify)
{
	static XWindowAttributes ca, ra;

	XGetWindowAttributes(dpy, root, &ra);
	XGetWindowAttributes(dpy, win, &ca);

	/* Prevent UnmapNotify events */
	XSelectInput(dpy, root, ra.your_event_mask & ~SubstructureNotifyMask);
	XSelectInput(dpy, win, ca.your_event_mask & ~StructureNotifyMask);

	XUnmapWindow(dpy, win);
  focus(NULL);
	if (iconify)
		window_set_state(dpy, win, IconicState);

	XSelectInput(dpy, root, ra.your_event_mask);
	XSelectInput(dpy, win, ca.your_event_mask);
}
