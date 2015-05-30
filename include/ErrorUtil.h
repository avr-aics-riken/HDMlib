/*
 * HDMlib - Hierarchical Data Management library
 *
 * Copyright (c) 2014-2015 Advanced Institute for Computational Science, RIKEN.
 * All rights reserved.
 *
 */

///
/// @file  ErrorUtil.h
/// @brief エラー処理関連のユーティリティ
///

#ifndef __BCMTOOLS_ERROR_UTIL_H__
#define __BCMTOOLS_ERROR_UTIL_H__

#include <mpi.h>

namespace BCMFileIO {

	/// エラー処理関連のユーティリティ
	class ErrorUtil {
	public:

		/// 全プロセスに対しエラー情報を配信
		/// 
		/// @param[in] err  エラーがある場合trueを入力
		/// @param[in] comm MPIコミュニケータ
		/// @return 1プロセスでもエラーがある場合trueを返す．全プロセスでエラーが無い場合false
		/// 
		static bool reduceError( const bool err, MPI::Intracomm& comm = MPI::COMM_WORLD );
	};
	
} // namespace BCMFileIO

#endif // __BCMTOOLS_ERROR_UTIL_H__

