/*
 * Copyright 1992 by Jutta Degener and Carsten Bormann, Technische
 * Universitaet Berlin.  See the accompanying file "COPYRIGHT" for
 * details.  THERE IS ABSOLUTELY NO WARRANTY FOR THIS SOFTWARE.
 */

#include <string.h>
static char	ident[] = "$Header: /home/mguthaus/.cvsroot/mibench/telecomm/gsm/src/gsm_create.c,v 1.1.1.1 2000/11/06 19:54:25 mguthaus Exp $";

#include	"../inc/config.h"

#ifdef	HAS_STRING_H
#include	<string.h>
#else
#	include "../inc/proto.h"
	// extern char	* memset P((char *, int, int));
#endif

#ifdef	HAS_STDLIB_H
#	include	<stdlib.h>
#else
#	ifdef	HAS_MALLOC_H
#		include 	<malloc.h>
#	else
		extern char * malloc();
#	endif
#endif

#include <stdio.h>

#include "../inc/gsm.h"
#include "../inc/private.h"
#include "../inc/proto.h"

gsm gsm_create P0()
{
	gsm  r;

#ifdef	USE_TABLE_MUL

	static int mul_init = 0;
	if (!mul_init) {
		mul_init = 1;
		init_umul_table();
	}

#endif

	r = (gsm)malloc(sizeof(struct gsm_state));
	if (!r) return r;

	memset((char *)r, 0, sizeof(*r));
	r->nrp = 40;

	return r;
}
