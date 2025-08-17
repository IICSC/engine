#include "Engine2D/Core/Transform.h"
#include "Engine2D/Utils/Logger.h"
#include <cmath>
#include <algorithm>

namespace Engine2D {

Transform::Transform()
    : m_localPosition(0.0f, 0.0f)
    , m_localRotation(0.0f)
    , m_localScale(1.0f, 1.0f)
    , m_worldPosition(0.0f, 0.0f)
    , m_worldRotation(0.0f)
    , m_worldScale(1.0f, 1.0f)
    , m_parent(nullptr)
    , m_dirty(true) {
    setName("Transform");
}

Transform::~Transform() {
    // 移除所有子对象
    while (!m_children.empty()) {
        removeChild(m_children.back());
    }
    
    // 从父对象中移除自己
    if (m_parent) {
        m_parent->removeChild(this);
    }
}

void Transform::initialize() {
    Component::initialize();
    updateWorldTransform();
}

void Transform::setPosition(const Vector2& position) {
    if (m_parent) {
        // 如果有父对象，计算本地位置
        Vector2 parentInverse = Vector2(-m_parent->getPosition().x, -m_parent->getPosition().y);
        m_localPosition = position + parentInverse;
    } else {
        m_localPosition = position;
    }
    m_dirty = true;
}

void Transform::setPosition(float x, float y) {
    setPosition(Vector2(x, y));
}

const Vector2& Transform::getPosition() const {
    if (m_dirty) {
        const_cast<Transform*>(this)->updateWorldTransform();
    }
    return m_worldPosition;
}

void Transform::translate(const Vector2& translation) {
    m_localPosition = m_localPosition + translation;
    m_dirty = true;
}

void Transform::translate(float x, float y) {
    translate(Vector2(x, y));
}

void Transform::setRotation(float rotation) {
    if (m_parent) {
        m_localRotation = rotation - m_parent->getRotation();
    } else {
        m_localRotation = rotation;
    }
    m_dirty = true;
}

float Transform::getRotation() const {
    if (m_dirty) {
        const_cast<Transform*>(this)->updateWorldTransform();
    }
    return m_worldRotation;
}

void Transform::rotate(float angle) {
    m_localRotation += angle;
    m_dirty = true;
}

void Transform::setScale(const Vector2& scale) {
    if (m_parent) {
        Vector2 parentScale = m_parent->getScale();
        m_localScale = Vector2(scale.x / parentScale.x, scale.y / parentScale.y);
    } else {
        m_localScale = scale;
    }
    m_dirty = true;
}

void Transform::setScale(float x, float y) {
    setScale(Vector2(x, y));
}

void Transform::setScale(float scale) {
    setScale(Vector2(scale, scale));
}

const Vector2& Transform::getScale() const {
    if (m_dirty) {
        const_cast<Transform*>(this)->updateWorldTransform();
    }
    return m_worldScale;
}

void Transform::setParent(Transform* parent) {
    if (m_parent == parent) {
        return;
    }

    // 从当前父对象中移除
    if (m_parent) {
        m_parent->removeChild(this);
    }

    m_parent = parent;

    // 添加到新父对象
    if (m_parent) {
        m_parent->addChild(this);
    }

    m_dirty = true;
}

Transform* Transform::getParent() const {
    return m_parent;
}

void Transform::addChild(Transform* child) {
    if (child && std::find(m_children.begin(), m_children.end(), child) == m_children.end()) {
        m_children.push_back(child);
        child->m_parent = this;
        child->m_dirty = true;
    }
}

bool Transform::removeChild(Transform* child) {
    auto it = std::find(m_children.begin(), m_children.end(), child);
    if (it != m_children.end()) {
        m_children.erase(it);
        child->m_parent = nullptr;
        child->m_dirty = true;
        return true;
    }
    return false;
}

const std::vector<Transform*>& Transform::getChildren() const {
    return m_children;
}

const Vector2& Transform::getLocalPosition() const {
    return m_localPosition;
}

void Transform::setLocalPosition(const Vector2& position) {
    m_localPosition = position;
    m_dirty = true;
}

float Transform::getLocalRotation() const {
    return m_localRotation;
}

void Transform::setLocalRotation(float rotation) {
    m_localRotation = rotation;
    m_dirty = true;
}

const Vector2& Transform::getLocalScale() const {
    return m_localScale;
}

void Transform::setLocalScale(const Vector2& scale) {
    m_localScale = scale;
    m_dirty = true;
}

Vector2 Transform::getForward() const {
    float rotation = getRotation();
    return Vector2(std::cos(rotation), std::sin(rotation));
}

Vector2 Transform::getRight() const {
    float rotation = getRotation();
    return Vector2(std::cos(rotation + M_PI/2), std::sin(rotation + M_PI/2));
}

void Transform::updateWorldTransform() {
    if (!m_dirty) {
        return;
    }

    if (m_parent) {
        // 计算全局变换
        Vector2 parentPos = m_parent->getPosition();
        float parentRot = m_parent->getRotation();
        Vector2 parentScale = m_parent->getScale();

        // 位置变换
        float cosRot = std::cos(parentRot);
        float sinRot = std::sin(parentRot);
        m_worldPosition.x = parentPos.x + (m_localPosition.x * cosRot - m_localPosition.y * sinRot) * parentScale.x;
        m_worldPosition.y = parentPos.y + (m_localPosition.x * sinRot + m_localPosition.y * cosRot) * parentScale.y;

        // 旋转变换
        m_worldRotation = parentRot + m_localRotation;

        // 缩放变换
        m_worldScale.x = parentScale.x * m_localScale.x;
        m_worldScale.y = parentScale.y * m_localScale.y;
    } else {
        // 没有父对象，本地变换就是全局变换
        m_worldPosition = m_localPosition;
        m_worldRotation = m_localRotation;
        m_worldScale = m_localScale;
    }

    m_dirty = false;

    // 标记所有子对象为脏状态
    for (auto child : m_children) {
        child->m_dirty = true;
    }
}

} // namespace Engine2D 