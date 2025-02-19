/* ========================================
	CatRobotGame/
	------------------------------------
	�V�[��(�X�e�[�W2)�pcpp
	------------------------------------
	SceneStage2.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "SceneStage2.h"

#include "ObjectPlayer.h"
#include "ObjectPlayerStart.h"
#include "ObjectCameraPlayer.h"
#include "ObjectCameraDebug.h"

#include "FileManager.h"

#include "ComponentTransform.h"
#include "ObjectGameStateManager.h"


/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
======================================= */
void SceneStage2::InitLocal()
{
	FileManager::StageObjectInput("Assets/Save/Stage/Stage2.stg");

	static_cast<ObjectPlayerStart*>(GetSceneObjectTag(E_ObjectTag::PlayerStart))->SetIsPlayerStart(true);

	AddSceneObject<ObjectCameraPlayer>("PlayerCamera");

	FileManager::UIInput("Assets/Save/UI/GameScene.ui");


	AddSceneObject<ObjectGameStateManager>("GameStateManager");
}
