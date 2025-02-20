/* ========================================
	CatRobotGame/
	------------------------------------
	�S�V�[���o�^�p�w�b�_
	------------------------------------
	�����F�V�[���̓o�^�������܂Ƃ߂Ă���
	------------------------------------
	RegisterAllScene.h
========================================== */
#pragma once

// =============== �C���N���[�h ===================
#include "SceneManager.h"

#include "SceneGameTest.h"

#include "SceneTitile.h"
#include "SceneStageSelect.h"

#include "SceneStage1.h"
#include "SceneStage2.h"

/* ========================================
	�V�[���o�^�֐�
	-------------------------------------
	���e�F�}�b�v�ɃV�[����o�^����
=========================================== */
void SceneManager::RegisterAllScene()
{
	REGISTER_SCENE(SceneGameTest);
	REGISTER_SCENE(SceneTitile);
	REGISTER_SCENE(SceneStageSelect);
	REGISTER_SCENE(SceneStage1);
	REGISTER_SCENE(SceneStage2);
}
