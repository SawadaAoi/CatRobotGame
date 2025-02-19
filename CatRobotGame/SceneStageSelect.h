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
class ObjectCamera;

// =============== �N���X��` ===================
class SceneStageSelect :
    public SceneBase
{
public:
	SceneStageSelect();
	void InitLocal() override;
	void UpdateLocal() override;
private:
	void StageChangeInput();
private:
	ObjectCamera* m_pCamera;

	UIObjectText* m_pStageName;
	UIObjectText* m_pScreenName;

	int m_nSelectStageNum;
	int m_nSelectStageNumOld;

	bool m_bChangeStageModel;
};

