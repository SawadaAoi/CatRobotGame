/* ========================================
	CatRobotGame/
	------------------------------------
	シーン(ステージセレクト)用cpp
	------------------------------------
	SceneStageSelect.cpp
========================================== */

// =============== インクルード ===================
#include "SceneStageSelect.h"

#include "SceneManager.h"
#include "FileManager.h"
#include "SoundManager.h"
#include "Input.h"

#include "UIObjectText.h"
#include "UIComponentText.h"
#include "UIComponentSprite.h"

#include "ObjectLightDirectional.h"
#include "ObjectCamera.h"
#include "ComponentTransform.h"


// =============== 定数 ===================
// シーン名、シーン変更関数のマップ
const std::vector<std::function<void()>> SCENE_CALL =
{
	[]() { SceneManager::ChangeScene("SceneStage1"); },
	[]() { SceneManager::ChangeScene("SceneStage2"); },
	[]() { SceneManager::ChangeScene("SceneStage3"); },
	[]() { SceneManager::ChangeScene("SceneStage4"); },
};

// ステージ名
const std::vector<std::string> SCENE_NAME =
{
	"ステージ１",
	"ステージ２",
	"ステージ３",
	"ステージ４",
};


// ステージモデルデータ
// ファイル保存位置
const std::string MODEL_DATA_PATH = "Assets/Save/StageSelect/";
// ファイル名
const std::vector<std::string> MODEL_DATA_NAME =
{
	"Stage1_Select.slc",
	"Stage2_Select.slc",
	"Stage3_Select.slc",
	"Stage4_Select.slc",
};

const int STAGE_NUM_MAX = SCENE_NAME.size();	// ステージ数

// カメラ位置
const Vector3<float> CAMERA_POS_ZOOMIN	= { 0.0f, 30.0f, -40.0f };
const Vector3<float> CAMERA_POS_ZOOMOUT = { 0.0f, 120.0f, -150.0f };
const float CAMERA_ROT_X = 40.0f;	// カメラ回転角度

// UVスクロール速度
const float UV_SCROLL_SPEED = 0.1f;

/* ========================================
	コンストラクタ
	-------------------------------------
	内容：コンストラクタ
========================================== */
SceneStageSelect::SceneStageSelect()
	: m_bChangeStageModel(false)
	, m_nSelectStageNum(0)
	, m_nSelectStageNumOld(-1)
	, m_pCamera(nullptr)
	, m_pStageName(nullptr)
	, m_pScreenName(nullptr)
	, m_pBG_Image(nullptr)
{
}

/* ========================================
	初期化関数
	-------------------------------------
	内容：初期化処理
========================================== */
void SceneStageSelect::InitLocal()
{
	AddSceneObject<ObjectLightDirectional>("Light");

	// カメラ追加
	m_pCamera = AddSceneObject<ObjectCamera>("Camera");
	m_pCamera->GetTransform()->SetPosition(CAMERA_POS_ZOOMIN);
	m_pCamera->GetTransform()->RotateX(CAMERA_ROT_X);

	// UI読み込み
	FileManager::UIInput("Assets/Save/UI/StageSelect.ui");

	// ステージ名、画面名取得
	m_pStageName = GetSceneUI<UIObjectText>("StageNameText");			
	m_pStageName->GetCompText()->SetFontType(FontType::Letrogo);
	m_pScreenName = GetSceneUI<UIObjectText>("ScreenNameText");

	// 背景画像取得
	m_pBG_Image = GetSceneUI<UIObjectBase>("BG_Image");
	m_pBG_Image->SetIs3DObjBackDraw(true);

	// ステージモデル読み込み
	FileManager::StageObjectInput(MODEL_DATA_PATH + MODEL_DATA_NAME[m_nSelectStageNum]);

	SceneManager::SetFadeInKind(FADE_KIND_NORMAL);
	SceneManager::SetFadeTime(2.0f);

	PLAY_BGM(BGM_KEY::BGM_SELECT);

}


/* ========================================
	更新関数
	-------------------------------------
	内容：更新処理
========================================== */
void SceneStageSelect::UpdateLocal()
{
	// UVスクロール
	Vector2<float> vUvPos = m_pBG_Image->GetSprite()->GetUvPos();
	vUvPos.x -= UV_SCROLL_SPEED * DELTA_TIME;
	vUvPos.y -= UV_SCROLL_SPEED * DELTA_TIME;
	m_pBG_Image->GetSprite()->SetUvPos(vUvPos);

	// ステージモデルが変更中なら
	if (m_bChangeStageModel) 
	{
		// ステージモデルが完全に削除されたら
		if (!GetSceneObjectTag(E_ObjectTag::StageSampleParent))
		{
			FileManager::StageObjectInput(MODEL_DATA_PATH + MODEL_DATA_NAME[m_nSelectStageNum]);	// ステージモデルを読み込み

			m_pCamera->GetTransform()->MoveTo(CAMERA_POS_ZOOMIN, 0.3f);	// カメラ位置を変更(モデルが拡大されるように見える位置に)
			m_bChangeStageModel = false;
		}	
	}
	else
	{
		StageChangeInput();	// ステージ変更入力

		// ステージが変更されたら
		if (m_nSelectStageNum != m_nSelectStageNumOld)
		{
			m_pStageName->SetText(SCENE_NAME[m_nSelectStageNum]);			// ステージ名を変更
			GetSceneObjectTag(E_ObjectTag::StageSampleParent)->Destroy();	// 現在表示されているステージモデルを削除
			m_pCamera->GetTransform()->SetPosition(CAMERA_POS_ZOOMOUT);			// カメラ位置を変更(モデルが縮小されるように見える位置に)

			m_bChangeStageModel = true;

		}
	}

	m_nSelectStageNumOld = m_nSelectStageNum;
}



/* ========================================
	ステージ変更入力関数
	-------------------------------------
	内容：ステージ変更入力処理
========================================== */
void SceneStageSelect::StageChangeInput()
{
	if (Input::IsKeyTrigger(VK_LEFT))
	{
		m_nSelectStageNum = (m_nSelectStageNum + STAGE_NUM_MAX - 1) % STAGE_NUM_MAX;

		PLAY_SE(SE_KEY::SE_MENU_CURSOR);
	}
	else if (Input::IsKeyTrigger(VK_RIGHT))
	{
		m_nSelectStageNum = (m_nSelectStageNum + 1) % STAGE_NUM_MAX;
		PLAY_SE(SE_KEY::SE_MENU_CURSOR);
	}

	if (Input::IsKeyTrigger(VK_RETURN))
	{
		SceneManager::SetFadeOutKind(FADE_KIND_NORMAL);
		SCENE_CALL[m_nSelectStageNum]();

		PLAY_SE(SE_KEY::SE_MENU_DECIDE);
	}
}

