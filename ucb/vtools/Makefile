#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	@(#)Makefile	6.3	(Berkeley)	10/26/04
#
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	fcvt.c rotate.c rotprt.c vfontinfo.c vfw.c vwidth.c
OBJS=	fcvt.o rotate.o rotprt.o vfontinfo.o vfw.o vwidth.o
ALL=	fcvt rotate rotprt vfontinfo vfw vwidth

all: ${ALL} fed

fcvt: ${LIBC}
	${CC} -o $@ ${CFLAGS} fcvt.c
rotate: ${LIBC}
	${CC} -o $@ ${CFLAGS} rotate.c
rotprt: ${LIBC}
	${CC} -o $@ ${CFLAGS} rotprt.c
vfontinfo: ${LIBC}
	${CC} -o $@ ${CFLAGS} vfontinfo.c
vfw: ${LIBC}
	${CC} -o $@ ${CFLAGS} vfw.c
vwidth: ${LIBC}
	${CC} -o $@ ${CFLAGS} vwidth.c

fed: FRC
	cd fed; make ${MFLAGS}

clean: FRC
	rm -f ${OBJS} core ${ALL}
	cd fed; make ${MFLAGS} clean

ldepend: FRC
	mkdep -p ${CFLAGS} ${SRCS}

depend:	ldepend FRC
	cd fed; make ${MFLAGS} depend

install: FRC
	install -s -o bin -g bin -m 755 ${ALL} ${DESTDIR}/usr/ucb
	cd fed; make ${MFLAGS} install

lint: FRC
	lint ${CFLAGS} ${SRCS}

tags: FRC
	ctags ${SRCS}

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

fcvt: fcvt.c /usr/include/stdio.h /usr/include/vfont.h
rotate: rotate.c /usr/include/stdio.h /usr/include/vfont.h
rotate: /usr/include/sys/types.h /usr/include/sys/stat.h
rotprt: rotprt.c /usr/include/stdio.h /usr/include/vfont.h
rotprt: /usr/include/sys/types.h /usr/include/sys/stat.h
vfontinfo: vfontinfo.c /usr/include/stdio.h /usr/include/ctype.h
vfontinfo: /usr/include/vfont.h
vfw: vfw.c /usr/include/stdio.h
vwidth: vwidth.c /usr/include/stdio.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
