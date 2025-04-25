/* ========================================
	CatRobotGame/
	------------------------------------
	�V�[��(�X�e�[�W4)�pcpp
	------------------------------------
	SceneStage4.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "SceneStage4.h"

#include "FileManager.h"
#include "SoundManager.h"
#include "Input.h"

/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
======================================= */
void SceneStage4::InitLocal()
{
	FileManager::StageObjectInput("Assets/Save/Stage/Stage4.stg");

	PLAY_BGM(BGM_KEY::BGM_GAME_1);
	__super::InitLocal();
}
