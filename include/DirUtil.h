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
/// @file  DirUtil.h
/// @brief ディレクトリ操作ユーティリティ
///

#ifndef __BCMTOOLS_DIRUTIL_H__
#define __BCMTOOLS_DIRUTIL_H__

#include <vector>
#include <string>

namespace BCMFileIO {

	/// ディレクトリ操作ユーティリティ
	class DirUtil {
	public:

		/// コンストラクタ
		///
		/// @param[in]	ディレクトリ名
		///
		DirUtil(const char* dirname);

		/// ディレクトリ内のファイル数を取得
		///
		/// @return ファイル数
		///
		unsigned int GetFileCount() const;

		/// ディレクトリ内のディレクトリ数を取得
		///
		/// @return ディレクトリ数
		///
		unsigned int GetDirCount() const;

		/// ディレクトリ内の指定インデックスのファイル名を取得
		///
		/// @param[in]	インデックス
		///
		/// @return ファイル名. インデックスがオーバーした場合は nullstringを返却
		///
		const std::string& GetFile(unsigned int i) const;

		/// ディレクトリ内の指定インデックスのディレクトリ名を取得
		///
		/// @param[in]	インデックス
		///
		/// @return ディレクトリ名. インデックスがオーバーした場合は nullstringを返却
		///
		const std::string& GetDir(unsigned int i) const;

		/// 入力ファイル名をフルパスにして返却
		///
		/// @param[in]	ファイル名
		///
		/// @return フルパスのファイル名
		///
		std::string GetFilePath(const char* filename) const;

		/// ディレクトリがオープン中か返却
		///
		/// @return true: オープン中、false: クローズ中
		///
		bool IsOpened() const;

		/// パス名を返却
		///
		/// @return パス名
		///
		const std::string& GetPath() const;

		/// ディレクトリ名を返却
		///
		/// @return ディレクトリ名
		///
		const std::string& GetName() const;

		/// ディレクトリ作成
		///
		/// @param[in]	ディレクトリ名
		///
		/// @return true: 作成成功、もしくは既に同一ディレクトリあり、false: 作成失敗、もしくは既に同一ファイル名あり
		///
		bool CreateDir(const char* dirname);

	private:
		/// 指定ファイルパスから最後の区切り文字位置で分割した文字列を返却
		///
		/// @param[in]	ファイルパス
		/// @param[in]	区切り文字
		///
		/// @return 分割後の文字列
		///
		std::string parseFilename(const char* fpath, const char* splitChar);

	private:
		std::string m_dirname;
		std::string m_dirpath;
		bool m_opened;
		std::vector<std::string> m_files;
		std::vector<std::string> m_dirs;
	};

} // namespace BCMFileIO

#endif // __BCMTOOLS_DIRUTIL_H__
