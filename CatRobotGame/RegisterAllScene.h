/* ========================================
	CatRobotGame/
	------------------------------------
	全シーン登録用ヘッダ
	------------------------------------
	説明：シーンの登録処理をまとめておく
	------------------------------------
	RegisterAllScene.h
========================================== */
#pragma once

// =============== インクルード ===================
#include "SceneManager.h"

#include "SceneGameTest.h"

#include "SceneTitile.h"
#include "SceneStageSelect.h"

#include "SceneStage1.h"
#include "SceneStage2.h"

/* ========================================
	シーン登録関数
	-------------------------------------
	内容：マップにシーンを登録する
=========================================== */
void SceneManager::RegisterAllScene()
{
	REGISTER_SCENE(SceneGameTest);
	REGISTER_SCENE(SceneTitile);
	REGISTER_SCENE(SceneStageSelect);
	REGISTER_SCENE(SceneStage1);
	REGISTER_SCENE(SceneStage2);
}
