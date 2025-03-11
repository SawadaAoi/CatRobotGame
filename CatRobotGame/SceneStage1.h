/* ========================================
	CatRobotGame/
	------------------------------------
	シーン(ステージ1)用ヘッダ
	------------------------------------
	説明：ステージ1のシーンクラス
	------------------------------------
	SceneStage1.h
========================================== */
#pragma once

// =============== インクルード ===================
#include "SceneStageBase.h"

// =============== クラス定義 ===================
class SceneStage1 :
    public SceneStageBase
{
public:
	void InitLocal() override;

	DEFINE_SCENE_TYPE(SceneStage1)
};

