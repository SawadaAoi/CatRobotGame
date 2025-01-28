/* ========================================
	DX22Base/
	------------------------------------
	�f�o�b�O�E�B���h�E�ݒ�pcpp
	------------------------------------
	DebugWindowSetting.cpp
========================================== */
#ifdef _DEBUG	// �f�o�b�O���[�h�̂ݗL��

// =============== �C���N���[�h ===================
#include "DebugWindowSetting.h"
#include "DebugMenu.h"
#include "GridLine.h"	// �O���b�h���ēǂݍ���
#include "SettingWindowAPI.h"
#include "SceneManager.h"
#include "CameraManager.h"	// �J�����}�l�[�W��

// �V�[��
#include <type_traits>
#include "SceneGameTest.h"
#include "SceneStage1.h"
#include "SceneTitile.h"

// =============== ���O��� ===================
namespace DebugUI
{

	// �E�B���h�E��(const char*�Œ�`���Ă��邽�߁A�錾�ƒ�`�𕪂��Ă���)
	// string�ł͂Ȃ�const char*�Ȃ̂́ADebugMenu�̑����̊֐��ŕ������const char*�ň����Ă��邽��
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

	// �V�[�����A�V�[���ύX�֐��̃}�b�v
	const std::map< std::string, std::function<void()>> SCENE_MAP =
	{
		{"SceneGameTest", []() { SceneManager::ChangeScene<SceneGameTest>(); } },
		{"SceneStage1", []() { SceneManager::ChangeScene<SceneStage1>(); } },
		{"SceneTitile", []() { SceneManager::ChangeScene<SceneTitile>(); } },

	};

/* ========================================
	�f�o�b�O�p�E�B���h�E�������֐�
	-------------------------------------
	���e�F�e�E�B���h�E�̏��������s��
=========================================== */
void InitDebugWindow()
{
	// �e�E�B���h�E����
	for (int i = 1; i < E_WinType::MAX; ++i)
	{
		Menu::Create(WIN_NAME[i]);
	}

	InitBasicSettings();
	InitCameraInfo();
	InitSceneList();
}

/* ========================================
	�E�B���h�E������(��{�ݒ�)�֐�
	-------------------------------------
	���e�F��{�ݒ�̏��������s��
=========================================== */
void InitBasicSettings()
{
	// �w�i�F
	WIN_BASIC_SETTING.AddItem(Item::CreateValue("BackColor", Item::Color, true));
	// �����蔻��\��
	WIN_BASIC_SETTING.AddItem(Item::CreateValue("DispCollision", Item::Bool, true));	
	// �O���b�h��
	// �l��ύX��������̏��������s���֐�
	Item::Callback FuncClickSave = [](bool isWrite, void* arg) {
		if (isWrite)
			GridLine::Init();
	};
	Item* pGridGroup = Item::CreateGroup("Grid");
	pGridGroup->AddGroupItem(Item::CreateCallBack("GridEnable", Item::Bool, FuncClickSave, true));	// �O���b�h���̕\��
	pGridGroup->AddGroupItem(Item::CreateCallBack("AxisEnable", Item::Bool, FuncClickSave, true, true));	// �����̕\��
	pGridGroup->AddGroupItem(Item::CreateCallBack("Size", Item::Float, FuncClickSave, true));	// �}�X��
	pGridGroup->AddGroupItem(Item::CreateCallBack("Margin", Item::Float, FuncClickSave, true));	// ����
	pGridGroup->AddGroupItem(Item::CreateCallBack("Color", Item::Color, FuncClickSave, true));	// ���F

	WIN_BASIC_SETTING.AddItem(pGridGroup);

	Item* pDrawGroup = Item::CreateGroup("Draw");
	// FPS
	pDrawGroup->AddGroupItem(Item::CreateValue("FPS", Item::Text, false));
	// �|�[�Y
	pDrawGroup->AddGroupItem(Item::CreateValue("Pause", Item::Bool, false, true));
	// �ő�FPS
	pDrawGroup->AddGroupItem(Item::CreateValue("MaxFPS", Item::Float, false));

	WIN_BASIC_SETTING.AddItem(pDrawGroup);

	WIN_BASIC_SETTING["Draw"]["Pause"].SetBool(false);
	WIN_BASIC_SETTING["Draw"]["MaxFPS"].SetFloat(WindowConfig::REFRESH_RATE);

}

/* ========================================
	�E�B���h�E������(�J�������)�֐�
	-------------------------------------
	���e�F�J�������̏��������s��
=========================================== */
void InitCameraInfo()
{
	WIN_CAMERA_INFO.AddItem(Item::CreateValue("ActiveCamera", Item::Kind::Text));	// �A�N�e�B�u�J������

	WIN_CAMERA_INFO.AddItem(Item::CreateValue("Orthographic", Item::Kind::Bool));	// ���s���e���ǂ���

	WIN_CAMERA_INFO.AddItem(Item::CreateList("CameraList", [](const void* arg)		// �J�������X�g
	{
		// �N���b�N���ꂽ�J�������A�N�e�B�u�ɂ���
		std::string sCameraName = reinterpret_cast<const char*>(arg);				// ���X�g���ږ�
		int nCameraNum = WIN_CAMERA_INFO["CameraList"].GetListNo(sCameraName.c_str());	// �J�����ԍ����擾

		CAMERA_MNG_INST.SwitchCamera(nCameraNum);	// �J�����؂�ւ�
	}, false, false, false, 3));

}

/* ========================================
	�E�B���h�E������(�V�[���ꗗ)�֐�
	-------------------------------------
	���e�F�V�[���ꗗ�̏��������s��
=========================================== */
void InitSceneList()
{
	// �V�[���ꗗ
	Item* pSceneList = Item::CreateList("SceneLists", [](const void* arg) 
	{
		// �I��������V�[���ύX
		std::string sSceneName = reinterpret_cast<const char*>(arg);	// ���X�g���ږ�
		SCENE_MAP.at(sSceneName)();	// �V�[���ύX
	}, true);

	// �V�[���������X�g�ɒǉ�
	for (auto& scene : SCENE_MAP)
	{
		pSceneList->AddListItem(scene.first.c_str());
	}

	WIN_SCENE_LIST.AddItem(pSceneList);
}

}

#endif // _DEBUG