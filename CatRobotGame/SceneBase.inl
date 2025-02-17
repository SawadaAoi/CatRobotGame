#include "SceneBase.h"
/* ========================================
	DX22Base/
	------------------------------------
	�I�u�W�F�N�g�pinl�t�@�C��
	------------------------------------
	��inl�t�@�C���̓w�b�_�t�@�C���ɋL�ڂ���Ă���̂Ɠ���
	�@�w�b�_�[�t�@�C���̏璷����h�����߂Ɏg�p
	------------------------------------
	ObjectBase.inl
========================================== */



/* ========================================
	�I�u�W�F�N�g�ǉ��֐�
	-------------------------------------
	���e�F�V�[���ɃI�u�W�F�N�g��ǉ�����
	-------------------------------------
	�����FsName	�I�u�W�F�N�g��
	-------------------------------------
	�ߒl�F�ǉ��I�u�W�F�N�g�|�C���^
========================================== */
template<typename T>
inline T* SceneBase::AddSceneObject(std::string sName)
{
	// ���N���X��ObjectBase�łȂ��ꍇ�̓G���[���o��
	if (std::is_base_of<ObjectBase, T>() == false)	return nullptr;

	// �I�u�W�F�N�g�쐬
	auto pObject = std::make_unique<T>(this);

	// ���O���d�����Ă���ꍇ�͘A�Ԃ�t����
	sName = CreateUniqueName(sName);

	// ����������(
	pObject->Init(sName);

	// �V�[�����X�V�����ǂ������`�F�b�N���܂�
	if (m_bIsUpdating)
	{
		// �ꎞ�ۑ��p�̔z��Ƀ��j�[�N�|�C���^���ړ����܂�
		m_pStandbyObjects.push_back(std::move(pObject));
	}
	else
	{
		// �V�[���̃I�u�W�F�N�g�z��Ƀ��j�[�N�|�C���^���ړ����܂�
		m_pObjects.push_back(std::move(pObject));
	}

	// �ǉ������I�u�W�F�N�g�̃|�C���^��Ԃ��܂�(�X�V���̏ꍇ�͈ꎞ�ۑ��p�z�񂩂�擾)
	return static_cast<T*>((m_bIsUpdating ? m_pStandbyObjects : m_pObjects).back().get());
}




/* ========================================
	�I�u�W�F�N�g�擾�֐�
	-------------------------------------
	���e�F�V�[���ɏ�������I�u�W�F�N�g���擾����
	-------------------------------------
	�����FsName	�I�u�W�F�N�g��
	-------------------------------------
	�ߒl�F�擾�I�u�W�F�N�g�|�C���^
========================================== */
template<typename T>
inline T* SceneBase::GetSceneObject(std::string sName)
{
	// ���N���X��ObjectBase�łȂ��ꍇ�̓G���[���o��
	if (std::is_base_of<ObjectBase, T>() == false)	return nullptr;

	// �w��̎�ނ̃I�u�W�F�N�g��S�Ď擾
	std::vector<T*> pObjectList = GetSceneObjects<T>();	

	// �V�[���ɏ�������I�u�W�F�N�g������
	for (const auto& pObject : pObjectList)
	{
		// �I�u�W�F�N�g������v������|�C���^��Ԃ�
		if (pObject->GetName() == sName)
		{
			return static_cast<T*>(pObject);
		}
	}

	return nullptr;	// ������Ȃ������ꍇ��nullptr��Ԃ�
}

/* ========================================
	�I�u�W�F�N�g�擾�֐�
	-------------------------------------
	���e�F�V�[���ɏ�������I�u�W�F�N�g���擾����
		�@����ԍŏ��Ɍ��������I�u�W�F�N�g���擾
	-------------------------------------
	�����F�擾�I�u�W�F�N�g�|�C���^
========================================== */
template<typename T>
inline T* SceneBase::GetSceneObject()
{
	// ���N���X��ObjectBase�łȂ��ꍇ�̓G���[���o��
	if (std::is_base_of<ObjectBase, T>() == false)	return nullptr;

		// �V�[���ɏ�������I�u�W�F�N�g������
	for (const auto& pObject : m_pObjects)
	{
		// �I�u�W�F�N�g�̌^����v������I�u�W�F�N�g�|�C���^��Ԃ�
		if (pObject->GetTypeID() == T::GetStaticTypeID())
		{
			return static_cast<T*>(pObject.get());
		}
	}

	return nullptr;	// ������Ȃ������ꍇ��nullptr��Ԃ�
}

/* ========================================
	�^�ʃI�u�W�F�N�g���W�֐�
	-------------------------------------
	���e�F�V�[���ɏ����������̕��̃I�u�W�F�N�g
		�@��S�Ď��W����
	-------------------------------------
	�ߒl�F�I�u�W�F�N�g�|�C���^�z��
========================================== */
template<typename T>
inline std::vector<T*> SceneBase::GetSceneObjects()
{
	// �擾�����I�u�W�F�N�g���i�[����z��
	std::vector<T*> objects;

	// ���N���X��ObjectBase�łȂ��ꍇ�̓G���[���o��
	if (std::is_base_of<ObjectBase, T>() == false)	return objects;

	// �V�[���ɏ�������I�u�W�F�N�g������
	for (const auto& pObject : m_pObjects)
	{
		// �I�u�W�F�N�g�̌^����v������z��ɒǉ�
		if (pObject->GetTypeID() == T::GetStaticTypeID())
		{
			objects.push_back(static_cast<T*>(pObject.get()));
		}
	}

	return objects;	// �擾�����I�u�W�F�N�g�̔z���Ԃ�
}

