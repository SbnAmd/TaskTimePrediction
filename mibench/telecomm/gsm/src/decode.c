/*
 * Copyright 1992 by Jutta Degener and Carsten Bormann, Technische
 * Universitaet Berlin.  See the accompanying file "COPYRIGHT" for
 * details.  THERE IS ABSOLUTELY NO WARRANTY FOR THIS SOFTWARE.
 */

/* $Header: /home/mguthaus/.cvsroot/mibench/telecomm/gsm/src/decode.c,v 1.1.1.1 2000/11/06 19:54:25 mguthaus Exp $ */

#include <stdio.h>

#include	"../inc/private.h"
#include	"../inc/gsm.h"
#include	"../inc/proto.h"

/*
 *  4.3 FIXED POINT IMPLEMENTATION OF THE RPE-LTP DECODER
 */

static void Postprocessing P2((S,s),
	struct gsm_state	* S,
	register word 		* s)
{
	register int		k;
	register word		msr = S->msr;
	register longword	ltmp;	/* for GSM_ADD */
	register word		tmp;

	for (k = 160; k--; s++) {
		tmp = GSM_MULT_R( msr, 28180 );
		msr = GSM_ADD(*s, tmp);  	   /* Deemphasis 	     */
		*s  = GSM_ADD(msr, msr) & 0xFFF8;  /* Truncation & Upscaling */
	}
	S->msr = msr;
}

void Gsm_Decoder P8((S,LARcr, Ncr,bcr,Mcr,xmaxcr,xMcr,s),
	struct gsm_state	* S,

	word		* LARcr,	/* [0..7]		IN	*/

	word		* Ncr,		/* [0..3] 		IN 	*/
	word		* bcr,		/* [0..3]		IN	*/
	word		* Mcr,		/* [0..3] 		IN 	*/
	word		* xmaxcr,	/* [0..3]		IN 	*/
	word		* xMcr,		/* [0..13*4]		IN	*/

	word		* s)		/* [0..159]		OUT 	*/
{
	int		j, k;
	word		erp[40], wt[160];
	word		* drp = S->dp0 + 120;

	for (j=0; j <= 3; j++, xmaxcr++, bcr++, Ncr++, Mcr++, xMcr += 13) {

		Gsm_RPE_Decoding( S, *xmaxcr, *Mcr, xMcr, erp );
		Gsm_Long_Term_Synthesis_Filtering( S, *Ncr, *bcr, erp, drp );

		for (k = 0; k <= 39; k++) wt[ j * 40 + k ] =  drp[ k ];
	}

	Gsm_Short_Term_Synthesis_Filter( S, LARcr, wt, s );
	Postprocessing(S, s);
}
