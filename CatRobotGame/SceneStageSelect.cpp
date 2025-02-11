/* ========================================
	CatRobotGame/
	------------------------------------
	�V�[��(�X�e�[�W�Z���N�g)�pcpp
	------------------------------------
	SceneStageSelect.cpp
========================================== */

// =============== �C���N���[�h ===================
#include "SceneStageSelect.h"
#include "SceneGameTest.h"
#include "SceneManager.h"
#include "SceneStage1.h"
#include "SceneTitile.h"

#include "FileManager.h"
#include "Input.h"
#include "TextureManager.h"
#include "UIComponentSprite.h"
#include "UIComponentText.h"
#include "UIObjectText.h"

// =============== �萔 ===================
// �V�[�����A�V�[���ύX�֐��̃}�b�v
const std::vector<std::function<void()>> SCENE_CALL =
{
	[]() { SceneManager::ChangeScene<SceneGameTest>(); } ,
	[]() { SceneManager::ChangeScene<SceneTitile>(); } ,
	[]() { SceneManager::ChangeScene<SceneStage1>(); }, 

};

// �X�e�[�W��
const std::vector<std::string> SCENE_NAME =
{
	"�e�X�g�X�e�[�W",
	"�^�C�g��",
	"�X�e�[�W�P",
};

// �X�e�[�W�摜
const TextureManager::E_TEX_KEY SCENE_IMAGE[3] =
{
	TextureManager::E_TEX_KEY::DEBUG_CAMERA_ICON,
	TextureManager::E_TEX_KEY::BLOCK_SIMPLE,
	TextureManager::E_TEX_KEY::STAGE_IMG_STAGE1,
};


/* ========================================
	�������֐�
	-------------------------------------
	���e�F����������
========================================== */
void SceneStageSelect::InitLocal()
{
	FileManager::UIInput("Assets/Save/GameUI/StageSelect.ui");

	m_pStageName = GetSceneUI<UIObjectText>("StageName");
	m_pStageName->GetCompText()->SetFontType(FontType::Letrogo);

	m_pScreenName = GetSceneUI<UIObjectText>("ScreenName");

	m_pStageImage = GetSceneUI<UIObjectBase>("StageImage");
	m_pCompSpriteStgImg = m_pStageImage->GetComponent<UIComponentSprite>();
}


/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�X�V����
========================================== */
void SceneStageSelect::UpdateLocal()
{
	if (Input::IsKeyTrigger(VK_LEFT))
	{
		m_nSelectStageNum = (m_nSelectStageNum + 2) % 3;
	}
	else if (Input::IsKeyTrigger(VK_RIGHT))
	{
		m_nSelectStageNum = (m_nSelectStageNum + 1) % 3;
	}

	m_pStageName->SetText(SCENE_NAME[m_nSelectStageNum]);
	m_pCompSpriteStgImg->SetTexture(GET_TEXTURE_DATA(SCENE_IMAGE[m_nSelectStageNum]));

	if (Input::IsKeyTrigger(VK_RETURN))
	{
		SCENE_CALL[m_nSelectStageNum]();
	}
}
