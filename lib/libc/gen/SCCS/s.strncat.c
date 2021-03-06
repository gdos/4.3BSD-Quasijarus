h57635
s 00002/00002/00026
d D 5.2 86/03/09 19:58:23 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00024
d D 5.1 85/06/05 12:37:36 mckusick 2 1
c Add copyright
e
s 00025/00000/00000
d D 4.1 80/12/21 16:40:17 wnj 1 0
c date and time created 80/12/21 16:40:17 by wnj
e
u
U
t
T
I 1
D 2
/* %W% (Berkeley) %G% */
E 2
I 2
D 3
#ifndef lint
E 3
I 3
#if defined(LIBC_SCCS) && !defined(lint)
E 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
#endif LIBC_SCCS and not lint
E 3

E 2
/*
 * Concatenate s2 on the end of s1.  S1's space must be large enough.
 * At most n characters are moved.
 * Return s1.
 */

char *
strncat(s1, s2, n)
register char *s1, *s2;
register n;
{
	register char *os1;

	os1 = s1;
	while (*s1++)
		;
	--s1;
	while (*s1++ = *s2++)
		if (--n < 0) {
			*--s1 = '\0';
			break;
		}
	return(os1);
}
E 1
