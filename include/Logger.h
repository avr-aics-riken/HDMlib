/*
 * HDMlib - Hierarchical Data Management library
 *
 * Copyright (c) 2014 Advanced Institute for Computational Science, RIKEN.
 * All rights reserved.
 *
 */

///
/// @file  Logger.h
/// @brief ログ出力ユーティリティ
///

#ifndef __BCMTOOLS_LOGGER_H__
#define __BCMTOOLS_LOGGER_H__

namespace BCMFileIO {

	class Logger {
	private:

		/// ログレベル
		enum LOG_LEVEL
		{
			LOG_ERROR = 0,
			LOG_WARN,
			LOG_INFO,
			LOG_DEBUG
		};
	
	public:
		/// コンストラクタ
		Logger();

		/// デストラクタ
		~Logger();

		/// ログ出力 (エラー)
		///
		/// @param[in] format	ログ出力書式
		/// @param[in] ...		ログ出力文字
		///
		static void Error( const char *format, ...);
	
		/// ログ出力 (警告)
		///
		/// @param[in] format	ログ出力書式
		/// @param[in] ...		ログ出力文字
		///
		static void Warn( const char *format, ...);
	
		/// ログ出力 (情報)
		///
		/// @param[in] format	ログ出力書式
		/// @param[in] ...		ログ出力文字
		///
		static void Info( const char *format, ...);
	
		/// ログ出力 (デバッグ情報)
		///
		/// @param[in] format	ログ出力書式
		/// @param[in] ...		ログ出力文字
		///
		static void Debug( const char *format, ...);

	private:
		/// ログ出力(内部関数)
		///
		/// @param[in] level	ログレベル
		/// @param[in] msg		ログ出力メッセージ
		///
		static void Log( enum LOG_LEVEL level, const std::string& msg );
	};

} // namespace BCMFileIO

#endif // __BCMTOOLS_LOGGER_H__

