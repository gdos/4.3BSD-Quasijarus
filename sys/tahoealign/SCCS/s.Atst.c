h34251
s 00016/00000/00000
d D 1.1 86/07/20 11:14:48 sam 1 0
c date and time created 86/07/20 11:14:48 by sam
e
u
U
t
T
I 1
/*	%M%	%I%	%E%	*/

#include "../tahoealign/align.h" 
tst(infop)	process_info *infop;
/*
/*	Test operand, set condition codes.
/*
/************************************************/
{
	register long quantity;

	quantity = operand(infop,0)->data;
	if (quantity < 0) negative_1; else negative_0;
	if (quantity == 0) zero_1; else zero_0;
	overflow_0; carry_1;
}
E 1
