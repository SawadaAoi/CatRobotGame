/* ========================================
	CatRobotGame/
	------------------------------------
	�V�[��(�X�e�[�W1)�pcpp
	------------------------------------
	SceneStage1.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "SceneStage1.h"

#include "FileManager.h"
#include "SoundManager.h"
#include "Input.h"

/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
======================================= */
void SceneStage1::InitLocal()
{
	FileManager::StageObjectInput("Assets/Save/Stage/Stage1.stg");

	PLAY_BGM(BGM_KEY::BGM_GAME_1);

	__super::InitLocal();
}

