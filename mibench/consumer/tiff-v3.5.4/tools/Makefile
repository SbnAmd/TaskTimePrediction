#	$Header: /home/mguthaus/.cvsroot/mibench/consumer/tiff-v3.5.4/tools/Makefile.in,v 1.1.1.1 2000/11/06 19:52:31 mguthaus Exp $
#
# Warning, this file was automatically created by the TIFF configure script
#
# TIFF Library Tools
#
# Copyright (c) 1988-1997 Sam Leffler
# Copyright (c) 1991-1997 Silicon Graphics, Inc.
# 
# Permission to use, copy, modify, distribute, and sell this software and 
# its documentation for any purpose is hereby granted without fee, provided
# that (i) the above copyright notices and this permission notice appear in
# all copies of the software and related documentation, and (ii) the names of
# Sam Leffler and Silicon Graphics may not be used in any advertising or
# publicity relating to the software without the specific, prior written
# permission of Stanford and Silicon Graphics.
# 
# THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND, 
# EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY 
# WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  
# 
# IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
# ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
# OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
# WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF 
# LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE 
# OF THIS SOFTWARE.
#
DEPTH	= ..

SRCDIR	= ../tools
LIBDIR	= ../libtiff

#
# VERSION:	v3.5.4
# DATE:		‫دوشنبه ۲۶ مئی ۲۵، ساعات ۱۸:۲۸:۳۹ (+0330)‬
# TARGET:	x86_64-unknown-linux
# CCOMPILER:	/usr/bin/gcc
#
SHELL	= /usr/bin/sh
NULL	=
CC	= /usr/bin/gcc
INSTALL	= ${SHELL} ../port/install.sh
#
COPTS	= 
OPTIMIZER=-O
IPATH	= -I. -I${SRCDIR} -I${LIBDIR}
CFLAGS	=  ${COPTS} ${OPTIMIZER} ${IPATH}
#
TIFFLIB	= ${DEPTH}/libtiff/libtiff.a
LIBJPEG	= 
LIBGZ	= 
LIBTIFF	= ${DEPTH}/libtiff/libtiff.a
LIBPORT	= 
MACHLIBS= 
LIBS	= ${LIBTIFF} ${LIBJPEG} ${LIBGZ} ${LIBPORT} ${MACHLIBS}
#
OBJS=	\
	fax2tiff.o \
	fax2ps.o \
	gif2tiff.o \
	pal2rgb.o \
	ppm2tiff.o \
	rgb2ycbcr.o \
	ras2tiff.o \
	thumbnail.o \
	tiff2bw.o \
	tiff2rgba.o \
	tiff2ps.o \
	tiffcmp.o \
	tiffcp.o \
	tiffdither.o \
	tiffdump.o \
	tiffinfo.o \
	tiffmedian.o \
	tiffsplit.o \
	${NULL}
TARGETS	=\
	fax2tiff \
	fax2ps \
	gif2tiff \
	pal2rgb \
	ppm2tiff \
	rgb2ycbcr \
	thumbnail \
	ras2tiff \
	tiff2bw \
	tiff2rgba \
	tiff2ps \
	tiffcmp \
	tiffcp \
	tiffdither \
	tiffdump \
	tiffinfo \
	tiffmedian \
	tiffsplit \
	${NULL}

all:	${TARGETS}
	@if [ "no" = yes ]; then \
	    ${MAKE} sgi2tiff; \
	else \
	    true; \
	fi
	@if [ "no" = yes ]; then \
	    ${MAKE} tiffgt tiffsv; \
	else \
	    true; \
	fi
install: all
	${INSTALL} -idb nostrip tiff.sw.tools -m 755 -dir bin
	${INSTALL} -idb nostrip tiff.sw.tools -m 755 -F bin -O ${TARGETS}
	@if [ "no" = yes ]; then \
	    ${INSTALL} -idb tiff.sw.tools -m 755 -F bin -O sgi2tiff; \
	else \
	    true; \
	fi
	@if [ "no" = yes ]; then \
	    ${INSTALL} -idb tiff.sw.tools -m 755 -F bin -O tiffgt tiffsv;\
	else \
	    true; \
	fi
