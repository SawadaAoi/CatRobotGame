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
#include "UIComponentTransform.h"

#include "TextureManager.h"
#include "ColorVec3.h"

// =============== �萔��` =======================
const Vector2<float> BG_SCALE = { 160.0f, 85.0f };

const Vector2<float> COIN_ICON_SCALE	= { 0.5f, 0.5f };
const Vector2<float> COIN_ICON_POSITON = { -30.0f, 0.0f };

const Vector2<float> TEXT_POSITON		= { -30.0f, -10.0f };
const std::string	STATIC_TEXT = " ";

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F������
	-------------------------------------
	����1�F���L�V�[��
========================================== */
UIObjectPlayerCoin::UIObjectPlayerCoin(SceneBase* pScene)
	: UIObjectBase(pScene)
	, m_pBG(nullptr)
	, m_pCoinIcon(nullptr)
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

	// �w�i
	m_pBG = m_pOwnerScene->AddSceneUI<UIObjectBase>("CoinBG");
	m_pBG->GetSprite()->SetTexture(GET_TEXTURE_DATA(TEX_KEY::UI_FRAME_2));
	m_pBG->GetTransform()->SetScale(BG_SCALE);
	m_pBG->SetIsSave(false);
	AddChildUI(m_pBG);

	// �R�C���A�C�R��
	m_pCoinIcon = m_pOwnerScene->AddSceneUI<UIObjectBase>("CoinIcon");
	m_pCoinIcon->GetSprite()->SetTexture(GET_TEXTURE_DATA(TEX_KEY::UI_COIN_ICON));
	m_pCoinIcon->GetTransform()->Scale(COIN_ICON_SCALE);
	m_pCoinIcon->SetIsSave(false);
	AddChildUI(m_pCoinIcon);

	// �R�C�����e�L�X�g
	m_pTextCoin = m_pOwnerScene->AddSceneUI<UIObjectText>("CoinText");
	m_pTextCoin->GetCompText()->SetFontColor(D2D1::ColorF::Black);
	m_pTextCoin->GetCompText()->SetFontSize(60);
	m_pTextCoin->GetCompText()->SetFontType(FontType::Letrogo);
	m_pTextCoin->GetCompText()->SetPivot(E_Pivot::LEFT_CENTER);
	m_pTextCoin->SetText(STATIC_TEXT + std::to_string(0));
	m_pTextCoin->SetIsSave(false);
	AddChildUI(m_pTextCoin);

	m_pTextCoin->GetTransform()->SetPosition(TEXT_POSITON);
	m_pCoinIcon->GetTransform()->SetPosition(COIN_ICON_POSITON);

	m_pPlayer = static_cast<ObjectPlayer*>(m_pOwnerScene->GetSceneObjectTag(E_ObjectTag::Player));
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
