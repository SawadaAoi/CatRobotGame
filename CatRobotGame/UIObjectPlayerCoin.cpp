/* ========================================
	CatRobotGame/
	------------------------------------
	UI�I�u�W�F�N�g(�v���C���[�����R�C��)�pcpp
	------------------------------------
	UIObjectPlayerCoin.cpp
========================================== */

// =============== �C���N���[�h =====================
#include "UIObjectPlayerCoin.h"
#include "UIObjectText.h"
#include "ObjectPlayer.h"

#include "SceneBase.h"
#include "UIComponentSprite.h"
#include "UIComponentText.h"

#include "TextureManager.h"
#include "ColorVec3.h"

// =============== �萔��` =======================
const std::string STATIC_TEXT = "COIN : ";


/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F������
	-------------------------------------
	����1�F���L�V�[��
========================================== */
UIObjectPlayerCoin::UIObjectPlayerCoin(SceneBase* pScene)
	: UIObjectBase(pScene)
	, m_pTextCoin(nullptr)
	, m_pPlayer(nullptr)
{
}

/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
========================================== */
void UIObjectPlayerCoin::InitLocal()
{
	m_pCompSprite->SetIsVisible(false);

	m_pTextCoin = m_pOwnerScene->AddSceneUI<UIObjectText>("Coin");
	m_pTextCoin->GetCompText()->SetFontColor(D2D1::ColorF::Black);
	m_pTextCoin->GetCompText()->SetFontSize(50);
	m_pTextCoin->GetCompText()->SetFontType(FontType::SmartFontUI);
	m_pTextCoin->GetCompText()->SetPivot(E_Pivot::LEFT_CENTER);
	m_pTextCoin->SetIsSave(false);

	 m_pPlayer = static_cast<ObjectPlayer*>(m_pOwnerScene->GetSceneObjectTag(E_ObjectTag::Player));

	m_pTextCoin->SetText(STATIC_TEXT + std::to_string(0));

	AddChildUI(m_pTextCoin);
}

/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�X�V����
========================================== */
void UIObjectPlayerCoin::UpdateLocal()
{
	if (!m_pPlayer)
	{
		 m_pPlayer = static_cast<ObjectPlayer*>(m_pOwnerScene->GetSceneObjectTag(E_ObjectTag::Player));
		return;
	}

	m_pTextCoin->SetText(STATIC_TEXT + std::to_string(m_pPlayer->GetCoinNum()));
}
