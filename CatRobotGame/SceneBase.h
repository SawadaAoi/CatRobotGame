/* ========================================
	DX22Base/
	------------------------------------
	�V�[���p�w�b�_
	------------------------------------
	�����F�e�V�[���̊��N���X
	------------------------------------
	SceneBase.h
========================================== */
#pragma once

// =============== �C���N���[�h =====================
#include <vector>
#include "ObjectBase.h"
#include <memory>
#include "DebugMenu.h"
#include "UIObjectBase.h"

// =============== �O���錾 =======================
class ComponentCollisionBase;

// =============== �萔��` =======================
// E_State�̌Ăяo�����ȗ�
#define OBJ_ACTIVE	ObjectBase::E_State::STATE_ACTIVE
#define OBJ_DEAD	ObjectBase::E_State::STATE_DEAD
#define OBJ_PAUSE	ObjectBase::E_State::STATE_PAUSE

// E_State�̌Ăяo�����ȗ�(UI�I�u�W�F�N�g�p)
#define UI_ACTIVE	UIObjectBase::E_State::STATE_ACTIVE
#define UI_DEAD		UIObjectBase::E_State::STATE_DEAD
#define UI_PAUSE	UIObjectBase::E_State::STATE_PAUSE

// �V�[�����擾�֐��̒�`���ȗ����邽�߂̃}�N��
#define DEFINE_SCENE_TYPE(name)				\
	std::string GetSceneName() override {	\
		return #name;						\
	} 

// =============== �N���X��` =====================
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase() {};

	void Init();	// ����������
	void Uninit();	// �I������
	void Update();	// �X�V����
	void Draw();	// �`�揈��

	virtual void InitLocal() {};	// �ʏ���������
	virtual void UninitLocal() {};	// �ʏI������
	virtual void UpdateLocal() {};	// �ʍX�V����
	virtual void DrawLocal() {};	// �ʕ`�揈��

	void UpdateObject();
	void UpdateUI();

	// UI�`�揇���ёւ�
	void SortUIObjects();

	void RemoveDeadObjects();
	void RemoveDeadUIObjects();

	// �I�u�W�F�N�g�֘A
	template<typename T>
	T* AddSceneObject(std::string sName);	// �I�u�W�F�N�g�ǉ�
	template<typename T>
	T* GetSceneObject(std::string sName);	// �I�u�W�F�N�g�擾(���O�w��)
	template<typename T>
	T* GetSceneObject();					// �I�u�W�F�N�g�擾(�^����(�ŏ��Ɍ�����������))
	template<typename T>
	std::vector<T*> GetSceneObjects();		// �I�u�W�F�N�g�擾(�^����(�S��))

	void AddSceneObjectBase(ObjectBase* pObject);	// �I�u�W�F�N�g�ǉ�
	ObjectBase* FindSceneObject(std::string sName);	// �I�u�W�F�N�g����

	// UI�I�u�W�F�N�g�֘A
	template<typename T>
	T* AddSceneUI(std::string sName);	// UI�I�u�W�F�N�g�ǉ�
	template<typename T>
	T* GetSceneUI(std::string sName);	// UI�I�u�W�F�N�g�擾(���O�w��)
	template<typename T>
	T* GetSceneUI();					// UI�I�u�W�F�N�g�擾(�^����(�ŏ��Ɍ�����������))
	template<typename T>
	std::vector<T*> GetSceneUIs();		// UI�I�u�W�F�N�g�擾(�^����(�S��))

	void AddSceneUI(UIObjectBase* pUIObject);		// UI�I�u�W�F�N�g�ǉ�
	UIObjectBase* FindSceneUI(std::string sName);	// UI�I�u�W�F�N�g����


	// �Փ˔���֘A
	void AddObjectCollision(ComponentCollisionBase* pCollision);	// �Փ˔���R���|�[�l���g�ǉ�
	void RemoveObjectCollision(ComponentCollisionBase* pCollision);	// �Փ˔���R���|�[�l���g�폜

	// ���O�A�ԕt�^�֐�(�d���`�F�b�N)
	std::string CreateUniqueName(std::string sName);
	std::string CreateUniqueUIName(std::string sName);

	// �Q�b�^�[
	virtual std::string GetSceneName();								// �V�[�����擾
	std::vector<ObjectBase*> GetAllSceneObjects();					// �V�[����ɑ��݂���S�ẴI�u�W�F�N�g���擾
	std::vector<UIObjectBase*> GetAllSceneUIObjects();				// �V�[����ɑ��݂���S�Ă�UI�I�u�W�F�N�g���擾
	std::vector<ObjectBase*> GetSceneObjectsTag(E_ObjectTag tag);	// �^�O�ɑΉ�����I�u�W�F�N�g���擾
	ObjectBase* GetSceneObjectTag(E_ObjectTag tag);					// �^�O�ɑΉ�����I�u�W�F�N�g���擾(��ԍŏ��Ɍ�����������)

private:
	void UpdateCollision();	// �Փ˔���X�V�֐�
	bool CheckUniqueName(std::string sName, std::vector<ObjectBase*> pObjects);	// ���O�d���`�F�b�N
	bool CheckUniqueUIName(std::string sName, std::vector<UIObjectBase*> pUIs);	// ���O�d���`�F�b�N

#ifdef _DEBUG
	void InitObjectList();
	void InitObjectInfo(std::string sName);
	void InitUIList();
	void InitUIInfo(std::string sName);

	void ReloadDebugObjectList();	// �I�u�W�F�N�g���X�g�ēǂݍ���
	void AddObjectListChild(ObjectBase* pObject);
	void ReloadDebugUIList();		// UI�I�u�W�F�N�g���X�g�ēǂݍ���
	void AddUIListChild(UIObjectBase* pUIObject);

#endif // _DEBUG
protected:
	std::vector<std::unique_ptr<ObjectBase>>	m_pObjects;				// �V�[���ɏ�������I�u�W�F�N�g�ꗗ
	std::vector<std::unique_ptr<ObjectBase>>	m_pStandbyObjects;		// �I�u�W�F�N�g���ꎞ�I�ɕۑ����Ă����z��
	std::vector<ComponentCollisionBase*>		m_pObjectCollision;		// �e�I�u�W�F�N�g�����Փ˔���R���|�[�l���g

	std::vector<std::unique_ptr<UIObjectBase>>	m_pUIObjects;			// �V�[���ɏ�������UI�I�u�W�F�N�g�ꗗ
	std::vector<std::unique_ptr<UIObjectBase>>	m_pStandbyUIObjects;	// UI�I�u�W�F�N�g���ꎞ�I�ɕۑ����Ă����z��

	bool m_bIsUpdating;	// �X�V�����ǂ���
	bool m_bIsUpdatingUI;	// UI�X�V�����ǂ���

#ifdef _DEBUG
	ObjectBase*		m_pSelectObj;			// �ꗗ�őI�𒆂̃I�u�W�F�N�g
	int				m_nObjectListSelectNo;	// �I�u�W�F�N�g���X�g�̔ԍ�
	UIObjectBase*	m_pSelectUI;			// �ꗗ�őI�𒆂�UI�I�u�W�F�N�g
	int				m_nUISelectNo;			// UI�I�u�W�F�N�g���X�g�̔ԍ�
#endif // _DEBUG
};

#include "SceneBase.inl"