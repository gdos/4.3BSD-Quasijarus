/*
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
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
 *
 *	@(#)confdec.c	7.1 (Berkeley) 2/28/04
 */

#include "param.h"
#include "inode.h"
#include "fs.h"
#include "saio.h"

extern int	nullsys(), nodev(), noioctl();

int	vmbopen(), vmbstrategy();
int	romopen(), romstrategy();

struct devsw devsw[] = {
	{ "vmb", vmbstrategy,	vmbopen,	nullsys,	noioctl },
	{ "rom", romstrategy,	romopen,	nullsys,	noioctl },
};

int	ndevs = (sizeof(devsw)/sizeof(devsw[0]));
