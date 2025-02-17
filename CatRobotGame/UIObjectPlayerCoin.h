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
	UIObjectText*	m_pTextCoin;
	ObjectPlayer*		m_pPlayer;
};

