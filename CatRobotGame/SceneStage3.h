/* ========================================
	CatRobotGame/
	------------------------------------
	シーン(ステージ3)用ヘッダ
	------------------------------------
	説明：ステージ3のシーンクラス
	------------------------------------
	SceneStage3.h
========================================== */
#pragma once

// =============== インクルード ===================
#include "SceneStageBase.h"

// =============== クラス定義 ===================
class SceneStage3 :
    public SceneStageBase
{
public:
	void InitLocal() override;
	DEFINE_SCENE_TYPE(SceneStage3)
};

