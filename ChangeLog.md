# HDMlib - Data management library for hierarchical Cartesian data structure


## REVISION HISTORY

---
- 2017-07-07  Version 1.0.3
   - set(CMAKE_FIND_ROOT_PATH /opt/FJSVtclang/1.2.0) in Toolchain_K.cmake


---
- 2017-03-07  Version 1.0.2
  - Rename to case-sensitive filename.
  - Merge pull request #6 from syoyo/case-sensitive

  
---
- 2017-03-07  Version 1.0.1
  - Introduction of real_type
  - Vec3d >> Vec3r
    - src/BCMFileSaver.cpp, BCMFileLoader.cpp
    - include/BCMFileSaver.h, BCMFileLoader.h
  - double >> REAL_TYPE
    - src/BCMFileLoader.cpp, except TextParser args
    - include/BCMFileLoader.h, BCMFileCommon.h
  - float >> REAL_TYPE
    - src/IdxStep.cpp
    - include/IdxStep.h
  - add Vec3.h
    - BCMFileCommon.h, IdxStep.h

---
- 2017-03-07  Version 1.0.0
  - Examples are still working
  - Tested.

|Compiler|MPI |Examples|
|:--|:--:|
|Intel 17.0.1 |ok|0%|
|GNU 6.2.0    |||
|fx10         |||
|K            |||
|fx100        |||


---
- 2015-07-08  Version 0.7.0
  - forget adding BUILD_DIR
  - bug fix at reduceError (snd & rcv buffer were same)
  - introduce BUILD_DIR to keep source directory clean

---
- 2015-06-02
  - fix issues of pull request #4

---
- 2015-05-30  Version 0.6.0
  - Fix output tp file, vector notation in Domain {}
  - update date of copyright
  - rearrange doc/


---
- 2015-03-05
  - Fix build on Intel MPI compilerwith mpiFCCpx


---
- 2015-03-04
  - Fix build on Intel MPI compiler


---
- 2015-02-17
  - Move template code body to header file


---
- 2014-05-15  Version 0.5.1
  - r6 update Vec3class 1.1


---
- 2014-04-02  Version 0.5.0
  - r5 update doc & comment


---
- 2014-03-23  Version 0.4.0
  - r4 update Vec3.h


---
- 2014-03-17  Version 0.3.0
  - r3 common namespace of Vec3class


---
- 2014-03-15  Version 0.2.0
  - r2 class library package


---
- 2014-01-25  Version 0.1.0
  - r1 Check compile and package
  - r0 Initial commit
