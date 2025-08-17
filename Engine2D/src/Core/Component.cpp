#include "Engine2D/Core/Component.h"
#include "Engine2D/Core/GameObject.h"
#include "Engine2D/Core/Transform.h"
#include "Engine2D/Utils/Logger.h"

namespace Engine2D {

Component::Component()
    : m_gameObject(nullptr)
    , m_name("Component")
    , m_active(true) {
}

Component::~Component() {
    destroy();
}

void Component::initialize() {
    LOG_DEBUG("组件初始化: " + m_name);
}

void Component::update(float deltaTime) {
    if (!m_active) return;
    // 基类默认不执行任何更新逻辑
}

void Component::render() {
    if (!m_active) return;
    // 基类默认不执行任何渲染逻辑
}

void Component::destroy() {
    LOG_DEBUG("组件销毁: " + m_name);
    m_active = false;
}

void Component::setGameObject(GameObject* gameObject) {
    m_gameObject = gameObject;
}

GameObject* Component::getGameObject() const {
    return m_gameObject;
}

Transform* Component::getTransform() const {
    if (m_gameObject) {
        return m_gameObject->getTransform();
    }
    return nullptr;
}

void Component::setName(const std::string& name) {
    m_name = name;
}

const std::string& Component::getName() const {
    return m_name;
}

void Component::setActive(bool active) {
    m_active = active;
}

bool Component::isActive() const {
    return m_active;
}

} // namespace Engine2D 