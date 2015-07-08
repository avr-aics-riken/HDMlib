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

lib_LIBRARIES = libHDM.a

libHDM_a_CXXFLAGS = @MPI_CFLAGS@ @TP_CFLAGS@ @BCM_CFLAGS@ -I$(top_srcdir)/include

libHDM_a_SOURCES = \
    BCMFileLoader.cpp \
    BCMFileSaver.cpp \
    BitVoxel.cpp \
    DirUtil.cpp \
    ErrorUtil.cpp \
    IdxStep.cpp \
    LeafBlockLoader.cpp \
    LeafBlockSaver.cpp \
    Logger.cpp

HDM_includedir = $(includedir)
HDM_include_HEADERS = \
    $(top_srcdir)/include/BCMFileCommon.h \
    $(top_srcdir)/include/BCMFileLoader.h \
    $(top_srcdir)/include/BCMFileSaver.h \
    $(top_srcdir)/include/BCMRLE.h \
    $(top_srcdir)/include/BCMTypes.h \
    $(top_srcdir)/include/BitVoxel.h \
    $(top_srcdir)/include/DirUtil.h \
    $(top_srcdir)/include/ErrorUtil.h \
    $(top_srcdir)/include/FileSystemUtil.h \
    $(top_srcdir)/include/hdmVersion.h \
    $(top_srcdir)/include/IdxBlock.h \
    $(top_srcdir)/include/IdxStep.h \
    $(top_srcdir)/include/LeafBlockLoader.h \
    $(top_srcdir)/include/LeafBlockSaver.h \
    $(top_srcdir)/include/Logger.h \
    $(top_srcdir)/include/PartitionMapper.h \
    $(top_srcdir)/include/Vec3.h

HDM_inline_includedir = $(includedir)/inline
HDM_inline_include_HEADERS =
