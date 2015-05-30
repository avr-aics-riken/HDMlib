/*
 * HDMlib - Hierarchical Data Management library
 *
 * Copyright (c) 2014-2015 Advanced Institute for Computational Science, RIKEN.
 * All rights reserved.
 *
 */

///
/// @file  BCMFileCommon.h
/// @brief BCMファイルIO用共通クラス群
///


#ifndef __BCMTOOLS_IDXBLOCK_H__
#define __BCMTOOLS_IDXBLOCK_H__

#include <vector>
#include <string>

#include "BCMFileCommon.h"
#include "IdxStep.h"

namespace BCMFileIO {

	/// インデックスファイル用ブロック情報クラス
	class IdxBlock
	{
	public:

		/// コンストラクタ
		IdxBlock() :
			rootDir(std::string("")),
			dataDir(std::string("")),
			vc(0),
			isGather(false),
			isStepSubDir(false),
			separateVCUpdate(false)
		{}

		/// データクラスIDからブロック情報を取得するユーティリティ関数
		/// 
		/// @param[in] idxBlockList ブロック情報リスト
		/// @param[in] dataClassID  データクラスID
		/// @return ブロック情報のポインタ
		///
		static inline IdxBlock* find(std::vector<IdxBlock>& idxBlockList, const int dataClassID ){
			for(std::vector<IdxBlock>::iterator it = idxBlockList.begin(); it != idxBlockList.end(); ++it){
				for(size_t i = 0; i < it->dataClassID.size(); i++){
					if( it->dataClassID[i] == dataClassID){
						return &(*it);
					}
				}
			}
			return NULL;
		}

		/// 系の名称からブロック情報を取得するユーティリティ関数
		/// 
		/// @param[in] idxBlockList ブロック情報リスト
		/// @param[in] name         系の名称
		/// @return ブロック情報のポインタ
		///
		static inline IdxBlock* find(std::vector<IdxBlock>& idxBlockList, const std::string& name ){
			for(std::vector<IdxBlock>::iterator it = idxBlockList.begin(); it != idxBlockList.end(); ++it){
				if( it->name == name){
					return &(*it);
				}
			}
			return NULL;
		}

		/// データクラスIDからブロック情報を取得するユーティリティ関数 (const用)
		/// 
		/// @param[in] idxBlockList ブロック情報リスト
		/// @param[in] dataClassID  データクラスID
		/// @return ブロック情報のポインタ
		///
		static inline const IdxBlock* find(const std::vector<IdxBlock>& idxBlockList, const int dataClassID ){
			for(std::vector<IdxBlock>::const_iterator it = idxBlockList.begin(); it != idxBlockList.end(); ++it){
				for(size_t i = 0; i < it->dataClassID.size(); i++){
					if( it->dataClassID[i] == dataClassID){
						return &(*it);
					}
				}
			}
			return NULL;
		}

		/// 系の名称からブロック情報を取得するユーティリティ関数 (const用)
		/// 
		/// @param[in] idxBlockList ブロック情報リスト
		/// @param[in] name         系の名称
		/// @return ブロック情報のポインタ
		///
		static inline const IdxBlock* find(const std::vector<IdxBlock>& idxBlockList, const std::string& name ){
			for(std::vector<IdxBlock>::const_iterator it = idxBlockList.begin(); it != idxBlockList.end(); ++it){
				if( it->name == name){
					return &(*it);
				}
			}
			return NULL;
		}


	public:
		std::string      rootDir;      ///< インデックスファイルのディレクトリ
		std::string      dataDir;      ///< データディレクトリ

		std::vector<int> dataClassID;  ///< データクラスID(マルチコンポーネント対応のため配列)
		LB_DATA_TYPE     dataType;     ///< セルのデータ識別子
		std::string      name;         ///< 系の名称
		LB_KIND          kind;         ///< リーフブロックタイプ
		unsigned int     bitWidth;     ///< セルあたりのビット幅
		unsigned int     vc;           ///< 仮想セルサイズ
		std::string      prefix;       ///< ファイル名Prefix
		std::string      extension;    ///< ファイル拡張子
		bool             isGather;     ///< Gatherフラグ
		bool             isStepSubDir; ///< ステップごとのサブディレクトリフラグ
		IdxStep          step;         ///< タイムステップ情報

		bool         separateVCUpdate;
	};

} // namespace BCMFileIO

#endif // __BCMTOOLS_IDXBLOCK_H__

