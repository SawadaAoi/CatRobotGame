/* ========================================
	CatRobotGame/
	------------------------------------
	�V�[��(�X�e�[�W2)�pcpp
	------------------------------------
	SceneStage2.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "SceneStage2.h"

#include "FileManager.h"
#include "SoundManager.h"
#include "Input.h"



/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
======================================= */
void SceneStage2::InitLocal()
{
	FileManager::StageObjectInput("Assets/Save/Stage/Stage2.stg");

	__super::InitLocal();
}
