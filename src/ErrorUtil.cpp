/*
 * HDMlib - Hierarchical Data Management library
 *
 * Copyright (c) 2014-2015 Advanced Institute for Computational Science, RIKEN.
 * All rights reserved.
 *
 */

///
/// @file  ErrorUtil.cpp
/// @brief エラー処理関連のユーティリティ
///

#include "ErrorUtil.h"

#include <stdio.h>
#include <stdarg.h>
#include <string>

namespace BCMFileIO {

	bool ErrorUtil::reduceError(const bool err, MPI::Intracomm& comm) {
		int ierr_s = err ? 1 : 0;
    int ierr_r = ierr_s;
		comm.Allreduce(&ierr_s, &ierr_r, 1, MPI::INT, MPI::BOR);
		return ierr_r == 0 ? false : true;
	}


} // namespace BCMFileIO
	
