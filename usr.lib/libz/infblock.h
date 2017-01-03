/*
 * This code has been derived from Jean-loup Gailly's zlib.
 * It has been integrated into Berkeley UNIX by Michael Sokolov
 *
 *	@(#)infblock.h	5.1 (Berkeley) 1/18/99
 */

/* WARNING: this file should *not* be used by applications. It is
   part of the implementation of the compression library and is
   subject to change. Applications should only use zlib.h.
 */

struct inflate_blocks_state;
typedef struct inflate_blocks_state FAR inflate_blocks_statef;

extern inflate_blocks_statef * inflate_blocks_new OF((
    z_streamp z,
    check_func c,               /* check function */
    uInt w));                   /* window size */

extern int inflate_blocks OF((
    inflate_blocks_statef *,
    z_streamp ,
    int));                      /* initial return code */

extern void inflate_blocks_reset OF((
    inflate_blocks_statef *,
    z_streamp ,
    uLongf *));                  /* check value on output */

extern int inflate_blocks_free OF((
    inflate_blocks_statef *,
    z_streamp ,
    uLongf *));                  /* check value on output */

extern void inflate_set_dictionary OF((
    inflate_blocks_statef *s,
    const Bytef *d,  /* dictionary */
    uInt  n));       /* dictionary length */