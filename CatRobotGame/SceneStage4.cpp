/* ========================================
	CatRobotGame/
	------------------------------------
	�V�[��(�X�e�[�W4)�pcpp
	------------------------------------
	SceneStage4.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "SceneStage4.h"

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
void SceneStage4::InitLocal()
{
	FileManager::StageObjectInput("Assets/Save/Stage/Stage4.stg");

	static_cast<ObjectPlayerStart*>(GetSceneObjectTag(E_ObjectTag::PlayerStart))->SetIsPlayerStart(true);
	

	AddSceneObject<ObjectCameraPlayer>("PlayerCamera");

	FileManager::UIInput("Assets/Save/UI/GameScene.ui");


	AddSceneObject<ObjectGameStateManager>("GameStateManager");
}
