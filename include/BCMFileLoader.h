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
/// @file  BCMFileLoader.h
/// @brief BCMファイルを読み込むクラス
///

#ifndef __BCMTOOLS_BCM_FILE_LOADER_H__
#define __BCMTOOLS_BCM_FILE_LOADER_H__

#include <mpi.h>

#include <string>
#include <vector>

#include "Vec3.h"

#include "BCMFileCommon.h"
#include "IdxBlock.h"
#include "IdxStep.h"
#include "Pedigree.h"

using namespace Vec3class;

class BlockManager;
class BCMOctree;
class BoundaryConditionSetterBase;

class TextParser;

namespace BCMFileIO {

	class PartitionMapper;

	/// BCMファイルを読み込むクラス
	class BCMFileLoader
	{
	public:

		/// コンストラクタ
		///
		/// @param[in] idxFilepath 入力インデックスファイル名 (実行ディレクトリからの相対パス)
		/// @param[in] bcsetter    境界条件設定クラス
		///
		BCMFileLoader(const std::string& idxFilename, BoundaryConditionSetterBase* bcsetter);

		/// デストラクタ
		///
		/// @note ファイルから読み込んだOctreeはデストラクタで解放される．
		~BCMFileLoader();

		/// 追加のインデックスファイルを読み込む
		///
		/// @param[in] filepath インデックスファイルのファイル名 (実行ディレクトリからの相対パス)
		/// @return 成功した場合true, 失敗した場合false
		///
		/// @note cellid.bcmとdata.bcmの2種類を読み込む場合に使用する。
		///       読み込む順番は不問。
		///       コンストラクタで読み込んだインデックスファイルとここで読み込むインデックスファイルの内容に相違がある場合、falseを返す
		///       内容の相違は、proc.bcmとtree.octのヘッダ情報で判定
		///
		bool LoadAdditionalIndex(const std::string& filepath);

		/// ブロックを生成
		///
		/// @param[out] dataClassID       生成したブロックのデータクラスID (配列の先頭アドレス)
		/// @param[in]  name              系の名称
		/// @param[in]  vc                仮想セルサイズ
		/// @param[in]  separateVCUpdate  仮想セルの同期方法フラグ．trueの場合、3軸方向別々に同期を行う
		/// @return 成功した場合true, 失敗した場合false
		///
		/// @note nameに対応するブロックがすでに生成されている場合、新しいブロックは生成せず、対応するデータクラスIDを返す
		///       nameに対応するデータが複数コンポーネント(Vertor/Tensor)の場合、dataClassIDの
		///
		///       separateVCUpdateは，読み込むデータクラスに対する初回呼び出しのみ有効
		///
		bool CreateLeafBlock(int *dataClassID, const std::string& name, const unsigned int vc, const bool separateVCUpdate = false);

		/// タイムステップ(step)におけるリーフブロックをファイルから読み込む．
		///
		/// @param[out] dataClassID       生成したブロックのデータクラスID (配列の先頭アドレス)
		/// @param[in]  name              系の名称
		/// @param[in]  vc                仮想セルサイズ
		/// @param[in]  step              読み込むタイムステップ
		/// @param[in]  separateVCUpdate  仮想セルの同期方法フラグ．trueの場合、3軸方向別々に同期を行う
		/// @return 成功した場合true, 失敗した場合false
		///
		/// @note dataClassIDの対象がGridの場合、stepは無視される．
		///       nameに対応するブロックが生成されていない場合、ブロックを生成．
		///       separateVCUpdateは，読み込むデータクラスに対する初回呼び出しのみ有効
		///       LoadLeafBlock()の前にCreateLeafBlock()で空のリーフブロックを作成していた場合，
		///       CreateLeafBlock()時に指定したseparateVCUpdateが有効になる．
		///
		bool LoadLeafBlock(int *dataClassID, const std::string& name, const unsigned int vc,
		                   const unsigned int step = 0, const bool separateVCUpdate = false);

		/// 読み込んだOctreeを返す．
		/// @return Octreeのポインタ
		///
		BCMOctree* GetOctree(){ return m_octree; }

		/// 領域全体の原点座標を返す．
		///
		/// @return 原点座標
		///
		Vec3r GetGlobalOrigin() const { return m_globalOrigin; }

		/// 領域全体の長さを返す．
		///
		/// @return 領域の長さ
		///
		Vec3r GetGlobalRegion() const { return m_globalRegion; }

		/// タイムステップ情報を取得
		///
		/// @param[in] name 系の名称
		/// @return nameに対応したタイムステップのポインタ。系が存在しない場合NULL
		///
		const IdxStep* GetStep(const std::string& name) const;

		/// 単位系を取得
		///
		/// @return 単位系
		///
		const IdxUnit& GetUnit() const { return m_unit; }

	private:

		/// Octreeファイルを読み込む
		///
		/// @param[in] filename Octreeファイルのファイル名
		/// @param[in] bcsetter 境界条件設定クラス
		/// @return 成功した場合true, 失敗した場合false
		///
		bool LoadOctree(const std::string& filename, BoundaryConditionSetterBase* bcsetter);

