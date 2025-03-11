/* ========================================
	CatRobotGame/
	------------------------------------
	シーン(ステージ2)用cpp
	------------------------------------
	SceneStage2.cpp
========================================== */

// =============== インクルード ===================
#include "SceneStage2.h"

#include "FileManager.h"
#include "SoundManager.h"
#include "Input.h"



/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化処理
======================================= */
void SceneStage2::InitLocal()
{
	FileManager::StageObjectInput("Assets/Save/Stage/Stage2.stg");

	__super::InitLocal();
}
