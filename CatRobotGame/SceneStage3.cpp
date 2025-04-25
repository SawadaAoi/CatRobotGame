/* ========================================
	CatRobotGame/
	------------------------------------
	シーン(ステージ3)用cpp
	------------------------------------
	SceneStage3.cpp
========================================== */

// =============== インクルード ===================
#include "SceneStage3.h"

#include "FileManager.h"
#include "SoundManager.h"
#include "Input.h"


/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化処理
======================================= */
void SceneStage3::InitLocal()
{
	FileManager::StageObjectInput("Assets/Save/Stage/Stage3.stg");

	PLAY_BGM(BGM_KEY::BGM_GAME_1);
	__super::InitLocal();
}
