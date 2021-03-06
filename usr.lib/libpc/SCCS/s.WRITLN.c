h08741
s 00004/00004/00021
d D 1.2 81/06/10 00:45:14 mckusic 2 1
c move the text of error messages from ERROR to the functions
c which generate them.
e
s 00025/00000/00000
d D 1.1 80/10/30 00:36:30 mckusick 1 0
c date and time created 80/10/30 00:36:30 by mckusick
e
u
U
t
T
I 1
/* Copyright (c) 1979 Regents of the University of California */

static char sccsid[] = "%Z%%M% %I% %G%";

#include "h00vars.h"
D 2
#include "h01errs.h"
E 2

WRITLN(curfile)

	register struct iorec	*curfile;
{
	if (curfile->funit & FREAD) {
D 2
		ERROR(EWRITEIT, curfile->pfname);
E 2
I 2
		ERROR("%s: Attempt to write, but open for reading\n",
			curfile->pfname);
E 2
		return;
	}
	if (++curfile->lcount >= curfile->llimit) {
D 2
		ERROR(ELLIMIT, curfile->pfname);
E 2
I 2
		ERROR("%s: Line limit exceeded\n", curfile->pfname);
E 2
		return;
	}
	fputc('\n', curfile->fbuf);
	if (ferror(curfile->fbuf)) {
D 2
		ERROR(EWRITE, curfile->pfname);
E 2
I 2
		PERROR("Could not write to ", curfile->pfname);
E 2
		return;
	}
}
E 1
