/*
 * HDMlib - Hierarchical Data Management library
 *
 * Copyright (c) 2014 Advanced Institute for Computational Science, RIKEN.
 * All rights reserved.
 *
 */

///
/// @file FileSystemUtil.h
/// @brief ファイル操作関連ユーティリティ
///

#ifndef __BCMTOOLS_FILESYSTEM_UTIL_H__
#define __BCMTOOLS_FILESYSTEM_UTIL_H__

#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h> 
#include <unistd.h> 
#include <dirent.h>

#include <string>
#include <vector>

#include "DirUtil.h"
#include "Logger.h"

namespace BCMFileIO {

	class FileSystemUtil {
	public:

		/// ファイルパスの "\\" を "/" に変換
		///
		/// @param[in]	path	ファイルパス
		/// @return "/"に変換されたファイルパス
		///
		static inline std::string ConvertPath(const std::string& path)
		{
			std::string r = path;
			size_t p = r.find("\\");
			while (p != std::string::npos)
			{
				*(r.begin() + p) = '/';
				p = r.find("\\");
			}
			return r;
		}

		/// pathからディレクトリ名を抜き出す
		///
		/// @param[in]	path	ファイルパス
		/// @return ディレクトリ名 (最後の"/"は残す)
		///
		static inline std::string GetDirectory(const std::string& path)
		{
			std::string cpath = ConvertPath(path);

			std::string dir;
			size_t p = cpath.rfind("/");
			if(p != std::string::npos)
			{
				dir = cpath.substr(0, p+1);
			}else{
				dir = std::string("./");
			}
			return dir;
		}

		/// pathから拡張子以前のファイル名を抜き出す
		///
		/// @param[in]	path	ファイルパス
		/// @return 拡張子以前のファイル名
		///
		static inline std::string GetFilePrefix(const std::string& path)
		{
			std::string cpath = ConvertPath(path);
			std::string filename = cpath.substr(cpath.rfind("/")+1);
			
			return filename.substr(0, filename.rfind("."));
		}

		/// dirをディレクトリ名として整形. 空の場合は"./"、文字列が入っている場合最後に "/"を追加
		///
		/// @param[in]	dir		ディレクトリ名
		/// @return 整形後のディレクトリ名
		///
		static inline std::string FixDirectoryPath(const std::string& dir)
		{
			if( dir == std::string("") ){
				return std::string("./");
			}else if( dir.rfind("/") != dir.length()-1 ){
				return dir + std::string("/");
			}else{
				return dir;
			}
		}

		/// pathで指定したディレクトリを作成 (mkdir -p 相当)
		///
		/// @param[in]	path			ディレクトリ名
		/// @param[in]	absolutePath	true: ルートディレクトリ (/) から作成、false: 相対パスとして作成
		/// @return true: 作成成功、false: 作成失敗
		///
		static bool CreateDirectory(const std::string& path, bool absolutePath = false)
		{
			
			std::vector<std::string> dirList;
			split(path, '/', dirList);
			
			std::string npath;
			if( absolutePath ){
				npath = std::string("/");
			}else{
				npath = std::string("./");
			}
		
			for(std::vector<std::string>::iterator it = dirList.begin(); it != dirList.end(); ++it){
				DirUtil dir(npath.c_str());
				
				if( *it == std::string(".")  ){ continue; }
				if( *it == std::string("..") ){ npath += *it + std::string("/"); continue; }
		
				if( !dir.CreateDir(it->c_str()) ){ 
					Logger::Error("cannnot create directory : %s\n", (npath + *it).c_str());
					return false;
				}
				
				npath += *it + std::string("/");
			}
		
			return true;
		}

		/// 文字列を指定の区切り文字で分割
		///
		/// @param[in]	input		入力文字列
		/// @param[in]	delimiter	区切り文字
		/// @param[out]	output		分割された文字列リスト
		/// @return true: 分割成功のみ返却
		///
		static bool split(const std::string& input, const char delimiter, std::vector<std::string>& output)
		{
			output.clear();
			
			std::string istr = input;
			
			size_t p = 0;
			while( (p = istr.find(delimiter)) != std::string::npos ){
				if(p != 0){
					output.push_back( istr.substr(0, p) );
				}
				istr.erase(istr.begin(), istr.begin() + p + 1);
			}
		
			if( istr.length() != 0 ) output.push_back(istr);
		
			return true;
		}
	};

} // namespace BCMFileIO

#endif // __BCMTOOLS_FILESYSTEM_UTIL_H__