		/// Indexファイルを読み込む
		///
		/// @param[in]  filename インデックスファイル (cellid.bcm / data.bcm)の相対パス
		/// @param[out] globalOrigin    計算空間全体の起点座標
		/// @param[out] globalRegion    計算空間全体の領域サイズ
		/// @param[out] octreeFilename  Octreeファイルのファイル名
		/// @param[out] blockSize       ブロックサイズ
		/// @param[out] idxProcList     プロセス情報リスト
		/// @param[out] idxBlockList    ブロック情報リスト
		/// @return 成功した場合true, 失敗した場合false
		///
		bool LoadIndex(const std::string& filename,
		               Vec3r& globalOrigin, Vec3r& globalRegion,
					   std::string& octreeFilename, Vec3i& blockSize,
					   std::vector<IdxProc>& idxProcList, std::vector<IdxBlock>& idxBlockList);

		/// Indexファイルのステップ情報を読み込む
		///
		/// @param[in]  tp TextParser
		/// @param[out] step 読み込んだステップ情報
		/// @return 成功した場合true, 失敗した場合false
		///
		bool LoadIndexStep(TextParser *tp,   IdxStep* step);

		/// Indexファイルのリーフブロック情報を読み込む (data.bcm用)
		///
		/// @param[in]  tp TextParser
		/// @param[out] ib 読み込んだブロック情報
		/// @return 成功した場合true, 失敗した場合false
		///
		bool LoadIndexData(TextParser *tp,   IdxBlock* ib);

		/// Indexファイルのリーフブロック情報を読み込む (cellId.bcm用)
		///
		/// @param[in]  tp TextParser
		/// @param[out] ib 読み込んだブロック情報
		/// @return 成功した場合true, 失敗した場合false
		///
		bool LoadIndexCellID(TextParser *tp, IdxBlock* ib);

		/// Indexファイルのプロセス情報を読み込む
		///
		/// @param[in]  filename プロセス情報ファイルのパス (proc.bcm)
		/// @param[out] procList プロセス情報リスト
		/// @return 成功した場合true, 失敗した場合false
		///
		bool LoadIndexProc(const std::string& filename, std::vector<IdxProc>& procList);

		/// 読み込んだインデックスファイルの内容をstdoutに出力
		void PrintIdxInformation();

		/// 読み込んだOctreeファイルの内容をstdoutに出力
		void PrintOctreeInformation();

		/// ユニークなタグを取得
		int GetUniqueTag();

		/// 2つの文字列を比較
		/// @param[in]  str1       文字列1
		/// @param[in]  str2       文字列2
		/// @param[in]  ignorecase true: 大文字、小文字を区別せず比較、false: 大文字、小文字を区別して比較
		/// @return 負: str1 < str2、ゼロ: str1 == str2、正: str1 > str2
		inline int CompStr( const std::string& str1, const std::string& str2, bool ignorecase=true );

		/// Vec3r型のデータ読み込み
		/// @param[in]  tp		テキストパーサ
		/// @param[in]  label   ラベル
		/// @param[out] v		Vec3r
		/// @return == TP_NO_ERROR: 正常終了、!= TP_NO_ERROR: エラー終了
		int ReadVec3( TextParser* tp, const std::string& label, Vec3r& v);

		/// Vec3i型のデータ読み込み
		/// @param[in]  tp		テキストパーサ
		/// @param[in]  label   ラベル
		/// @param[out] v		Vec3i
		/// @return == TP_NO_ERROR: 正常終了、!= TP_NO_ERROR: エラー終了
		int ReadVec3( TextParser* tp, const std::string& label, Vec3i& v);

		/// LB_DATA_TYPEのデータタイプ取得
		/// @param[in]  typeStr	データタイプ
		/// @param[out]	retType	LB_DATA_TYPEデータタイプ
		/// @return true: 正常終了、false: 該当データタイプなし
		bool GetType(const std::string& typeStr, LB_DATA_TYPE &retType);

		/// Octreeヘッダの取得
		/// @param[in] 	fp			ファイルポインタ
		/// @param[out]	header		OctTreeファイルヘッダ
		/// @param[out]	isNeedSwap	true: BSwap必要、false: BSwap不要
		/// @return true: 正常終了、false: 読み込みエラー
		bool LoadOctreeHeader(FILE *fp, OctHeader& header, bool& isNeedSwap);

		/// Octreeファイルより Pedigreeリストを取得する
		/// @param[in] 	filename	ファイル名
		/// @param[out]	header		OctTreeファイルヘッダ
		/// @param[out]	pedigrees	Pedigreeリスト
		/// @return true: 正常終了、false: ファイル読み込みエラー
		bool LoadOctreeFile(const std::string& filename, OctHeader& header, std::vector<Pedigree>& pedigrees);


	private:
		BlockManager& m_blockManager;          ///< ブロックマネージャ
		const MPI::Intracomm& m_comm;          ///< MPIコミュニケータ

		Vec3i                 m_leafBlockSize; ///< リーフブロックサイズ
		std::vector<IdxProc>  m_idxProcList;   ///< プロセス情報リスト
		std::vector<IdxBlock> m_idxBlockList;  ///< ブロック情報リスト
		IdxUnit               m_unit;          ///< 単位系

		Vec3r m_globalOrigin;                  ///< 領域全体の原点座標
		Vec3r m_globalRegion;                  ///< 領域全体の長さ

		BCMOctree *m_octree;                   ///< Octree

		PartitionMapper* m_pmapper;            ///< MxNデータマッパ
	};

} // namespace BCMFileIO


#endif // __BCMTOOLS_BCM_FILE_LOADER_H__
