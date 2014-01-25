###
#########################################################################
#
# HDMlib - Hierarchical Data Management library
#
# Copyright (c) 2014 Advanced Institute for Computational Science, RIKEN.
# All rights reserved.
#
#########################################################################
###

lib_LIBRARIES = libHDM.a

libHDM_a_CXXFLAGS = @MPI_CFLAGS@ @TP_CFLAGS@ @BCM_CFLAGS@ -I$(top_builddir)/include

libHDM_a_SOURCES = \
    BCMFileLoader.cpp \
    BCMFileSaver.cpp \
    BitVoxel.cpp \
    ErrorUtil.cpp \
    FileSystemUtil.cpp \
    LeafBlockLoader.cpp \
    LeafBlockSaver.cpp

HDM_includedir = $(includedir)
HDM_include_HEADERS = \
    $(top_builddir)/include/BCMFileCommon.h \
    $(top_builddir)/include/BCMFileLoader.h \
    $(top_builddir)/include/BCMFileSaver.h \
    $(top_builddir)/include/BitVoxel.h \
    $(top_builddir)/include/ErrorUtil.h \
    $(top_builddir)/include/FileSystemUtil.h \
    $(top_builddir)/include/LeafBlockLoader.h \
    $(top_builddir)/include/LeafBlockSaver.h \
    $(top_builddir)/include/PartitionMapper.h \
    $(top_builddir)/include/RLE.h \
    $(top_builddir)/include/type.h

HDM_inline_includedir = $(includedir)/inline
HDM_inline_include_HEADERS =


