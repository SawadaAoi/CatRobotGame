/* ========================================
	CatRobotGame/
	------------------------------------
	�I�u�W�F�N�g(�v���C���[)�pcpp
	------------------------------------
	ObjectPlayer.cpp
========================================== */

// =============== �C���N���[�h =====================
#include "ObjectPlayer.h"


// �R���|�[�l���g
#include "ComponentTransform.h"
#include "ComponentRigidbody.h"
#include "ComponentCollisionOBB.h"
#include "ComponentPlayerController.h"
#include "ComponentGroundRaycast.h"
#include "ComponentModelAnime.h"


/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F������
	-------------------------------------
	����1�F���L�V�[���|�C���^
=========================================== */
ObjectPlayer::ObjectPlayer(SceneBase* pScene)
	: ObjectBase(pScene)
	, m_pCompGroundRaycast(nullptr)
	, m_pCompRigidbody(nullptr)
	, m_pCompModelAnime(nullptr)
	, m_pCompPlayerController(nullptr)
{
	SetTag(E_ObjectTag::Player);	// �^�O�̐ݒ�
}

/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
========================================= */
void ObjectPlayer::InitLocal()
{
	m_pCompTransform =GetComponent<ComponentTransform>();

	m_pCompGroundRaycast = AddComponent<ComponentGroundRaycast>();
	m_pCompGroundRaycast->SetStartPosOffset(Vector3<float>(0.0f, -0.4f, 0.0f));
	m_pCompGroundRaycast->SetRayLength(0.2f);

	AddComponent<ComponentCollisionOBB>();
	
	m_pCompRigidbody = AddComponent<ComponentRigidbody>();
	m_pCompRigidbody->SetUseGravity(true);
	m_pCompRigidbody->SetGroundDrag(0.9f);

	m_pCompPlayerController = AddComponent<ComponentPlayerController>();

	m_pCompModelAnime = AddComponent<ComponentModelAnime>();

}

/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�X�V����
========================================= */
void ObjectPlayer::UpdateLocal()
{
	// �n�ʂɐݒu���Ă���ꍇ�@���@�W�����v���łȂ��ꍇ
	if (m_pCompGroundRaycast->GetHitFlg() && m_pCompRigidbody->GetVelocity().y <=0.0f)
	{
		Vector3<float> vPos = m_pCompTransform->GetWorldPosition();
		vPos.y = m_pCompGroundRaycast->GetHitPos().y + 0.5f;
		m_pCompTransform->SetLocalPosition(vPos);

		m_pCompPlayerController->SetUseJump(true);
	}
	else
	{
		m_pCompPlayerController->SetUseJump(false);
	}

}


