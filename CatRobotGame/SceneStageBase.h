/* ========================================
	CatRobotGame/
	------------------------------------
	シーン(ステージ基底)用ヘッダ
	------------------------------------
	説明：ステージシーンの基底クラス
	------------------------------------
	SceneStageBase.h
========================================== */
#pragma once

// =============== インクルード ===================
#include "SceneBase.h"


// =============== クラス定義 ===================
class SceneStageBase :
    public SceneBase
{
public:
	SceneStageBase();
	void InitLocal() override;
	void UpdateLocal() override;

	DEFINE_SCENE_TYPE(SceneStageBase)
private:
	void Pause();	// ポーズ処理
	void Resume();	// ポーズ解除処理
private:
	bool m_bPause;	// ポーズフラグ(true:ポーズ中)
};

