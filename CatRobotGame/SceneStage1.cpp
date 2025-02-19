/* ========================================
	CatRobotGame/
	------------------------------------
	�V�[��(�X�e�[�W1)�pcpp
	------------------------------------
	SceneStage1.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "SceneStage1.h"

#include "ObjectPlayer.h"
#include "ObjectPlayerStart.h"
#include "ObjectCameraPlayer.h"

#include "FileManager.h"

#include "ComponentTransform.h"
#include "ObjectGameStateManager.h"


/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
======================================= */
void SceneStage1::InitLocal()
{
	FileManager::StageObjectInput("Assets/Save/Stage/Stage1.stg");

	static_cast<ObjectPlayerStart*>(GetSceneObjectTag(E_ObjectTag::PlayerStart))->SetIsPlayerStart(true);
	

	AddSceneObject<ObjectCameraPlayer>("PlayerCamera");

	FileManager::UIInput("Assets/Save/UI/GameScene.ui");


	AddSceneObject<ObjectGameStateManager>("GameStateManager");
}
