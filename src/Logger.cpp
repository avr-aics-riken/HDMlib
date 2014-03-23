/*
 * HDMlib - Hierarchical Data Management library
 *
 * Copyright (c) 2014 Advanced Institute for Computational Science, RIKEN.
 * All rights reserved.
 *
 */

///
/// @file  Logger.cpp
/// @brief ログ出力ユーティリティ
///

#include <stdio.h>
#include <stdarg.h>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

#include <mpi.h>

#include "Logger.h"

namespace BCMFileIO {

	Logger::Logger()
	{
	}

	Logger::~Logger()
	{
	}

	void Logger::Log( enum LOG_LEVEL level, const std::string& msg )
	{
		static const char *log_header[4] = {
			"[ERR]", "[WRN]", "[INF]", "[DBG]"
		};
	
		MPI::Intracomm& comm = MPI::COMM_WORLD;
		char rankstr[128];
		sprintf(rankstr, "[RANK:%6d]", comm.Get_rank());
		
		std::string logstr(rankstr);
		logstr += std::string(" ") + std::string(log_header[level]) + std::string(" ") + msg;
	
	#ifdef _WIN32
		OutputDebugStringA(logstr.c_str());
	#else
		printf("%s", logstr.c_str());	
	#endif
	}
	
	void Logger::Error(const char *format, ...)
	{
		char buf[256];
		va_list arg;
		va_start(arg, format);
		vsprintf(buf, format, arg);
		va_end(arg);
		
		Log(LOG_ERROR, buf);
	}
	
	void Logger::Warn(const char *format, ...)
	{
		char buf[256];
		va_list arg;
		va_start(arg, format);
		vsprintf(buf, format, arg);
		va_end(arg);
		
		Log(LOG_WARN, buf);
	}
	
	void Logger::Info(const char *format, ...)
	{
		char buf[256];
		va_list arg;
		va_start(arg, format);
		vsprintf(buf, format, arg);
		va_end(arg);
		
		Log(LOG_INFO, buf);
	}
	
	void Logger::Debug(const char *format, ...)
	{
		char buf[256];
		va_list arg;
		va_start(arg, format);
		vsprintf(buf, format, arg);
		va_end(arg);
		
		Log(LOG_DEBUG, buf);
	}


} // namespace BCMFileIO
	
