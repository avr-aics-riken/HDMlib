/*
 * HDMlib - Hierarchical Data Management library
 *
 * Copyright (c) 2014 Advanced Institute for Computational Science, RIKEN.
 * All rights reserved.
 *
 */

///
/// @file  IdxStep.h
/// @brief インデックスファイル用タイムステップ情報クラス
///


#ifndef __BCMTOOLS_IDXSTEP_H__
#define __BCMTOOLS_IDXSTEP_H__

//#include <limits.h>
#include <vector>
//#include <string>
#include <list>

#include "BitVoxel.h"

namespace BCMFileIO {

	/// インデックスファイル用タイムステップ情報
	class IdxStep
	{
	public:

		/// コンストラクタ
		IdxStep();
		
		/// コンストラクタ
		///
		/// @param[in] rangeMin      タイムステップレンジの開始インデックス
		/// @param[in] rangeMax      タイムステップレンジの終了インデックス
		/// @param[in] rangeInterval ステップ間隔
		///
		IdxStep(const unsigned int rangeMin, const unsigned int rangeMax, const unsigned int rangeInterval=1);
		
		/// デストラクタ
		~IdxStep();

		/// タイムステップレンジ設定
		///
		/// @param[in] rangeMin      タイムステップレンジの開始インデックス
		/// @param[in] rangeMax      タイムステップレンジの終了インデックス
		/// @param[in] rangeInterval ステップ間隔
		/// @return 成功した場合true, 失敗した場合false
		///
		bool SetRange(const unsigned int rangeMin, const unsigned int rangeMax, const unsigned int rangeInterval=1);

		/// 追加ステップの設定
		/// 
		/// @param[in] step 追加ステップ
		///
		void AddStep(const unsigned int step );

		/// 削除ステップの設定
		///
		/// @param[in] step 削除ステップ
		///
		void SubStep(const unsigned int step );

		/// ステップが設定したリストに含まれるかを判定
		///
		/// @param[in] step 判定するステップ番号
		/// @return stepがリストに含まれる場合true, 含まれない場合false
		///
		bool IsCorrect(const unsigned int step) const;

		/// Step = 0における時刻を設定
		///
		/// @param[in] time Step = 0における時刻
		///
		void SetInitalTime(float time);
		
		/// Step間の時刻幅を設定
		///
		/// @param[in] deltaT Step間の時刻幅
		///
		void SetDeltaT(float deltaT);

		/// 設定したStepのリストを取得
		///
		/// @return ステップのリスト
		/// @note リストはメソッド内で確保するため、リスト取得後、不要になったら解放してください。
		///
		std::list<unsigned int>* GetStepList() const;

		/// ステップの開始インデックスを取得
		///
		/// @return 開始インデックス
		///
		unsigned int GetRangeMin() const;
		
		/// ステップの終了インデックスを取得
		///
		/// @return 終了インデックス
		///
		unsigned int GetRangeMax() const;

		/// ステップ間隔を取得
		///
		/// @return ステップ間隔
		///
		unsigned int GetRangeInterval() const;

		/// 追加ステップリストを取得
		///
		/// @return 追加ステップリスト
		///
		const std::vector<unsigned int>& GetAddStepList() const;
		
		/// 削除ステップリストを取得
		/// 
		/// @return 削除ステップリスト
		///
		const std::vector<unsigned int>& GetSubStepList() const;
		
		/// Step = 0における時刻を取得
		/// 
		/// @return Step = 0における時刻
		///
		float GetInitialTime() const;
		
		/// Step間の時間幅を取得
		///
		/// @return Step間の時間幅
		///
		float GetDeltaT() const;

	private:
		unsigned int m_rangeMin;          ///< タイムステップレンジ (Min)
		unsigned int m_rangeMax;          ///< タイムステップレンジ (Max)
		unsigned int m_rangeInterval;     ///< タイムステップレンジ (Interval)
		std::vector<unsigned int> m_adds; ///< 追加タイムステップリスト
		std::vector<unsigned int> m_subs; ///< 削除タイムステップリスト
		float        m_time;              ///< Step = 0 における時刻
		float        m_deltaT;            ///< Step間の時間幅
	};

} // namespace BCMFileIO

#endif // __BCMTOOLS_IDXSTEP_H__

