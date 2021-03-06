h36519
s 00010/00005/00168
d D 3.6 88/06/29 21:38:50 bostic 6 5
c install approved copyright notice
e
s 00013/00007/00160
d D 3.5 88/02/21 13:38:55 bostic 5 4
c written by Edward Wang; attach Berkeley specific copyright
e
s 00001/00001/00166
d D 3.4 86/08/05 01:25:05 edward 4 3
c lint
e
s 00006/00000/00161
d D 3.3 85/04/24 16:24:13 edward 3 2
c copyright messages
e
s 00001/00003/00160
d D 3.2 85/04/03 22:20:53 edward 2 1
c lint, and others
e
s 00163/00000/00000
d D 3.1 85/03/01 17:49:14 edward 1 0
c date and time created 85/03/01 17:49:14 by edward
e
u
U
t
T
I 1
D 5
#ifndef lint
static char sccsid[] = "%W% %G%";
#endif

E 5
I 3
/*
D 5
 * Copyright (c) 1983 Regents of the University of California,
 * All rights reserved.  Redistribution permitted subject to
 * the terms of the Berkeley Software License Agreement.
E 5
I 5
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 6
I 6
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
E 5
 */
I 5

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

E 3
#include "ww.h"

/*
 * Resize a window.  Should be unattached.
 */
wwsize(w, nrow, ncol)
register struct ww *w;
{
	register i, j;
	int nline;
	union ww_char **buf = 0;
	char **win = 0;
	short *nvis = 0;
	char **fmap = 0;
	char m;

D 2
	if (w->ww_forw != 0 || w->ww_back != 0)
		return;				/* sanity */
E 2
	/*
	 * First allocate new buffers.
	 */
	win = wwalloc(w->ww_w.t, w->ww_w.l, nrow, ncol, sizeof (char));
	if (win == 0)
		goto bad;
	if (w->ww_fmap != 0) {
		fmap = wwalloc(w->ww_w.t, w->ww_w.l, nrow, ncol, sizeof (char));
		if (fmap == 0)
			goto bad;
	}
	if (nrow > w->ww_b.nr || ncol > w->ww_b.nc) {
		nline = MAX(w->ww_b.nr, nrow);
		buf = (union ww_char **) wwalloc(w->ww_b.t, w->ww_b.l,
			nline, ncol, sizeof (union ww_char));
		if (buf == 0)
			goto bad;
	}
	nvis = (short *)malloc((unsigned) nrow * sizeof (short));
	if (nvis == 0) {
		wwerrno = WWE_NOMEM;
		goto bad;
	}
	nvis -= w->ww_w.t;
	/*
	 * Copy text buffer.
	 */
	if (buf != 0) {
		int b, r;

		b = w->ww_b.t + nline;
		r = w->ww_b.l + ncol;
		if (ncol < w->ww_b.nc)
			for (i = w->ww_b.t; i < w->ww_b.b; i++)
				for (j = w->ww_b.l; j < r; j++)
					buf[i][j] = w->ww_buf[i][j];
		else
			for (i = w->ww_b.t; i < w->ww_b.b; i++) {
				for (j = w->ww_b.l; j < w->ww_b.r; j++)
					buf[i][j] = w->ww_buf[i][j];
				for (; j < r; j++)
					buf[i][j].c_w = ' ';
			}
		for (; i < b; i++)
			for (j = w->ww_b.l; j < r; j++)
				buf[i][j].c_w = ' ';
	}
	/*
	 * Now free the old stuff.
	 */
	wwfree((char **)w->ww_win, w->ww_w.t);
	w->ww_win = win;
	if (buf != 0) {
		wwfree((char **)w->ww_buf, w->ww_b.t);
		w->ww_buf = buf;
	}
	if (w->ww_fmap != 0) {
		wwfree((char **)w->ww_fmap, w->ww_w.t);
		w->ww_fmap = fmap;
	}
	free((char *)(w->ww_nvis + w->ww_w.t));
	w->ww_nvis = nvis;
	/*
	 * Set new sizes.
	 */
		/* window */
	w->ww_w.b = w->ww_w.t + nrow;
	w->ww_w.r = w->ww_w.l + ncol;
	w->ww_w.nr = nrow;
	w->ww_w.nc = ncol;
		/* text buffer */
	if (buf != 0) {
		w->ww_b.b = w->ww_b.t + nline;
		w->ww_b.r = w->ww_b.l + ncol;
		w->ww_b.nr = nline;
		w->ww_b.nc = ncol;
	}
		/* scroll */
	if ((i = w->ww_b.b - w->ww_w.b) < 0 ||
	    (i = w->ww_cur.r - w->ww_w.b + 1) > 0) {
		w->ww_buf += i;
		w->ww_b.t -= i;
		w->ww_b.b -= i;
		w->ww_cur.r -= i;
	}
		/* interior */
	w->ww_i.b = MIN(w->ww_w.b, wwnrow);
	w->ww_i.r = MIN(w->ww_w.r, wwncol);
	w->ww_i.nr = w->ww_i.b - w->ww_i.t;
	w->ww_i.nc = w->ww_i.r - w->ww_i.l;
	/*
	 * Initialize new buffers.
	 */
		/* window */
	m = 0;
	if (w->ww_oflags & WWO_GLASS)
		m |= WWM_GLS;
	if (w->ww_oflags & WWO_REVERSE)
		m |= WWM_REV;
	for (i = w->ww_w.t; i < w->ww_w.b; i++)
		for (j = w->ww_w.l; j < w->ww_w.r; j++)
			w->ww_win[i][j] = m;
		/* frame map */
	if (fmap != 0)
		for (i = w->ww_w.t; i < w->ww_w.b; i++)
			for (j = w->ww_w.l; j < w->ww_w.r; j++)
				w->ww_fmap[i][j] = 0;
		/* visibility */
	j = m ? 0 : w->ww_w.nc;
	for (i = w->ww_w.t; i < w->ww_w.b; i++)
		w->ww_nvis[i] = j;
	/*
	 * Put cursor back.
	 */
	if (w->ww_hascursor) {
		w->ww_hascursor = 0;
		wwcursor(w, 1);
	}
	/*
	 * Fool with pty.
	 */
	if (w->ww_ispty && w->ww_pty >= 0) {
		struct winsize winsize;

		winsize.ws_row = nrow;
		winsize.ws_col = ncol;
		winsize.ws_xpixel = winsize.ws_ypixel = 0;
D 2
		(void) ioctl(w->ww_pty, TIOCSWINSZ, (char *)&winsize);
E 2
I 2
D 4
		(void) ioctl(w->ww_pty, (int)TIOCSWINSZ, (char *)&winsize);
E 4
I 4
		(void) ioctl(w->ww_pty, TIOCSWINSZ, (char *)&winsize);
E 4
E 2
	}
	return 0;
bad:
	if (win != 0)
		wwfree(win, w->ww_w.t);
	if (fmap != 0)
		wwfree(fmap, w->ww_w.t);
	if (buf != 0)
		wwfree((char **)buf, w->ww_b.t);
	if (nvis != 0)
		free((char *)(nvis + w->ww_w.t));
	return -1;
}
E 1
