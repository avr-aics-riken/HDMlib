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
/// @file  BitVoxel.h
/// @brief ビットボクセル圧縮/展開ライブラリ
///

#ifndef __BCMTOOLS_BITVOXEL_H__
#define __BCMTOOLS_BITVOXEL_H__

#include <cstdlib>


namespace BCMFileIO {

	/// ビットボクセル圧縮/展開ライブラリ
	class BitVoxel {
	public:

		/// ビットボクセル型の定義
		typedef unsigned int bitVoxelCell;

		/// コンストラクタ
		BitVoxel();

		/// デストラクタ
		~BitVoxel();

		/// ボクセルをビットボクセル化した場合のビットボクセルサイズを出力
		///
		/// @param[in]  sourceSize ボクセル数
		/// @param[in]  bitWidth   ビット幅
		/// @return ビットボクセルサイズ
		///
		/// @note ビットボクセルサイズはバイト単位ではない．
		///
		static size_t GetSize(const size_t sourceSize, const unsigned char bitWidth);

		/// ビットボクセル圧縮
		///
		/// @param[out] bitVoxelSize 出力ビットボクセルサイズ
		/// @param[in]  boxelSize    入力ボクセルサイズ
		/// @param[in]  voxel        入力ボクセルの先頭ポインタ
		/// @param[in]  bitWidth     ビット幅
		/// @return ビットボクセルの先頭ポインタ
		///
		/// @note returnされたポインタは適宜解放(delete)してください．
		///
		static bitVoxelCell* Compress( size_t* bitVoxelSize, const size_t voxelSize, const unsigned char* voxel, const unsigned char  bitWidth);

		/// ビットボクセル展開
		///
		/// @param[in] bitVoxelSize ボクセルサイズ (展開後のボクセル数)
		/// @param[in] bitVoxel     入力ビットボクセル
		/// @param[in] bitWidth     ビット幅
		/// @return 展開されたボクセルの先頭ポインタ
		///
		/// @note returnされたポインタは適宜解放(delete)してください．
		///
		static unsigned char* Decompress( const size_t voxelSize, const bitVoxelCell* bitVoxel, const unsigned char  bitWidth);
	};

} // namespace BCMFileIO


#endif // __BCMTOOLS_BITVOXEL_H__
