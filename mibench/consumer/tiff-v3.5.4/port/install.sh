#! /usr/bin/sh
#	$Header: /home/mguthaus/.cvsroot/mibench/consumer/tiff-v3.5.4/port/install.sh.in,v 1.1.1.1 2000/11/06 19:52:31 mguthaus Exp $
#
# Warning, this file was automatically created by the TIFF configure script
#
# HylaFAX Facsimile Software
#
# Copyright (c) 1990-1997 Sam Leffler
# Copyright (c) 1991-1997 Silicon Graphics, Inc.
# HylaFAX is a trademark of Silicon Graphics
# 
# Permission to use, copy, modify, distribute, and sell this software and 
# its documentation for any purpose is hereby granted without fee, provided
# that (i) the above copyright notices and this permission notice appear in
# all copies of the software and related documentation, and (ii) the names of
# Sam Leffler and Silicon Graphics may not be used in any advertising or
# publicity relating to the software without the specific, prior written
# permission of Sam Leffler and Silicon Graphics.
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

#
# Warning, this file was automatically created by the HylaFAX configure script
#
# VERSION:	v3.5.4
# DATE:		‫دوشنبه ۲۶ مئی ۲۵، ساعات ۱۸:۲۸:۳۹ (+0330)‬
# TARGET:	x86_64-unknown-linux
#

#
# Shell script to emulate Silicon Graphics install program.
# We emulate the non-standard interface used by install so
# that we can build SGI inst packages on SGI systems.  Note
# that we cannot emulate everything because we don't maintain
# a history of installed software; thus we cannot tell when
# configuration files have been modified and save old copies.
#
# NB: we don't do chown/chmod/chgrp by default; it must be
#     explicitly set on the command line.
#

#
# install [options] files ...
# 
# Options are:
#
# -o		save existing target foo as OLDfoo
# -O		remove existing target foo, if it fails save as OLDfoo
# -m mode	set mode of installed target
# -u uid	set uid of installed target
# -g gid	set gid of installed target
# -root path	set ROOT directory for target pathnames
# -dir		create directories
# -fifo		create FIFO special files
# -ln path	create hard link
# -lns path	create symbolic link
# -src path	source pathname different from target
# -f dir	install files in the target directory ROOT/dir
# -F dir	like -f, but create directories that do not exist
# -v		echo actions
# -idb stuff	specify package and, optionally, do special work
#
preopts=
postopts=
SaveFirst=no
HasSource=yes
RemoveFirst=no
NoUpdate=no
Suggested=no
Updated=no

CMD=cp
SRC=
FILES=
DESTDIR="."
ROOT="."
CHMOD=":"
CHOWN=":"
CHGRP=":"
RM="rm -f"
MV="mv -f"
ECHO=echo
VERBOSE=":"
STRIP="/usr/bin/strip"
CMP=cmp

TARGETS=
while [ x"$1" != x ]
do
    arg=$1
    case $arg in
    -m)		shift; CHMOD="/usr/bin/chmod $1";;
    -u)		shift; CHOWN="@CHOWN@ $1";;
    -g)		shift; CHGRP="@CHGRP@ $1";;
    -o)		SaveFirst=yes;;
    -O)		RemoveFirst=yes; SaveFirst=yes;;
    -root)	shift; ROOT=$1;;
    -dir)	CMD=mkdir; HasSource=no;
		RM=":"; STRIP=":"
		;;
    -fifo)	CMD=@MKFIFO@; HasSource=no;
		x=`echo $CMD | /usr/bin/sed 's;.*/;;'`;
		test $x = mknod && postopts="p";
		STRIP=":"
		;;
    -ln)	shift; CMD=/usr/bin/ln; SRC="$1"
		STRIP=":"
		;;
    -lns)	shift; CMD=/usr/bin/ln; preopts="-s"; SRC="$1"
		STRIP=":"
		;;
    -src)	shift; SRC="$1";;
    -[fF])	shift; DESTDIR="$1";;
    -idb)	shift; opt="$1"
		case "$opt" in
		*config\(update\)*)	Updated=yes;;
		*config\(suggest\)*)	Suggested=yes;;
		*config\(noupdate\)*)	NoUpdate=yes;;
		*nostrip*)		STRIP=":";;
		esac
		;;
    # these are skipped/not handled
    -new|-rawidb|-blk|-chr) shift;;
    -v)		VERBOSE=$ECHO;;
    -*) 	;;
    *)		TARGETS="$TARGETS $arg";;
    esac
    shift
