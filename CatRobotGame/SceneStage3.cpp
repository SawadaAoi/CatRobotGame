/* ========================================
	CatRobotGame/
	------------------------------------
	シーン(ステージ3)用cpp
	------------------------------------
	SceneStage3.cpp
========================================== */

// =============== インクルード ===================
#include "SceneStage3.h"

#include "ObjectPlayer.h"
#include "ObjectPlayerStart.h"
#include "ObjectCameraPlayer.h"

#include "FileManager.h"

#include "ComponentTransform.h"
#include "ObjectGameStateManager.h"


/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化処理
======================================= */
void SceneStage3::InitLocal()
{
	FileManager::StageObjectInput("Assets/Save/Stage/Stage3.stg");

	static_cast<ObjectPlayerStart*>(GetSceneObjectTag(E_ObjectTag::PlayerStart))->SetIsPlayerStart(true);
	

	AddSceneObject<ObjectCameraPlayer>("PlayerCamera");

	FileManager::UIInput("Assets/Save/UI/GameScene.ui");


	AddSceneObject<ObjectGameStateManager>("GameStateManager");
}
