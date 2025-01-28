/* ========================================
	DX22Base/
	------------------------------------
	デバッグウィンドウ設定用cpp
	------------------------------------
	DebugWindowSetting.cpp
========================================== */
#ifdef _DEBUG	// デバッグモードのみ有効

// =============== インクルード ===================
#include "DebugWindowSetting.h"
#include "DebugMenu.h"
#include "GridLine.h"	// グリッド線再読み込み
#include "SettingWindowAPI.h"
#include "SceneManager.h"
#include "CameraManager.h"	// カメラマネージャ

// シーン
#include <type_traits>
#include "SceneGameTest.h"
#include "SceneStage1.h"
#include "SceneTitile.h"

// =============== 名前空間 ===================
namespace DebugUI
{

	// ウィンドウ名(const char*で定義しているため、宣言と定義を分けている)
	// stringではなくconst char*なのは、DebugMenuの多くの関数で文字列をconst char*で扱っているため
	const char* WIN_NAME[E_WinType::MAX] =
	{
		"DebugWindowList",
		"BasicSettings",
		"CameraInfo",
		"SceneList",
		"ObjectList",
		"ObjectInfo",
		"UIList",
		"UIInfo",
	};

	// シーン名、シーン変更関数のマップ
	const std::map< std::string, std::function<void()>> SCENE_MAP =
	{
		{"SceneGameTest", []() { SceneManager::ChangeScene<SceneGameTest>(); } },
		{"SceneStage1", []() { SceneManager::ChangeScene<SceneStage1>(); } },
		{"SceneTitile", []() { SceneManager::ChangeScene<SceneTitile>(); } },

	};

/* ========================================
	デバッグ用ウィンドウ初期化関数
	-------------------------------------
	内容：各ウィンドウの初期化を行う
=========================================== */
void InitDebugWindow()
{
	// 各ウィンドウ生成
	for (int i = 1; i < E_WinType::MAX; ++i)
	{
		Menu::Create(WIN_NAME[i]);
	}

	InitBasicSettings();
	InitCameraInfo();
	InitSceneList();
}

/* ========================================
	ウィンドウ初期化(基本設定)関数
	-------------------------------------
	内容：基本設定の初期化を行う
=========================================== */
void InitBasicSettings()
{
	// 背景色
	WIN_BASIC_SETTING.AddItem(Item::CreateValue("BackColor", Item::Color, true));
	// 当たり判定表示
	WIN_BASIC_SETTING.AddItem(Item::CreateValue("DispCollision", Item::Bool, true));	
	// グリッド線
	// 値を変更したら線の初期化を行う関数
	Item::Callback FuncClickSave = [](bool isWrite, void* arg) {
		if (isWrite)
			GridLine::Init();
	};
	Item* pGridGroup = Item::CreateGroup("Grid");
	pGridGroup->AddGroupItem(Item::CreateCallBack("GridEnable", Item::Bool, FuncClickSave, true));	// グリッド線の表示
	pGridGroup->AddGroupItem(Item::CreateCallBack("AxisEnable", Item::Bool, FuncClickSave, true, true));	// 軸線の表示
	pGridGroup->AddGroupItem(Item::CreateCallBack("Size", Item::Float, FuncClickSave, true));	// マス数
	pGridGroup->AddGroupItem(Item::CreateCallBack("Margin", Item::Float, FuncClickSave, true));	// 線幅
	pGridGroup->AddGroupItem(Item::CreateCallBack("Color", Item::Color, FuncClickSave, true));	// 線色

	WIN_BASIC_SETTING.AddItem(pGridGroup);

	Item* pDrawGroup = Item::CreateGroup("Draw");
	// FPS
	pDrawGroup->AddGroupItem(Item::CreateValue("FPS", Item::Text, false));
	// ポーズ
	pDrawGroup->AddGroupItem(Item::CreateValue("Pause", Item::Bool, false, true));
	// 最大FPS
	pDrawGroup->AddGroupItem(Item::CreateValue("MaxFPS", Item::Float, false));

	WIN_BASIC_SETTING.AddItem(pDrawGroup);

	WIN_BASIC_SETTING["Draw"]["Pause"].SetBool(false);
	WIN_BASIC_SETTING["Draw"]["MaxFPS"].SetFloat(WindowConfig::REFRESH_RATE);

}

/* ========================================
	ウィンドウ初期化(カメラ情報)関数
	-------------------------------------
	内容：カメラ情報の初期化を行う
=========================================== */
void InitCameraInfo()
{
	WIN_CAMERA_INFO.AddItem(Item::CreateValue("ActiveCamera", Item::Kind::Text));	// アクティブカメラ名

	WIN_CAMERA_INFO.AddItem(Item::CreateValue("Orthographic", Item::Kind::Bool));	// 平行投影かどうか

	WIN_CAMERA_INFO.AddItem(Item::CreateList("CameraList", [](const void* arg)		// カメラリスト
	{
		// クリックされたカメラをアクティブにする
		std::string sCameraName = reinterpret_cast<const char*>(arg);				// リスト項目名
		int nCameraNum = WIN_CAMERA_INFO["CameraList"].GetListNo(sCameraName.c_str());	// カメラ番号を取得

		CAMERA_MNG_INST.SwitchCamera(nCameraNum);	// カメラ切り替え
	}, false, false, false, 3));

}

/* ========================================
	ウィンドウ初期化(シーン一覧)関数
	-------------------------------------
	内容：シーン一覧の初期化を行う
=========================================== */
void InitSceneList()
{
	// シーン一覧
	Item* pSceneList = Item::CreateList("SceneLists", [](const void* arg) 
	{
		// 選択したらシーン変更
		std::string sSceneName = reinterpret_cast<const char*>(arg);	// リスト項目名
		SCENE_MAP.at(sSceneName)();	// シーン変更
	}, true);

	// シーン名をリストに追加
	for (auto& scene : SCENE_MAP)
	{
		pSceneList->AddListItem(scene.first.c_str());
	}

	WIN_SCENE_LIST.AddItem(pSceneList);
}

}

#endif // _DEBUG