/* ========================================
	CatRobotGame/
	------------------------------------
	�V�[��(�X�e�[�W���)�p�w�b�_
	------------------------------------
	�����F�X�e�[�W�V�[���̊��N���X
	------------------------------------
	SceneStageBase.h
========================================== */
#pragma once

// =============== �C���N���[�h ===================
#include "SceneBase.h"


// =============== �N���X��` ===================
class SceneStageBase :
    public SceneBase
{
public:
	SceneStageBase();
	void InitLocal() override;
	void UpdateLocal() override;

	DEFINE_SCENE_TYPE(SceneStageBase)
private:
	void Pause();	// �|�[�Y����
	void Resume();	// �|�[�Y��������
private:
	bool m_bPause;	// �|�[�Y�t���O(true:�|�[�Y��)
};