clean:
	rm -f ${TARGETS} ${OBJS} sgigt.o tiffgt sgisv.o tiffsv \
	    sgi2tiff.o sgi2tiff core a.out ycbcr 

#
# System-independent tools
#

tiffinfo: tiffinfo.o ${TIFFLIB}
	${CC} -o tiffinfo ${CFLAGS} tiffinfo.o ${LIBS}
tiffinfo.o: ${SRCDIR}/tiffinfo.c
	${CC} -c ${CFLAGS} ${SRCDIR}/tiffinfo.c

tiffcmp:tiffcmp.o ${TIFFLIB}
	${CC} -o tiffcmp ${CFLAGS} tiffcmp.o ${LIBS}
tiffcmp.o: ${SRCDIR}/tiffcmp.c
	${CC} -c ${CFLAGS} ${SRCDIR}/tiffcmp.c

tiffcp:	tiffcp.o ${TIFFLIB}
	${CC} -o tiffcp ${CFLAGS} tiffcp.o ${LIBS}
tiffcp.o: ${SRCDIR}/tiffcp.c
	${CC} -c ${CFLAGS} ${SRCDIR}/tiffcp.c

tiffdump: tiffdump.o
	${CC} -o tiffdump ${CFLAGS} tiffdump.o ${LIBS}
tiffdump.o: ${SRCDIR}/tiffdump.c
	${CC} -c ${CFLAGS} ${SRCDIR}/tiffdump.c

tiffmedian: tiffmedian.o ${TIFFLIB}
	${CC} -o tiffmedian ${CFLAGS} tiffmedian.o ${LIBS}
tiffmedian.o: ${SRCDIR}/tiffmedian.c
	${CC} -c ${CFLAGS} ${SRCDIR}/tiffmedian.c

tiffsplit: tiffsplit.o ${TIFFLIB}
	${CC} -o tiffsplit ${CFLAGS} tiffsplit.o ${LIBS}
tiffsplit.o: ${SRCDIR}/tiffsplit.c
	${CC} -c ${CFLAGS} ${SRCDIR}/tiffsplit.c

tiff2ps: tiff2ps.o ${TIFFLIB}
	${CC} -o tiff2ps ${CFLAGS} tiff2ps.o ${LIBS}
tiff2ps.o: ${SRCDIR}/tiff2ps.c
	${CC} -c ${CFLAGS} ${SRCDIR}/tiff2ps.c

#
# Junky stuff... programs that are more examples of how
# to use the library than full-blown useful tools.
#

# convert RGB image to B&W
tiff2bw: tiff2bw.o ${TIFFLIB}
	${CC} -o tiff2bw ${CFLAGS} tiff2bw.o ${LIBS}
tiff2bw.o: ${SRCDIR}/tiff2bw.c
	${CC} -c ${CFLAGS} ${SRCDIR}/tiff2bw.c

# convert anything to RGBA.
tiff2rgba: tiff2rgba.o ${TIFFLIB}
	${CC} -o tiff2rgba ${CFLAGS} tiff2rgba.o ${LIBS}
tiff2rgba.o: ${SRCDIR}/tiff2rgba.c
	${CC} -c ${CFLAGS} ${SRCDIR}/tiff2rgba.c

# convert B&W image to bilevel w/ FS dithering
tiffdither: tiffdither.o ${TIFFLIB}
	${CC} -o tiffdither ${CFLAGS} tiffdither.o ${LIBS}
tiffdither.o: ${SRCDIR}/tiffdither.c
	${CC} -c ${CFLAGS} ${SRCDIR}/tiffdither.c

# simple Sun rasterfile converter
ras2tiff: ras2tiff.o ${TIFFLIB}
	${CC} -o ras2tiff ${CFLAGS} ras2tiff.o ${LIBS}
