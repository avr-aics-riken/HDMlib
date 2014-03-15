/*
 * HDMlib - Hierarchical Data Management library
 *
 * Copyright (c) 2014 Advanced Institute for Computational Science, RIKEN.
 * All rights reserved.
 *
 */

///
/// @file  IdxStep.cpp
/// @brief インデックスファイル用タイムステップ情報クラス
///

#include "IdxStep.h"

namespace BCMFileIO {

	// #############################################################
	// コンストラクタ
	IdxStep::IdxStep() : m_rangeMin(0), m_rangeMax(0), m_rangeInterval(0), m_time(.0f), m_deltaT(.1f)
	{
	}

	// #############################################################
	// コンストラクタ
	IdxStep::IdxStep(const unsigned int rangeMin, const unsigned int rangeMax, const unsigned int rangeInterval)
		: m_rangeMin(0), m_rangeMax(0), m_rangeInterval(0), m_time(.0f), m_deltaT(.1f)
	{
		SetRange(rangeMin, rangeMax, rangeInterval);
	}

	// #############################################################
	// デストラクタ
	IdxStep::~IdxStep()
	{
	}

	// #############################################################
	// タイムステップレンジ設定
	bool IdxStep::SetRange(const unsigned int rangeMin, const unsigned int rangeMax, const unsigned int rangeInterval)
	{
		if(rangeMax <= rangeMin){ return false; }
		m_rangeMin      = rangeMin;
		m_rangeMax      = rangeMax;
		m_rangeInterval = rangeInterval;

		return true;
	}

	// #############################################################
	// 追加ステップの設定
	void IdxStep::AddStep(const unsigned int step )
	{
		m_adds.push_back(step);
	}

	// #############################################################
	// 削除ステップの設定
	void IdxStep::SubStep(const unsigned int step )
	{
		m_subs.push_back(step);
	}

	// #############################################################
	// ステップが設定したリストに含まれるかを判定
	bool IdxStep::IsCorrect(const unsigned int step) const
	{
		for(std::vector<unsigned int>::const_iterator it = m_adds.begin(); it != m_adds.end(); ++it){
			if( *it == step ){ return true; }
		}
		for(std::vector<unsigned int>::const_iterator it = m_subs.begin(); it != m_subs.end(); ++it){
			if( *it == step ){ return false; }
		}

		if( m_rangeMin <= step && m_rangeMax >= step ){
			if( ((step - m_rangeMin) % m_rangeInterval) == 0 ){
				return true;
			}else{
				return false;
			}
		}
		return false;
	}

	// #############################################################
	// Step = 0における時刻を設定
	void IdxStep::SetInitalTime(float time)
	{
		m_time   = time;
	}
		
	// #############################################################
	// Step間の時刻幅を設定
	void IdxStep::SetDeltaT(float deltaT)
	{
		m_deltaT = deltaT;
	}

	// #############################################################
	// 設定したStepのリストを取得
	std::list<unsigned int>* IdxStep::GetStepList() const
	{
		if( m_rangeInterval == 0 ){ return NULL; }

		std::list<unsigned int>*steps = new std::list<unsigned int>;

		for(unsigned int i = m_rangeMin; i <= m_rangeMax; i+= m_rangeInterval){
			steps->push_back(i);
		}
			
		// 追加リストからのステップ追加
		for(std::vector<unsigned int>::const_iterator it = m_adds.begin(); it != m_adds.end(); ++it){
			steps->push_back((*it));
		}

		// 削除リストからステップ削除
		for(std::vector<unsigned int>::const_iterator it = m_subs.begin(); it != m_subs.end(); ++it){
			steps->remove((*it));
		}
			
		steps->sort();

		return steps;
	}
		
	// #############################################################
	// ステップの開始インデックスを取得
	unsigned int IdxStep::GetRangeMin() const
	{
		return m_rangeMin;
	}

	// #############################################################
	// ステップの終了インデックスを取得
	unsigned int IdxStep::GetRangeMax() const
	{
		return m_rangeMax;
	}

	// #############################################################
	// ステップ間隔を取得
	unsigned int IdxStep::GetRangeInterval() const
	{
		return m_rangeInterval;
	}

	// #############################################################
	// 追加ステップリストを取得
	const std::vector<unsigned int>& IdxStep::GetAddStepList() const
	{
		return m_adds;
	}

	// #############################################################
	// 削除ステップリストを取得
	const std::vector<unsigned int>& IdxStep::GetSubStepList() const
	{
		return m_subs;
	}

	// #############################################################
	// Step = 0における時刻を取得
	float IdxStep::GetInitialTime() const
	{
		return m_time;
	}
		
	// #############################################################
	// Step間の時間幅を取得
	float IdxStep::GetDeltaT() const
	{
		return m_deltaT;
	}

} // namespace BCMFileIO
