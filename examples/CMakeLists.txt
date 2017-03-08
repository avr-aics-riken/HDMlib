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
      ${PROJECT_BINARY_DIR}/include
      ${PROJECT_SOURCE_DIR}/include
      ${TP_INC}
      ${BCM_INC}
      ${PL_INC}
)

link_directories(
      ${PROJECT_BINARY_DIR}/src
      ${BCM_LIB}
      ${PL_LIB}
      ${TP_LIB}
)



#### Sample1 : Creator

add_executable(creator
               SampleCreator/BCMPolylib.cpp
               SampleCreator/main.cpp
)

if(with_MPI)
  target_link_libraries(creator -lHDMmpi -lBCMmpi -lPOLYmpi -lTPmpi)
  set (test_parameters -np 2
                      "creator"
                      "${PROJECT_SOURCE_DIR}/examples/SampleCreator/test.conf"
  )
  add_test(NAME TEST_1 COMMAND "mpirun" ${test_parameters}
  )
else()
  target_link_libraries(crator -lHDM -lBCM -lPOLY -lTP)
endif()



### Sample2 : Loader

add_executable(loader SampleLoader/main.cpp)

if(with_MPI)
  target_link_libraries(loader -lHDMmpi -lBCMmpi -lPOLYmpi -lTPmpi)
  set (test_parameters -np 2
                      "loader"
                      "data.bcm"
  )
  add_test(NAME TEST_2 COMMAND "mpirun" ${test_parameters}
  )
else()
  target_link_libraries(loader -lHDM -lBCM -lPOLY -lTP)
endif()
