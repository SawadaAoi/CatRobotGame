/* ========================================
	CatRobotGame/
	------------------------------------
	�V�[��(�X�e�[�W�Z���N�g)�p�w�b�_
	------------------------------------
	�����F�e�X�e�[�W��I������V�[���N���X
	------------------------------------
	SceneStageSelect.h
========================================== */
#pragma once

// =============== �C���N���[�h ===================
#include "SceneBase.h"

// =============== �O���錾 ===================
class UIObjectText;
class UIComponentSprite;

// =============== �N���X��` ===================
class SceneStageSelect :
    public SceneBase
{
public:
	void InitLocal() override;
	void UpdateLocal() override;
private:
	UIObjectText* m_pStageName;
	UIObjectText* m_pScreenName;

	UIObjectBase* m_pStageImage;
	UIComponentSprite* m_pCompSpriteStgImg;

	int m_nSelectStageNum;
};

