/* ========================================
	CatRobotGame/
	------------------------------------
	シーン(ステージセレクト)用cpp
	------------------------------------
	SceneStageSelect.cpp
========================================== */

// =============== インクルード ===================
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

// =============== 定数 ===================
// シーン名、シーン変更関数のマップ
const std::vector<std::function<void()>> SCENE_CALL =
{
	[]() { SceneManager::ChangeScene<SceneGameTest>(); } ,
	[]() { SceneManager::ChangeScene<SceneTitile>(); } ,
	[]() { SceneManager::ChangeScene<SceneStage1>(); }, 

};

// ステージ名
const std::vector<std::string> SCENE_NAME =
{
	"テストステージ",
	"タイトル",
	"ステージ１",
};

// ステージ画像
const TextureManager::E_TEX_KEY SCENE_IMAGE[3] =
{
	TextureManager::E_TEX_KEY::DEBUG_CAMERA_ICON,
	TextureManager::E_TEX_KEY::BLOCK_SIMPLE,
	TextureManager::E_TEX_KEY::STAGE_IMG_STAGE1,
};


/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化処理
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
	更新関数
	-------------------------------------
	内容：更新処理
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
