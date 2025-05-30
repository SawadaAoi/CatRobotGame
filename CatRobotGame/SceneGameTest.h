/* ========================================
	CatRobotGame/
	------------------------------------
	シーン(テスト)用ヘッダ
	------------------------------------
	説明：テスト用のシーンクラス
	------------------------------------
	SceneGameTest.h
========================================== */
#pragma once

// =============== インクルード ===================
#include "SceneBase.h"

// =============== クラス定義 ===================
class SceneGameTest :
	public SceneBase
{
public:
	void InitLocal() override;
	DEFINE_SCENE_TYPE(SceneGameTest)
};