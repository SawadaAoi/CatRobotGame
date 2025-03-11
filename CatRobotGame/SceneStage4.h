/* ========================================
	CatRobotGame/
	------------------------------------
	シーン(ステージ4)用ヘッダ
	------------------------------------
	説明：ステージ4のシーンクラス
	------------------------------------
	SceneStage4.h
========================================== */
#pragma once

// =============== インクルード ===================
#include "SceneStageBase.h"

// =============== クラス定義 ===================
class SceneStage4 :
    public SceneStageBase
{
public:
	void InitLocal() override;
	DEFINE_SCENE_TYPE(SceneStage4)
};