ras2tiff.o: ${SRCDIR}/ras2tiff.c
	${CC} -c ${CFLAGS} ${SRCDIR}/ras2tiff.c

# simple GIF converter
gif2tiff: gif2tiff.o ${TIFFLIB}
	${CC} -o gif2tiff ${CFLAGS} gif2tiff.o ${LIBS}
gif2tiff.o: ${SRCDIR}/gif2tiff.c
	${CC} -c ${CFLAGS} ${SRCDIR}/gif2tiff.c

# very limited PBM converter
ppm2tiff: ppm2tiff.o ${TIFFLIB}
	${CC} -o ppm2tiff ${CFLAGS} ppm2tiff.o ${LIBS}
ppm2tiff.o: ${SRCDIR}/ppm2tiff.c
	${CC} -c ${CFLAGS} ${SRCDIR}/ppm2tiff.c

# Group 3/4 FAX file converter
fax2tiff: fax2tiff.o ${TIFFLIB}
	${CC} -o fax2tiff ${CFLAGS} fax2tiff.o ${LIBS}
fax2tiff.o: ${SRCDIR}/fax2tiff.c
	${CC} -c -I${LIBDIR} -I${DEPTH}/libtiff ${CFLAGS} ${SRCDIR}/fax2tiff.c

# Group 3/4 FAX to encoded PS converter
fax2ps: fax2ps.o ${TIFFLIB}
	${CC} -o fax2ps ${CFLAGS} fax2ps.o ${LIBS}
fax2ps.o: ${SRCDIR}/fax2ps.c
	${CC} -c ${CFLAGS} ${SRCDIR}/fax2ps.c

# convert Palette image to RGB
pal2rgb: pal2rgb.o ${TIFFLIB}
	${CC} -o pal2rgb ${CFLAGS} pal2rgb.o ${LIBS}
pal2rgb.o: ${SRCDIR}/pal2rgb.c
	${CC} -c ${CFLAGS} ${SRCDIR}/pal2rgb.c

# convert RGB image to YCbCr
rgb2ycbcr: rgb2ycbcr.o ${TIFFLIB}
	${CC} -o rgb2ycbcr ${CFLAGS} rgb2ycbcr.o ${LIBS}
rgb2ycbcr.o: ${SRCDIR}/rgb2ycbcr.c
	${CC} -c ${CFLAGS} ${SRCDIR}/rgb2ycbcr.c

# generate thumbnail images from fax (example of SubIFD usage)
thumbnail: thumbnail.o ${TIFFLIB}
	${CC} -o thumbnail ${CFLAGS} thumbnail.o ${LIBS}
thumbnail.o: ${SRCDIR}/thumbnail.c
	${CC} -c ${CFLAGS} ${SRCDIR}/thumbnail.c

#
# System-specific tools.
#

#
# sgi2tiff converts SGI RGB images to TIFF; it requires
# the SGI image library -limage.
#
sgi2tiff: sgi2tiff.o ${TIFFLIB}
	${CC} -o sgi2tiff ${CFLAGS} sgi2tiff.o -limage ${LIBS}
sgi2tiff.o: ${SRCDIR}/sgi2tiff.c
	${CC} -c ${CFLAGS} ${SRCDIR}/sgi2tiff.c

# SGI versions of tiffgt & tiffsv that require -lgl
tiffgt:	sgigt.o ${TIFFLIB}
	${CC} -o tiffgt ${CFLAGS} sgigt.o -lgutil -lgl ${LIBS}
sgigt.o: ${SRCDIR}/sgigt.c
	${CC} -c ${CFLAGS} ${SRCDIR}/sgigt.c

tiffsv:	sgisv.o ${TIFFLIB}
	${CC} -o tiffsv ${CFLAGS} sgisv.o -lgutil -lgl ${LIBS}
sgisv.o: ${SRCDIR}/sgisv.c
	${CC} -c ${CFLAGS} ${SRCDIR}/sgisv.c
