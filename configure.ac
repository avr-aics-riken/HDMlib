###
#########################################################################
#
# HDMlib - Hierarchical Data Management library
#
# Copyright (c) 2014-2015 Advanced Institute for Computational Science, RIKEN.
# All rights reserved.
#
#########################################################################
###

#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.57])
AC_INIT([HDMlib], [0.6.0], [keno@riken.jp],[HDMlib])
AM_INIT_AUTOMAKE()
AC_CONFIG_SRCDIR([src/ErrorUtil.cpp])
AC_CONFIG_HEADERS([config.h])

# revision No.
HDM_REVISION="20150530_1600"
AC_SUBST(HDM_REVISION)

#
# default prefix setting
#
AC_PREFIX_DEFAULT([/usr/local/HDMlib])
if test "$prefix" = "NONE" ; then
  HDM_INST_DIR=/usr/local/HDMlib
else
  HDM_INST_DIR="$prefix"
fi



#
# MPI environment
#
enable_mpi="none"


HDM_CXX="$CXX"
AC_SUBST(HDM_CXX)

case "$HDM_CXX" in
  mpicxx)   enable_mpi="wrappermpi" ;;
  mpicc)    enable_mpi="wrappermpi" ;;
  mpiCC)    enable_mpi="wrappermpi" ;;
  mpic++)   enable_mpi="wrappermpi" ;;
  mpiFCCpx) enable_mpi="wrappermpi" ;;
  CC)       enable_mpi="wrappermpi" ;;
  mpiicc)   enable_mpi="wrappermpi" ;;
  mpiicpc)  enable_mpi="wrappermpi" ;;
esac


AC_SUBST(MPI_DIR)
AC_SUBST(MPI_CFLAGS)
AC_SUBST(MPI_LDFLAGS)
AC_SUBST(MPI_LIBS)


# 
# MPI library
#
AC_ARG_WITH(MPI, [AC_HELP_STRING([--without-MPI],[do not use MPI library])], , with_MPI=yes)
if test "$with_MPI" = "no" ; then
  CXXFLAGS=-D_HDM_WITHOUT_MPI_
else

  # openmpi
  AC_ARG_WITH( ompi, [AC_HELP_STRING([--with-ompi=dir],[Specify OpenMPI install directory])], , with_ompi=none)
  if test "$with_ompi" != "none" ; then
    MPI_DIR=$with_ompi;
    MPI_CFLAGS=-I$MPI_DIR/include
    MPI_LDFLAGS=-L$MPI_DIR/lib
    MPI_LIBS=-lmpi
    enable_mpi="ompi"
  fi
fi


#
# Warning
#

if test "$with_MPI" = "yes" ; then
  if test "$enable_mpi" != "wrappermpi" ; then
    if test "$with_ompi" = "none" ; then
      echo "  Warning: OpenMPI library is not specified."
      echo "           If compilation error occurs about MPI, specify --with-ompi option."
    fi
  fi
fi



#
# TextParser environment
#
AC_ARG_WITH(parser, [AC_HELP_STRING([--with-parser=dir],[Specify TextParser install directory])], , with_parser=none)
AC_SUBST(TP_DIR)
AC_SUBST(TP_CFLAGS)
AC_SUBST(TP_LDFLAGS)

if test "$with_parser" != "none" ; then
  TP_DIR=$with_parser;
  TP_CFLAGS=`$TP_DIR/bin/tp-config --cflags`
  TP_LDFLAGS=`$TP_DIR/bin/tp-config --libs`
else
  echo "  Error: TextParser library is not specified."
  echo "         Specify --with-parser option."
  exit 1
fi



#
# BCMlib
#
AC_ARG_WITH(bcm, [AC_HELP_STRING([--with-bcm=dir],[Specify BCMlib install directory])], , with_bcm=none)
AC_SUBST(BCM_DIR)
AC_SUBST(BCM_CFLAGS)
AC_SUBST(BCM_LDFLAGS)

if test "$with_bcm" != "none" ; then
  BCM_DIR=$with_bcm;
  BCM_CFLAGS=`$BCM_DIR/bin/bcm-config --cflags`
  BCM_LDFLAGS=`$BCM_DIR/bin/bcm-config --libs`
else
  echo "  Error: BCM library is not specified."
  echo "         Specify --with-bcm option."
  exit 1
fi



#
# HDM special flags
#
HDM_CFLAGS="-I$HDM_INST_DIR/include"
AC_SUBST(HDM_CFLAGS)

HDM_LDFLAGS="-L$HDM_INST_DIR/lib"
AC_SUBST(HDM_LDFLAGS)

HDM_LIBS="-lHDM"
AC_SUBST(HDM_LIBS)


#
# MAKE_SUB_DIRS
#
AC_SUBST(MAKE_SUB_DIRS)
MAKE_SUB_DIRS="src doc"

# K/FX
#if test "$host" != "sparc64-unknown-linux-gnu" ; then
#  MAKE_SUB_DIRS="$MAKE_SUB_DIRS"" tools/frm/src"
#fi




# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_RANLIB


# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([limits.h stdint.h string.h unistd.h])


# Checks for typedefs, structures, and compiler characteristics.
#AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_MODE_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T


# Checks for library functions.
AC_CHECK_FUNCS([memset mkdir sqrt])



AC_CONFIG_FILES([Makefile
                 src/Makefile
                 doc/Makefile
                 hdm-config
                 include/hdmVersion.h])
AC_OUTPUT


chmod +x ./hdm-config
