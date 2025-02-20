/* ========================================
	DX22Base/
	------------------------------------
	�V�[���Ǘ��p�w�b�_
	------------------------------------
	�����F�e�V�[���̊Ǘ����s���N���X
	------------------------------------
	SceneManager.h
========================================== */
#pragma once

// =============== �C���N���[�h =====================
#include "SceneBase.h"
#include "UIObjectFade.h"
#include <unordered_map>
#include <functional>

// =============== �萔��` =======================
#define REGISTER_SCENE(className) SceneManager::RegisterScene(#className, []() { return std::make_unique<className>(); })

#define FADE_KIND_NORMAL			SceneManager::FADE_NORMAL
#define FADE_KIND_IRIS_OUT_CIRCLE	SceneManager::FADE_IRIS_OUT_CIRCLE
#define FADE_KIND_IRIS_OUT_TEXTURE	SceneManager::FADE_IRIS_OUT_TEXTURE

// =============== �O���錾 =======================
class UIObjectFade;

// =============== �N���X��` =====================
class SceneManager
{
public:
	using CreateSceneFunc = std::function<std::unique_ptr<SceneBase>()>;

	enum E_FadeKind
	{
		FADE_NORMAL,
		FADE_IRIS_OUT_CIRCLE,
		FADE_IRIS_OUT_TEXTURE,
	};
public:

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// ���ׂẴV�[���o�^
	static void RegisterAllScene();
	// �V�[���o�^
	static void RegisterScene(const std::string& sSceneName, CreateSceneFunc func);
	
	// �V�[���؂�ւ�
	static void ChangeScene(const std::string& sSceneName, float fFadeTime = 1.0f);	// �V�[���؂�ւ�

	// �V�[���ēǂݍ���
	static void ReloadScene(float fFadeTime = 1.0f);	// �V�[���ēǂݍ��݂��Ăяo��

	// �Q�b�^�[
	static SceneBase* GetScene();	// �V�[���擾
	static std::vector<std::string> GetSceneNameList();	// �V�[�������X�g�擾

	// �Z�b�^�[
	static void SetFadeInKind(E_FadeKind eFadeInKind);							// �t�F�[�h�C����ސݒ�
	static void SetFadeOutKind(E_FadeKind eFadeOutKind);						// �t�F�[�h�A�E�g��ސݒ�
	static void SetFadeKind(E_FadeKind eFadeInKind, E_FadeKind eFadeOutKind);	// �t�F�[�h��ސݒ�
	static void SetFadeTime(float fFadeTime);									// �t�F�[�h���Ԑݒ�

private:
	static void CommitSceneChange();	// �V�[���ύX���m�肷��
	static void InitFadeOut();			// �t�F�[�h�A�E�g������
	static void InitFadeIn();			// �t�F�[�h�C��������
	static void InitScene();			// �V�[��������
private:
	static inline std::unique_ptr<SceneBase> m_pScene = nullptr;	// std::unique_ptr�ɕύX

	static inline std::unordered_map<std::string, CreateSceneFunc> m_SceneMap;	// �V�[�������֐��}�b�v
	static inline std::string	m_sNextSceneName	= "";		// ���̃V�[����
	static inline bool			m_isSceneChange		= false;	// �V�[���؂�ւ��t���O

	static inline UIObjectFade* m_pFade = nullptr;
	static inline E_FadeKind	m_eFadeInKind	= FADE_NORMAL;
	static inline E_FadeKind	m_eFadeOutKind = FADE_NORMAL;
	static inline float			m_fFadeTime = 1.0f;
};

