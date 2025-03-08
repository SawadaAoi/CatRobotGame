/* ========================================
	CatRobotGame/
	------------------------------------
	シーン(ステージ1)用cpp
	------------------------------------
	SceneStage1.cpp
========================================== */

// =============== インクルード ===================
#include "SceneStage1.h"

#include "ObjectPlayer.h"
#include "ObjectPlayerStart.h"
#include "ObjectCameraPlayer.h"

#include "FileManager.h"

#include "ComponentTransform.h"
#include "ObjectGameStateManager.h"
#include "SoundManager.h"


/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化処理
======================================= */
void SceneStage1::InitLocal()
{
	FileManager::StageObjectInput("Assets/Save/Stage/Stage1.stg");

	static_cast<ObjectPlayerStart*>(GetSceneObjectTag(E_ObjectTag::PlayerStart))->SetIsPlayerStart(true);
	

	AddSceneObject<ObjectCameraPlayer>("PlayerCamera");

	FileManager::UIInput("Assets/Save/UI/GameScene.ui");


	AddSceneObject<ObjectGameStateManager>("GameStateManager");

	PLAY_BGM(BGM_KEY::BGM_GAME_1);

}
