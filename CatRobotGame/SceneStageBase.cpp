/* ========================================
	CatRobotGame/
	------------------------------------
	�V�[��(�X�e�[�W���)�pcpp
	------------------------------------
	SceneStageBase.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "SceneStageBase.h"
#include "Input.h"
#include "ObjectPlayer.h"
#include "ObjectPlayerStart.h"
#include "ObjectCameraPlayer.h"
#include "ObjectGameStateManager.h"

#include "FileManager.h"

/* ========================================
	�R���X�g���N�^
	-------------------------------------
	���e�F�R���X�g���N�^
========================================== */
SceneStageBase::SceneStageBase()
	: m_bPause(false)
{
}

/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
========================================== */
void SceneStageBase::InitLocal()
{
	// �v���C���[�̐���
	static_cast<ObjectPlayerStart*>(GetSceneObjectTag(E_ObjectTag::PlayerStart))->SetIsPlayerStart(true);

	// �J�����v���C���[��ǉ�
	AddSceneObject<ObjectCameraPlayer>("PlayerCamera");

	// UI�ǂݍ���
	FileManager::UIInput("Assets/Save/UI/GameScene.ui");

	// �Q�[���X�e�[�g�}�l�[�W����ǉ�
	AddSceneObject<ObjectGameStateManager>("GameStateManager");
}

/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�X�V����
========================================== */
void SceneStageBase::UpdateLocal()
{
	// �|�[�Y����
	if (Input::IsKeyTrigger('P'))
	{
		if (m_bPause)
		{
			Resume();
		}
		else
		{
			Pause();
		}

		m_bPause = !m_bPause;
	}
}

/* ========================================
	�|�[�Y����
	-------------------------------------
	���e�F�|�[�Y����
		�@�V�[���ɓo�^����Ă���I�u�W�F�N�g��S�Ē�~(�A�N�e�B�u��Ԃ��ꎞ��~��ԂɕύX)
========================================== */
void SceneStageBase::Pause()
{
	// �����I�u�W�F�N�g�z��
	for (auto& pObject : m_pObjects)
	{
		if (pObject->GetState() == OBJ_DEAD) continue;
		pObject->SetState(OBJ_PAUSE);
	}

	// �ꎞ�ۑ��I�u�W�F�N�g�z��
	for (auto& pObject : m_pStandbyObjects)
	{
		if (pObject->GetState() == OBJ_DEAD) continue;
		pObject->SetState(OBJ_PAUSE);
	}
}

/* ========================================
	�|�[�Y��������
	-------------------------------------
	���e�F�|�[�Y��������
		�@�V�[���ɓo�^����Ă���I�u�W�F�N�g��S�čĊJ(�ꎞ��~��Ԃ��A�N�e�B�u��ԂɕύX)
========================================== */
void SceneStageBase::Resume()
{
	// �����I�u�W�F�N�g�z��
	for (auto& pObject : m_pObjects)
	{
		if (pObject->GetState() == OBJ_DEAD) continue;
		pObject->SetState(OBJ_ACTIVE);
	}

	// �ꎞ�ۑ��I�u�W�F�N�g�z��
	for (auto& pObject : m_pStandbyObjects)
	{
		if (pObject->GetState() == OBJ_DEAD) continue;
		pObject->SetState(OBJ_ACTIVE);
	}
}
