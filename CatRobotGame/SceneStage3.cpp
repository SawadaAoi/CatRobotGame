/* ========================================
	CatRobotGame/
	------------------------------------
	�V�[��(�X�e�[�W3)�pcpp
	------------------------------------
	SceneStage3.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "SceneStage3.h"

#include "FileManager.h"
#include "SoundManager.h"
#include "Input.h"


/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
======================================= */
void SceneStage3::InitLocal()
{
	FileManager::StageObjectInput("Assets/Save/Stage/Stage3.stg");

	PLAY_BGM(BGM_KEY::BGM_GAME_1);
	__super::InitLocal();
}
