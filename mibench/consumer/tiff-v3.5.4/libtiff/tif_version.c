/* $Header: /home/mguthaus/.cvsroot/mibench/consumer/tiff-v3.5.4/libtiff/tif_version.c,v 1.1.1.1 2000/11/06 19:52:27 mguthaus Exp $ */
/*
 * Copyright (c) 1992-1997 Sam Leffler
 * Copyright (c) 1992-1997 Silicon Graphics, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and 
 * its documentation for any purpose is hereby granted without fee, provided
 * that (i) the above copyright notices and this permission notice appear in
 * all copies of the software and related documentation, and (ii) the names of
 * Sam Leffler and Silicon Graphics may not be used in any advertising or
 * publicity relating to the software without the specific, prior written
 * permission of Sam Leffler and Silicon Graphics.
 * 
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY 
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  
 * 
 * IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
 * ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF 
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE 
 * OF THIS SOFTWARE.
 */
#include "tiffiop.h"
// #include "version.h"

#define VERSION \
"LIBTIFF, Version 3.4beta028 \n"\
"Copyright (c) 1988-1995 Sam Leffler\n"\
"Copyright (c) 1991-1996 Silicon Graphics, Inc."

static const char TIFFVersion[] = VERSION;

const char*
TIFFGetVersion(void)
{
	return (TIFFVersion);
}
