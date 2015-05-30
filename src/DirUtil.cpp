/*
 * HDMlib - Hierarchical Data Management library
 *
 * Copyright (c) 2014-2015 Advanced Institute for Computational Science, RIKEN.
 * All rights reserved.
 *
 */

#include "ErrorUtil.h"
#include "FileSystemUtil.h"
#include "DirUtil.h"

#include <vector>
#include <string>
#include <cstring>

#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h> 
#include <unistd.h> 
#include <dirent.h>


namespace BCMFileIO {

	/// コンストラクタ
	DirUtil::DirUtil(const char* dirname)
	{
		m_opened = false;
		m_dirpath = std::string(dirname);
		
		m_dirname = parseFilename(dirname,  "/");
		DIR* pDir = opendir(dirname);	
		if (!pDir)
			return;
		
		dirent* pEnt = readdir(pDir);
	    while (pEnt)
		{
	        if ( strcmp( pEnt->d_name, "." ) &&
	             strcmp( pEnt->d_name, ".." ) )
			{
				std::string wPathName = std::string(dirname) + std::string("/") + std::string(pEnt->d_name);
				struct stat wStat;
	            if ( stat( wPathName.c_str(), &wStat ) )
	                break;
	            
	            if ( S_ISDIR( wStat.st_mode ) )
					m_dirs.push_back(pEnt->d_name);
	            else
	                m_files.push_back(pEnt->d_name);
	        }
			pEnt = readdir(pDir);
	    }
		closedir(pDir);
		m_opened = true;
	}
		
	/// ディレクトリがオープン中か返却
	bool DirUtil::IsOpened() const
	{
		return m_opened;
	}
		
	/// ディレクトリ内のファイル数を取得
	unsigned int DirUtil::GetFileCount() const
	{
		return static_cast<unsigned int>(m_files.size());
	}

	/// ディレクトリ内のディレクトリ数を取得
	unsigned int DirUtil::GetDirCount() const
	{
		return static_cast<unsigned int>(m_dirs.size());
	}

	/// ディレクトリ内の指定インデックスのファイル名を取得
	const std::string& DirUtil::GetFile(unsigned int i) const
	{
		static std::string nullstring;
		if (i >= m_files.size())
			return nullstring;
		
		return m_files[i];
	}

	/// ディレクトリ内の指定インデックスのディレクトリ名を取得
	const std::string& DirUtil::GetDir(unsigned int i) const
	{
		static std::string nullstring;
		if (i >= m_dirs.size())
			return nullstring;
		
		return m_dirs[i];
	}

	/// 入力ファイル名をフルパスにして返却
	std::string DirUtil::GetFilePath(const char* filename) const
	{
		return m_dirpath + "/" + filename;
	}

	/// パス名を返却
	const std::string& DirUtil::GetPath() const
	{
		return m_dirpath;
	}

	/// ディレクトリ名を返却
	const std::string& DirUtil::GetName() const
	{
		return m_dirname;
	}

	/// ディレクトリ作成
	bool DirUtil::CreateDir(const char* dirname)
	{
		std::string dirpath = GetFilePath(dirname);
		std::vector<std::string>::iterator it = std::find(m_files.begin(), m_files.end(), dirname);
		if (it != m_files.end())
			return false;
		it = std::find(m_dirs.begin(), m_dirs.end(), dirname);
		if (it != m_dirs.end())
			return true;
		
		const mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
		if ( mkdir(dirpath.c_str(), mode) != 0 )
		{
			usleep(10000);
			DirUtil check(dirpath.c_str());
			return check.IsOpened();
		}
	
		return true;
	}

	/// 指定ファイルパスから最後の区切り文字位置で分割した文字列を返却
	std::string DirUtil::parseFilename(const char* fpath, const char* splitChar)
	{
		std::string f(fpath);
		size_t p = f.rfind(splitChar);
		if (p != std::string::npos)
			f.erase(f.begin(), f.begin() + p + 1);
		return f;
	}

} // namespace BCMFileIO
