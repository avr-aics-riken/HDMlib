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

SUBDIRS = @MAKE_SUB_DIRS@

bin_SCRIPTS = hdm-config
CLEANFILES = $(bin_SCRIPTS)
EXTRA_DIST = hdm-config.in LICENSE examples doc README.md
dist_data_DATA = AUTHORS COPYING ChangeLog README LICENSE
dist_include_HEADERS = include/mpi_stubs.h

clean-local:
	find ./ -name *.obj | xargs rm -f
	find ./ -name *.exe | xargs rm -f
	find ./ -name *.lib | xargs rm -f

distclean-local: clean-local
	rm -f ./bin/*
	rm -f ./lib/*
