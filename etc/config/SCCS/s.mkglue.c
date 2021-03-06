h49540
s 00016/00028/00277
d D 5.7 04/03/02 17:49:29 msokolov 7 6
c redesign handling of VAXBI and peripheral nexus devices
e
s 00010/00005/00295
d D 5.6 88/06/18 13:43:05 bostic 6 5
c install approved copyright notice
e
s 00009/00003/00291
d D 5.5 88/04/29 13:43:40 bostic 5 4
c add Berkeley specific header; original conception by Michael Toy
e
s 00001/00001/00293
d D 5.4 87/04/07 11:22:58 karels 4 3
c wrong way
e
s 00001/00001/00293
d D 5.3 87/04/06 10:02:09 bostic 3 2
c fprintf format/argument mismatch
e
s 00089/00000/00205
d D 5.2 86/10/13 15:35:34 sam 2 1
c replace ancient sun support with tahoe support
e
s 00205/00000/00000
d D 5.1 86/02/18 17:54:30 sam 1 0
c date and time created 86/02/18 17:54:30 by sam
e
u
U
t
T
I 1
/*
 * Copyright (c) 1980 Regents of the University of California.
D 5
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
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

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5

/*
 * Make the bus adaptor interrupt glue files.
 */
#include <stdio.h>
#include "config.h"
#include "y.tab.h"
#include <ctype.h>

/*
 * Create the UNIBUS interrupt vector glue file.
I 7
 * (Though it isn't just for UNIBUS any more, but for all devices with vectors.)
E 7
 */
