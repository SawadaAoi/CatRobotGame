/* ========================================
	CatRobotGame/
	------------------------------------
	シーン(ステージ4)用cpp
	------------------------------------
	SceneStage4.cpp
========================================== */

// =============== インクルード ===================
#include "SceneStage4.h"

#include "FileManager.h"
#include "SoundManager.h"
#include "Input.h"

/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化処理
======================================= */
void SceneStage4::InitLocal()
{
	FileManager::StageObjectInput("Assets/Save/Stage/Stage4.stg");

	PLAY_BGM(BGM_KEY::BGM_GAME_1);
	__super::InitLocal();
}
