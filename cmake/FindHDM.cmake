###################################################################################
#
# HDMlib - Data management library for hierarchical Cartesian data structure
#
# Copyright (c) 2014-2017 Advanced Institute for Computational Science (AICS), RIKEN.
# All rights reserved.
#
# Copyright (c) 2017 Research Institute for Information Technology (RIIT), Kyushu University.
# All rights reserved.
#
###################################################################################

# - Try to find HDMlib
# Once done, this will define
#
#  HDM_FOUND - system has HDMlib
#  HDM_INCLUDE_DIRS - HDMlib include directories
#  HDM_LIBRARIES - link these to use HDMlib

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(HDM_PKGCONF HDM)

if(CMAKE_PREFIX_PATH)
  set(HDM_CANDIDATE_PATH ${CMAKE_PREFIX_PATH})
  file(GLOB tmp "${CMAKE_PREFIX_PATH}/[Jj][Hh][Pp][Cc][Nn][Dd][Ff]*/")
  list(APPEND HDM_CANDIDATE_PATH ${tmp})
endif()

# Include dir
find_path(HDM_INCLUDE_DIR
  NAMES HDMTools.h
  PATHS ${HDM_ROOT} ${HDM_PKGCONF_INCLUDE_DIRS} ${HDM_CANDIDATE_PATH}
  PATH_SUFFIXES include
)

# Finally the library itself
find_library(HDM_LIBRARY
  NAMES HDM
  PATHS ${HDM_ROOT} ${HDM_PKGCONF_LIBRARY_DIRS} ${HDM_CANDIDATE_PATH}
  PATH_SUFFIXES lib
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(HDM_PROCESS_INCLUDES HDM_INCLUDE_DIR)
set(HDM_PROCESS_LIBS HDM_LIBRARY)
libfind_process(HDM)
