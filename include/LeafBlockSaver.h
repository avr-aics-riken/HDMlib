/*
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
 */

///
/// @file  LeafBlockSaver.h
/// @brief LeafBlockファイルを出力する関数群
///

#ifndef __BCMTOOLS_LEAFBLOCK_SAVER_H__
#define __BCMTOOLS_LEAFBLOCK_SAVER_H__

#include <mpi.h>

#include "BCMFileCommon.h"
#include "IdxBlock.h"
#include "Vec3.h"

using namespace Vec3class;

class BlockManager;

namespace BCMFileIO {

	class LeafBlockSaver {
	public:

		/// LeafBlockファイル(CellID)の出力
		///
		/// @param[in] comm      MPIコミュニケータ
		/// @param[in] ib        ブロック情報
		/// @param[in] size      リーフブロックサイズ
		/// @param[in] numBlock  総ブロック数
		/// @param[in] datas     CellIDが格納されたデータバッファ
		/// @param[in] rle       RLE圧縮フラグ (trueの場合RLE圧縮を行う)
		///
		/// @return 成功した場合true, 失敗した場合false
		///
		static bool SaveCellID( const MPI::Intracomm& comm,
								const IdxBlock*       ib,
								const Vec3i&          size,
								const size_t          numBlock,
								const unsigned char*  datas,
								bool                  rle);


		/// LeafBlockファイル(物理量)の出力
		///
		/// @param[in] comm         MPIコミュニケータ
		/// @param[in] ib           ブロック情報
		/// @param[in] blockManager ブロックマネージャ
		/// @param[in] step         出力タイムステップのインデックス番号
		///
		/// @return 成功した場合true, 失敗した場合false
		///
		static bool SaveData(const MPI::Intracomm& comm,
							 const IdxBlock*       ib,
							 BlockManager&         blockManager,
							 const unsigned int    step);

	private:
		template<typename T>
		static bool _SaveData(const MPI::Intracomm& comm,
								  const IdxBlock*       ib,
								  BlockManager&         blockManager,
								  const unsigned int    step);

		template<typename T>
		static bool CopyScalar3DToBuffer(BlockManager& blockManager, const int dataClassID, const int dataID, const int vc, T* buf);
	};

} // BCMFileIO

#endif // __BCMTOOLS_LEAFBLOCK_SAVER_H__
