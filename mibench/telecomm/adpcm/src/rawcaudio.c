/* testc - Test adpcm coder */

#include "adpcm.h"
#include <stdio.h>
#include "rawaudio.h"

struct adpcm_state state_c;

#define NSAMPLES 1000

char	abuf_c[NSAMPLES/2];
short	sbuf_c[NSAMPLES];

// main() {
void _rawcaudio() {
    int n;

    while(1) {
	n = read(0, sbuf_c, NSAMPLES*2);
	if ( n < 0 ) {
	    perror("input file");
	    exit(1);
	}
	if ( n == 0 ) break;
	adpcm_coder(sbuf_c, abuf_c, n/2, &state_c);
	write(1, abuf_c, n/4);
    }
    fprintf(stderr, "Final valprev=%d, index=%d\n",
	    state_c.valprev, state_c.index);
    exit(0);
}
