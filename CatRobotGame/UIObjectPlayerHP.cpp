/* ========================================
	CatRobotGame/
	------------------------------------
	UI�I�u�W�F�N�g(�v���C���[HP)�pcpp
	------------------------------------
	UIObjectPlayerHP.cpp
========================================== */

// =============== �C���N���[�h =====================
#include "ObjectPlayer.h"
#include "SceneBase.h"
#include "TextureManager.h"
// �R���|�[�l���g
#include "UIComponentSprite.h"
#include "UIComponentTransform.h"
#include "UIObjectPlayerHP.h"

// =============== �萔��` =======================
const Vector2<float> DEFAULT_SCALE = Vector2<float>(100.0f, 100.0f);

const std::string		HEART_OBJECT_NAME = "Heart_";							// HP�I�u�W�F�N�g��
const Vector2<float>	HEART_TEXTURE_SCALE = Vector2<float>(100.0f, 100.0f);	// HP�e�N�X�`���̃X�P�[��
const float				HEART_TEXTURE_SPACE = 70.0f;							// HP�e�N�X�`���̊Ԋu

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F������
	-------------------------------------
	����1�F���L�V�[��
========================================== */
UIObjectPlayerHP::UIObjectPlayerHP(SceneBase* pScene)
	: UIObjectBase(pScene)
	, m_pPlayerIcon(nullptr)
	, m_pPlayer(nullptr)
{
}


/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
========================================== */
void UIObjectPlayerHP::InitLocal()
{
	m_pPlayer = static_cast<ObjectPlayer*>(m_pOwnerScene->GetSceneObjectTag(E_ObjectTag::Player));

	// �����p�����[�^�ݒ�
	m_pCompTransform->SetScale(DEFAULT_SCALE);
	m_pCompSprite->SetIsVisible(false);

	// �v���C���[�A�C�R����ݒ�(��ԍ�)
	m_pPlayerIcon = m_pOwnerScene->AddSceneUI<UIObjectBase>("0_PlayerIcon");
	m_pPlayerIcon->GetTransform()->SetPosition(GetTransform()->GetPosition());
	m_pPlayerIcon->GetTransform()->SetScale(DEFAULT_SCALE);
	m_pPlayerIcon->GetComponent<UIComponentSprite>()->SetTexture(GET_TEXTURE_DATA(TEX_KEY::UI_PLAYER_ICON));
	m_pPlayerIcon->SetIsSave(false);
	AddChildUI(m_pPlayerIcon);

	// �v���C���[�����݂���ꍇ��HP�𐶐�
	if (m_pPlayer) CreateHP();
}


/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�X�V����
========================================== */
void UIObjectPlayerHP::UpdateLocal()
{

	// �v���C���[�����݂��Ȃ��ꍇ�͎擾����
	if (!m_pPlayer)
	{
		m_pPlayer = static_cast<ObjectPlayer*>(m_pOwnerScene->GetSceneObjectTag(E_ObjectTag::Player));
		if (m_pPlayer) CreateHP();		// �v���C���[�����݂���ꍇ��HP�𐶐�

		return;
	}

	int nHP		= m_pPlayer->GetHp();		// TODO: �v���C���[��HP���擾����
	int nHPMax	= m_pPlayer->GetMaxHp();	// TODO: �v���C���[�̍ő�HP���擾����

	// HP�̕\�������X�V
	for (int i = 0; i < nHPMax; i++)
	{
		m_pUIObjectHP[i]->GetComponent<UIComponentSprite>()->SetIsVisible(i < nHP);	
	}
}

/* ========================================
	HP�����֐�
	-------------------------------------
	���e�FHP�𐶐�����
========================================== */
void UIObjectPlayerHP::CreateHP()
{
	int nHP = m_pPlayer->GetHp();		// TODO: �v���C���[��HP���擾����

	// HP�����̃n�[�g�𐶐�
	for (int i = 1; i <= nHP; i++)
	{
		// �n�[�g�I�u�W�F�N�g�𐶐�(���O��"Heart_" + i)
		UIObjectBase* pUIObject = m_pOwnerScene->AddSceneUI<UIObjectBase>(HEART_OBJECT_NAME + std::to_string(i));

		pUIObject->SetIsSave(false);

		// �g�����X�t�H�[��
		UIComponentTransform* pCompTrans = pUIObject->GetTransform();
		Vector2<float> vPos = GetTransform()->GetPosition() + Vector2<float>(i * HEART_TEXTURE_SPACE, 0.0f);
		pCompTrans->SetPosition(vPos);
		pCompTrans->SetScale(HEART_TEXTURE_SCALE);
		// �X�v���C�g
		UIComponentSprite* pCompSprite = pUIObject->GetComponent<UIComponentSprite>();
		pCompSprite->SetTexture(GET_TEXTURE_DATA(TEX_KEY::UI_HP_HEART));

		AddChildUI(pUIObject);
		m_pUIObjectHP.push_back(pUIObject);
	}
}

