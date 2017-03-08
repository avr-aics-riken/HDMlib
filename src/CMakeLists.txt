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


include_directories(
       ${PROJECT_BINARY_DIR}/include       # hdmVersion.h
       ${PROJECT_SOURCE_DIR}/include
       ${TP_INC}
       ${BCM_INC}
)


link_directories(
      ${TP_LIB}
      ${BCM_LIB}
)


set(hdm_files
    BCMFileLoader.cpp
    BCMFileSaver.cpp
    BitVoxel.cpp
    DirUtil.cpp
    ErrorUtil.cpp
    IdxStep.cpp
    LeafBlockLoader.cpp
    LeafBlockSaver.cpp
    Logger.cpp
)


if(with_MPI)
  add_library(HDMmpi STATIC ${hdm_files})
  target_link_libraries(HDMmpi -lBCMmpi -lTPmpi)
  install(TARGETS HDMmpi DESTINATION lib)
else()
  add_library(HDM STATIC ${hdm_files})
  target_link_libraries(HDM -lBCM -lTP)
  install(TARGETS HDM DESTINATION lib)
endif()


install(FILES
        ${PROJECT_SOURCE_DIR}/include/BCMFileCommon.h
        ${PROJECT_SOURCE_DIR}/include/BCMFileLoader.h
        ${PROJECT_SOURCE_DIR}/include/BCMFileSaver.h
        ${PROJECT_SOURCE_DIR}/include/BCMRLE.h
        ${PROJECT_SOURCE_DIR}/include/BCMTypes.h
        ${PROJECT_SOURCE_DIR}/include/BitVoxel.h
        ${PROJECT_SOURCE_DIR}/include/DirUtil.h
        ${PROJECT_SOURCE_DIR}/include/ErrorUtil.h
        ${PROJECT_SOURCE_DIR}/include/FileSystemUtil.h
        ${PROJECT_SOURCE_DIR}/include/hdmVersion.h.in
        ${PROJECT_SOURCE_DIR}/include/IdxBlock.h
        ${PROJECT_SOURCE_DIR}/include/IdxStep.h
        ${PROJECT_SOURCE_DIR}/include/LeafBlockLoader.h
        ${PROJECT_SOURCE_DIR}/include/LeafBlockSaver.h
        ${PROJECT_SOURCE_DIR}/include/Logger.h
        ${PROJECT_SOURCE_DIR}/include/PartitionMapper.h
        ${PROJECT_SOURCE_DIR}/include/Vec3.h
        ${PROJECT_BINARY_DIR}/include/hdmVersion.h
        DESTINATION include
)
