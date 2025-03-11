/* ========================================
	CatRobotGame/
	------------------------------------
	シーン(ステージ2)用ヘッダ
	------------------------------------
	説明：ステージ２のシーンクラス
	------------------------------------
	SceneStage2.h
========================================== */
#pragma once

// =============== インクルード ===================
#include "SceneStageBase.h"

// =============== クラス定義 ===================
class SceneStage2 :
    public SceneStageBase
{
public:
	void InitLocal() override;
	DEFINE_SCENE_TYPE(SceneStage2)
};

