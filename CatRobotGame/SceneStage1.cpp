/* ========================================
	CatRobotGame/
	------------------------------------
	シーン(ステージ1)用cpp
	------------------------------------
	SceneStage1.cpp
========================================== */

// =============== インクルード ===================
#include "SceneStage1.h"

#include "FileManager.h"
#include "SoundManager.h"
#include "Input.h"

/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化処理
======================================= */
void SceneStage1::InitLocal()
{
	FileManager::StageObjectInput("Assets/Save/Stage/Stage1.stg");

	PLAY_BGM(BGM_KEY::BGM_GAME_1);

	__super::InitLocal();
}

