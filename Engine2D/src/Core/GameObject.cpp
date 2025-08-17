#include "Engine2D/Core/GameObject.h"
#include "Engine2D/Core/Component.h"
#include "Engine2D/Core/Transform.h"
#include "Engine2D/Core/Scene.h"
#include "Engine2D/Utils/Logger.h"

namespace Engine2D {

GameObject::GameObject(const std::string& name)
    : m_name(name)
    , m_active(true)
    , m_scene(nullptr)
    , m_transform(nullptr) {
}

GameObject::~GameObject() {
    destroy();
}

void GameObject::initialize() {
    LOG_DEBUG("初始化游戏对象: " + m_name);
    
    // 确保有Transform组件
    if (!m_transform) {
        m_transform = addComponent<Transform>();
    }
    
    // 初始化所有组件
    for (auto& component : m_components) {
        if (component->isActive()) {
            component->initialize();
        }
    }
}

void GameObject::update(float deltaTime) {
    if (!m_active) return;
    
    // 更新所有组件
    for (auto& component : m_components) {
        if (component->isActive()) {
            component->update(deltaTime);
        }
    }
}

void GameObject::render() {
    if (!m_active) return;
    
    // 渲染所有组件
    for (auto& component : m_components) {
        if (component->isActive()) {
            component->render();
        }
    }
}

void GameObject::destroy() {
    LOG_DEBUG("销毁游戏对象: " + m_name);
    
    // 销毁所有组件
    for (auto& component : m_components) {
        component->destroy();
    }
    
    m_components.clear();
    m_componentMap.clear();
    m_transform = nullptr;
    m_active = false;
}

void GameObject::setName(const std::string& name) {
    m_name = name;
}

const std::string& GameObject::getName() const {
    return m_name;
}

void GameObject::setActive(bool active) {
    m_active = active;
}

bool GameObject::isActive() const {
    return m_active;
}

Transform* GameObject::getTransform() const {
    return m_transform;
}

void GameObject::setScene(Scene* scene) {
    m_scene = scene;
}

Scene* GameObject::getScene() const {
    return m_scene;
}

const std::vector<std::unique_ptr<Component>>& GameObject::getComponents() const {
    return m_components;
}

} // namespace Engine2D 