/* ========================================
	UI�I�u�W�F�N�g�ǉ��֐�
	-------------------------------------
	���e�F�V�[����UI�I�u�W�F�N�g��ǉ�����
	-------------------------------------
	�����FsName	�I�u�W�F�N�g��
	-------------------------------------
	�ߒl�F�ǉ�UI�I�u�W�F�N�g�|�C���^
========================================== */
template<typename T>
inline T* SceneBase::AddSceneUI(std::string sName)
{
	// ���N���X��UIObjectBase�łȂ��ꍇ�͒ǉ����Ȃ�
	if (std::is_base_of<UIObjectBase, T>::value == false)	return nullptr;

	// �I�u�W�F�N�g�쐬
	auto pUIObject = std::make_unique<T>(this);

	// ���O���d�����Ă���ꍇ�͘A�Ԃ�t����
	sName = CreateUniqueUIName(sName);

	// ����������(
	pUIObject->Init(sName);

	// �V�[�����X�V�����ǂ������`�F�b�N���܂�
	if (m_bIsUpdatingUI)
	{
		// �ꎞ�ۑ��p�̔z��Ƀ��j�[�N�|�C���^���ړ����܂�
		m_pStandbyUIObjects.push_back(std::move(pUIObject));
	}
	else
	{
		// �V�[����UI�I�u�W�F�N�g�z��Ƀ��j�[�N�|�C���^���ړ����܂�
		m_pUIObjects.push_back(std::move(pUIObject));
	}

	// �ǉ������I�u�W�F�N�g�̃|�C���^��Ԃ��܂�(�X�V���̏ꍇ�͈ꎞ�ۑ��p�z�񂩂�擾)
	return static_cast<T*>((m_bIsUpdatingUI ? m_pStandbyUIObjects : m_pUIObjects).back().get());
}

/* ========================================
	UI�I�u�W�F�N�g�擾�֐�
	-------------------------------------
	���e�F�V�[���ɏ�������UI�I�u�W�F�N�g���擾����
	-------------------------------------
	�����FsName	�I�u�W�F�N�g��
	-------------------------------------
	�ߒl�F�擾UI�I�u�W�F�N�g�|�C���^
========================================== */
template<typename T>
inline T* SceneBase::GetSceneUI(std::string sName)
{
	// ���N���X��UIObjectBase�łȂ��ꍇ�͒ǉ����Ȃ�
	if (std::is_base_of<UIObjectBase, T>::value == false)	return nullptr;

	// �w��̎�ނ̃I�u�W�F�N�g��S�Ď擾
	std::vector<T*> pUIObjectList = GetSceneUIs<T>();

	// �I�u�W�F�N�g������v�������̂�T��
	for (const auto& pUIObject : pUIObjectList)
	{
		// �I�u�W�F�N�g������v������|�C���^��Ԃ�
		if (pUIObject->GetName() == sName)
		{
			return static_cast<T*>(pUIObject);
		}
	}

	return nullptr;	// ������Ȃ������ꍇ��nullptr��Ԃ�
}

/* ========================================
	UI�I�u�W�F�N�g�擾�֐�
	-------------------------------------
	���e�F�V�[���ɏ�������UI�I�u�W�F�N�g���擾����
		�@����ԍŏ��Ɍ�������UI�I�u�W�F�N�g���擾
	-------------------------------------
	�ߒl�F�擾UI�I�u�W�F�N�g�|�C���^
========================================== */
template<typename T>
inline T* SceneBase::GetSceneUI()
{
	// ���N���X��UIObjectBase�łȂ��ꍇ�͒ǉ����Ȃ�
	if (std::is_base_of<UIObjectBase, T>::value == false)	return nullptr;

	// �V�[���ɏ�������I�u�W�F�N�g������
	for (const auto& pUIObject : m_pUIObjects)
	{
		// �I�u�W�F�N�g�̌^����v������I�u�W�F�N�g�|�C���^��Ԃ�
		if (pUIObject->GetTypeID() == T::GetStaticTypeID())
		{
			return static_cast<T*>(pUIObject.get());
		}
	}

	return nullptr;	// ������Ȃ������ꍇ��nullptr��Ԃ�
}

/* ========================================
	�^��UI�I�u�W�F�N�g���W�֐�
	-------------------------------------
	���e�F�V�[���ɏ����������̕���UI�I�u�W�F�N�g
		�@��S�Ď��W����
	-------------------------------------
	�ߒl�FUI�I�u�W�F�N�g�|�C���^�z��
========================================== */
template<typename T>
inline std::vector<T*> SceneBase::GetSceneUIs()
{
	// �擾�����I�u�W�F�N�g���i�[����z��
	std::vector<T*> pUIObjectList;

	// ���N���X��UIObjectBase�łȂ��ꍇ�͒ǉ����Ȃ�
	if (std::is_base_of<UIObjectBase, T>::value == false)	return pUIObjectList;

	// �V�[���ɏ�������I�u�W�F�N�g������
	for (const auto& pUIObject : m_pUIObjects)
	{
		// �I�u�W�F�N�g�̌^����v������z��ɒǉ�
		if (pUIObject->GetTypeID() == T::GetStaticTypeID())
		{
			pUIObjectList.push_back(static_cast<T*>(pUIObject.get()));
		}
	}

	return pUIObjectList;	// �擾�����I�u�W�F�N�g�̔z���Ԃ�
}

