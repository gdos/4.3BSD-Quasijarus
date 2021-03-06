h27282
s 00055/00000/00000
d D 7.1 04/03/18 19:09:31 msokolov 1 0
c date and time created 04/03/18 19:09:31 by msokolov
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */

#ifdef VAX410
#include "param.h"
#include "time.h"
#include "kernel.h"
#include "vmmac.h"

#include "mtpr.h"
#include "cpu.h"
#include "clock.h"
#include "pte.h"
#include "78032.h"
#include "../babyvax/bvreg.h"

/*
 * 410-specific routines
 */

ka410_init()
{
	if (bv_regs.bvr_cfgtst & CFGTST_MULTU)
		printf("MicroVAX 2000 (KA410)\n");
	else
		printf("VAXstation 2000 (KA410)\n");
}

ka410_memnop()
{

	/* void */
}

ka410_mchk(cmcf)
	caddr_t cmcf;
{
	register struct mcuv2frame *mcf = (struct mcuv2frame *)cmcf;
	register u_int type = mcf->mcuv2_summary;
	extern char *mcuv2[];

	printf("machine check %x", type);
	if (type < NMCUV2 && mcuv2[type])
		printf(": %s", mcuv2[type]);
	printf("\n\tvap %x istate %x pc %x psl %x\n",
	    mcf->mcuv2_mrvaddr, mcf->mcuv2_istate,
	    mcf->mcuv2_pc, mcf->mcuv2_psl);
	return (MCHK_PANIC);
}
#endif
E 1