done

#
# Install the specified target.
#
install()
{
    src=$1 target=$2
    if [ $RemoveFirst = yes -a -f $target ]; then
	$VERBOSE "$RM $target"
	$RM $target
    fi
    if [ $SaveFirst = yes -a -f $target ]; then
	bf=`echo $src | /usr/bin/sed 's;.*/;;'`
	$VERBOSE "$MV $target $ROOT/$DESTDIR/OLD$bf"
	$MV $target $ROOT/$DESTDIR/OLD$bf
    fi
    if [ -z "$SRC" -a $HasSource = yes ]; then
	$VERBOSE "$CMD $preopts $src $target $postopts"
	$CMD $preopts $f $target $postopts
    else
	$VERBOSE "$CMD $preopts $SRC $target $postopts"
	$CMD $preopts $SRC $target $postopts
    fi
    if [ $? -eq 0 ]; then
	$VERBOSE "$CHOWN $target"
	$CHOWN $target
	$VERBOSE "$CHGRP $target"
	$CHGRP $target
	$VERBOSE "$CHMOD $target"
	$CHMOD $target
	if [ $STRIP != ":" -a -x $ROOT/$DESTDIR/$f ]; then
	    $STRIP $target >/dev/null 2>&1 || true
	    $VERBOSE "$STRIP $target"
	fi
    fi
}

if [ $Suggested = yes ]; then
    #
    # A suggested file.  If an existing target does
    # not exist, then install it.  Otherwise, install
    # it as target.N if it's different from the current
    # installed target.
    #
    # NB: cannot be used with a special file 'cuz we
    #     use test -f to see if the file exists.
    #
    for f in $TARGETS; do
	t=$ROOT/$DESTDIR/$f
	if [ -f $t ]; then
	    if [ -z "$SRC" -a $HasSource = yes ]; then
		$CMP -s $f $t || {
		    $ECHO "*** Warning, target has local changes, installing $f as $t.N"
		    install $f $t.N;
		}
	    else
		$CMP -s $SRC $t || {
		    $ECHO "*** Warning, target has local changes, installing $f as $t.N"
		    install $f $t.N
		}
	    fi
	else
	    install $f $t
	fi
    done
elif [ $Updated = yes ]; then
    #
    # A file to be updated.  If an existing target does
    # not exist, then install it.  Otherwise, install
    # it as target and save the old version as target.O
    # if the old version is different from the current
    # installed target.
    #
    # NB: cannot be used with a special file 'cuz we
    #     use test -f to see if the file exists.
    #
    for f in $TARGETS; do
	t=$ROOT/$DESTDIR/$f
	if [ -f $t ]; then
	    if [ -z "$SRC" -a $HasSource = yes ]; then
		$CMP -s $f $t || $MV $t $t.O
	    else
		$CMP -s $SRC $t || $MV $t $t.O
	    fi
	fi
	install $f $t
    done
elif [ $NoUpdate = yes ]; then
    #
    # A file that is never to be updated; the target
    # is created only if it does not exist.
    #
    # NB: cannot be used with a special file 'cuz we
    #     use test -f to see if the file exists.
    #
    for f in $TARGETS; do
	t=$ROOT/$DESTDIR/$f
	test -f $t || install $f $t
    done
else
    #
    # Normal case, a target that should be installed
    # with the existing copy, optionally, saved first.
    #
    for f in $TARGETS; do
	install $f $ROOT/$DESTDIR/$f
    done
fi
