/* ========================================
    DX22Base/
    ------------------------------------
    UI��ޓo�^�p�w�b�_
    ------------------------------------
    �����F�����񂩂�UI�𐶐����邽�߂̓o�^�N���X
    ------------------------------------
    UITypeRegistry.h
========================================== */
#pragma once

// =============== �C���N���[�h ===================
#include "UIObjectBase.h"
#include "SceneManager.h"


// =============== �萔��` =======================
#define UI_TYPE_REGISTRY_INST UITypeRegistry::GetInstance()    // �C���X�^���X�擾�p�}�N��
#define REGISTER_UI_TYPE(className)                                             \
    UITypeRegistry::GetInstance().Register(#className,                          \
        []() -> UIObjectBase* { return new className(SceneManager::GetScene()); })    \

// =============== �N���X��` ===================
class UITypeRegistry
{
public:
    using CreateFunction = UIObjectBase* ();                            // �֐��|�C���^�̌^���`
public:
    static UITypeRegistry& GetInstance();
    void Register(const std::string& sClassName, CreateFunction* func); // �}�b�v(������E�N���X�����֐�)�ɓo�^
    UIObjectBase* CreateUI(const std::string& sClassName);              // UI����

    static void RegisterAllUITypes();                                   // UI�̓o�^���s���֐�

    // �Q�b�^�[
    std::unordered_map<std::string, CreateFunction*>& GetUITypeMap();
private:
    // ������ƃN���X�����֐��̃}�b�v
    std::unordered_map<std::string, CreateFunction*> m_UITypeMap;

};

