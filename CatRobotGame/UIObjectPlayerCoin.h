/* ========================================
	CatRobotGame/
	------------------------------------
	UI�I�u�W�F�N�g(�v���C���[�����R�C��)�p�w�b�_
	------------------------------------
	�����F�v���C���[�̏����R�C����\������UI�I�u�W�F�N�g
	------------------------------------
	UIObjectPlayerCoin.h
========================================== */
#pragma once

// =============== �C���N���[�h =====================
#include "UIObjectBase.h"

// =============== �O���錾 =====================
class UIObjectText;
class ObjectPlayer;

// =============== �N���X��` =====================
class UIObjectPlayerCoin :
    public UIObjectBase
{
public:
	UIObjectPlayerCoin(SceneBase* pScene);
	void InitLocal() override;
	void UpdateLocal() override;

	DEFINE_UI_OBJECT_TYPE(UIObjectPlayerCoin)
private:
	UIObjectBase*	m_pBG;			// �w�i
	UIObjectBase*	m_pCoinIcon;	// �R�C���A�C�R��
	UIObjectText*	m_pTextCoin;	// �R�C�����e�L�X�g
	ObjectPlayer*	m_pPlayer;
};