ubglue()
{
	register FILE *fp, *gp;
	register struct device *dp, *mp;
I 7
	register struct idlst *id, *id2;
E 7

	fp = fopen(path("ubglue.s"), "w");
	if (fp == 0) {
		perror(path("ubglue.s"));
		exit(1);
	}
	gp = fopen(path("ubvec.s"), "w");
	if (gp == 0) {
		perror(path("ubvec.s"));
		exit(1);
	}
	for (dp = dtab; dp != 0; dp = dp->d_next) {
D 7
		mp = dp->d_conn;
		if (mp != 0 && mp != (struct device *)-1 &&
		    !eq(mp->d_name, "mba")) {
			struct idlst *id, *id2;

			for (id = dp->d_vec; id; id = id->id_next) {
				for (id2 = dp->d_vec; id2; id2 = id2->id_next) {
					if (id2 == id) {
						dump_ubavec(fp, id->id,
						    dp->d_unit);
						break;
					}
					if (!strcmp(id->id, id2->id))
						break;
E 7
I 7
		for (id = dp->d_vec; id; id = id->id_next) {
			for (id2 = dp->d_vec; id2; id2 = id2->id_next) {
				if (id2 == id) {
					dump_ubavec(fp, id->id, dp->d_unit);
					break;
E 7
				}
I 7
				if (!strcmp(id->id, id2->id))
					break;
E 7
			}
		}
	}
	dump_std(fp, gp);
	for (dp = dtab; dp != 0; dp = dp->d_next) {
D 7
		mp = dp->d_conn;
		if (mp != 0 && mp != (struct device *)-1 &&
		    !eq(mp->d_name, "mba")) {
			struct idlst *id, *id2;

			for (id = dp->d_vec; id; id = id->id_next) {
				for (id2 = dp->d_vec; id2; id2 = id2->id_next) {
					if (id2 == id) {
						dump_intname(fp, id->id,
							dp->d_unit);
						break;
					}
					if (!strcmp(id->id, id2->id))
						break;
E 7
I 7
		for (id = dp->d_vec; id; id = id->id_next) {
			for (id2 = dp->d_vec; id2; id2 = id2->id_next) {
				if (id2 == id) {
					dump_intname(fp, id->id, dp->d_unit);
					break;
E 7
				}
I 7
				if (!strcmp(id->id, id2->id))
					break;
E 7
			}
		}
	}
	dump_ctrs(fp);
	(void) fclose(fp);
	(void) fclose(gp);
}

static int cntcnt = 0;		/* number of interrupt counters allocated */

/*
 * Print a UNIBUS interrupt vector.
 */
dump_ubavec(fp, vector, number)
	register FILE *fp;
	char *vector;
	int number;
{
	char nbuf[80];
	register char *v = nbuf;

	(void) sprintf(v, "%s%d", vector, number);
	fprintf(fp, "\t.globl\t_X%s\n\t.align\t2\n_X%s:\n\tpushr\t$0x3f\n",
	    v, v);
	fprintf(fp, "\tincl\t_fltintrcnt+(4*%d)\n", cntcnt++);
	if (strncmp(vector, "dzx", 3) == 0)
		fprintf(fp, "\tmovl\t$%d,r0\n\tjmp\tdzdma\n\n", number);
	else {
		if (strncmp(vector, "uur", 3) == 0) {
			fprintf(fp, "#ifdef UUDMA\n");
			fprintf(fp, "\tmovl\t$%d,r0\n\tjsb\tuudma\n", number);
			fprintf(fp, "#endif\n");
		}
		fprintf(fp, "\tpushl\t$%d\n", number);
		fprintf(fp, "\tcalls\t$1,_%s\n\tpopr\t$0x3f\n", vector);
		fprintf(fp, "\tincl\t_cnt+V_INTR\n\trei\n\n");
	}
}

I 2
/*
 * Create the VERSAbus interrupt vector glue file.
 */
vbglue()
{
	register FILE *fp, *gp;
	register struct device *dp, *mp;

	fp = fopen(path("vbglue.s"), "w");
	if (fp == 0) {
		perror(path("vbglue.s"));
		exit(1);
	}
	gp = fopen(path("vbvec.s"), "w");
	if (gp == 0) {
		perror(path("vbvec.s"));
		exit(1);
	}
	for (dp = dtab; dp != 0; dp = dp->d_next) {
		struct idlst *id, *id2;

		mp = dp->d_conn;
		if (mp == 0 || mp == (struct device *)-1 ||
		    eq(mp->d_name, "mba"))
			continue;
		for (id = dp->d_vec; id; id = id->id_next)
			for (id2 = dp->d_vec; id2; id2 = id2->id_next) {
				if (id == id2) {
					dump_vbavec(fp, id->id, dp->d_unit);
					break;
				}
				if (eq(id->id, id2->id))
					break;
			}
	}
	dump_std(fp, gp);
	for (dp = dtab; dp != 0; dp = dp->d_next) {
		mp = dp->d_conn;
		if (mp != 0 && mp != (struct device *)-1 &&
		    !eq(mp->d_name, "mba")) {
			struct idlst *id, *id2;

			for (id = dp->d_vec; id; id = id->id_next) {
				for (id2 = dp->d_vec; id2; id2 = id2->id_next) {
					if (id2 == id) {
						dump_intname(fp, id->id,
							dp->d_unit);
						break;
					}
					if (eq(id->id, id2->id))
						break;
				}
			}
		}
	}
	dump_ctrs(fp);
	(void) fclose(fp);
	(void) fclose(gp);
}

/*
 * Print a VERSAbus interrupt vector
 */
dump_vbavec(fp, vector, number)
	register FILE *fp;
	char *vector;
	int number;
{
	char nbuf[80];
	register char *v = nbuf;

	(void) sprintf(v, "%s%d", vector, number);
	fprintf(fp, "SCBVEC(%s):\n", v);
	fprintf(fp, "\tCHECK_SFE(4)\n");
	fprintf(fp, "\tSAVE_FPSTAT(4)\n");
	fprintf(fp, "\tPUSHR\n");
	fprintf(fp, "\tincl\t_fltintrcnt+(4*%d)\n", cntcnt++);
	fprintf(fp, "\tpushl\t$%d\n", number);
	fprintf(fp, "\tcallf\t$8,_%s\n", vector);
	fprintf(fp, "\tincl\t_cnt+V_INTR\n");
	fprintf(fp, "\tPOPR\n");
	fprintf(fp, "\tREST_FPSTAT\n");
	fprintf(fp, "\trei\n\n");
}

E 2
static	char *vaxinames[] = {
	"clock", "cnr", "cnx", "tur", "tux",
	"mba0", "mba1", "mba2", "mba3",
	"uba0", "uba1", "uba2", "uba3"
};
I 2
static	char *tahoeinames[] = {
	"clock", "cnr", "cnx", "rmtr", "rmtx", "buserr",
};
E 2
static	struct stdintrs {
	char	**si_names;	/* list of standard interrupt names */
	int	si_n;		/* number of such names */
} stdintrs[] = {
	{ vaxinames, sizeof (vaxinames) / sizeof (vaxinames[0]) },
I 2
	{ tahoeinames, (sizeof (tahoeinames) / sizeof (tahoeinames[0])) }
E 2
};
/*
 * Start the interrupt name table with the names
 * of the standard vectors not directly associated
 * with a bus.  Also, dump the defines needed to
 * reference the associated counters into a separate
 * file which is prepended to locore.s.
 */
dump_std(fp, gp)
	register FILE *fp, *gp;
{
	register struct stdintrs *si = &stdintrs[machine-1];
	register char **cpp;
	register int i;

	fprintf(fp, "\n\t.globl\t_intrnames\n");
	fprintf(fp, "\n\t.globl\t_eintrnames\n");
	fprintf(fp, "\t.data\n");
	fprintf(fp, "_intrnames:\n");
	cpp = si->si_names;
	for (i = 0; i < si->si_n; i++) {
		register char *cp, *tp;
		char buf[80];

		cp = *cpp;
		if (cp[0] == 'i' && cp[1] == 'n' && cp[2] == 't') {
			cp += 3;
			if (*cp == 'r')
				cp++;
		}
		for (tp = buf; *cp; cp++)
			if (islower(*cp))
				*tp++ = toupper(*cp);
			else
				*tp++ = *cp;
		*tp = '\0';
		fprintf(gp, "#define\tI_%s\t%d\n", buf, i*sizeof (long));
		fprintf(fp, "\t.asciz\t\"%s\"\n", *cpp);
		cpp++;
	}
}

dump_intname(fp, vector, number)
	register FILE *fp;
	char *vector;
	int number;
{
	register char *cp = vector;

	fprintf(fp, "\t.asciz\t\"");
	/*
	 * Skip any "int" or "intr" in the name.
	 */
	while (*cp)
		if (cp[0] == 'i' && cp[1] == 'n' &&  cp[2] == 't') {
			cp += 3;
			if (*cp == 'r')
				cp++;
		} else {
			putc(*cp, fp);
			cp++;
		}
	fprintf(fp, "%d\"\n", number);
}

/*
 * Reserve space for the interrupt counters.
 */
dump_ctrs(fp)
	register FILE *fp;
{
	struct stdintrs *si = &stdintrs[machine-1];

	fprintf(fp, "_eintrnames:\n");
	fprintf(fp, "\n\t.globl\t_intrcnt\n");
	fprintf(fp, "\n\t.globl\t_eintrcnt\n");
	fprintf(fp, "\t.align 2\n");
	fprintf(fp, "_intrcnt:\n");
	fprintf(fp, "\t.space\t4 * %d\n", si->si_n);
D 3
	fprintf(fp, "_fltintrcnt:\n", cntcnt);
E 3
I 3
D 4
	fprintf(fp, "_fltintrcnt: %d\n", cntcnt);
E 4
I 4
	fprintf(fp, "_fltintrcnt:\n");
E 4
E 3
	fprintf(fp, "\t.space\t4 * %d\n", cntcnt);
	fprintf(fp, "_eintrcnt:\n\n");
	fprintf(fp, "\t.text\n");
}
E 1
