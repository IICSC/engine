#pragma once

#include <string>

namespace Engine2D {

class GameObject;
class Transform;

/**
 * @brief 组件基类，所有组件都继承自此类
 * 
 * 组件是游戏对象功能的基本单位，每个组件负责特定的功能
 */
class Component {
public:
    /**
     * @brief 构造函数
     */
    Component();
    virtual ~Component();

    /**
     * @brief 初始化组件
     */
    virtual void initialize();

    /**
     * @brief 更新组件
     * @param deltaTime 帧间隔时间
     */
    virtual void update(float deltaTime);

    /**
     * @brief 渲染组件
     */
    virtual void render();

    /**
     * @brief 销毁组件
     */
    virtual void destroy();

    /**
     * @brief 设置组件所属的游戏对象
     * @param gameObject 游戏对象指针
     */
    void setGameObject(GameObject* gameObject);

    /**
     * @brief 获取组件所属的游戏对象
     * @return 游戏对象指针
     */
    GameObject* getGameObject() const;

    /**
     * @brief 获取游戏对象的Transform组件
     * @return Transform组件指针
     */
    Transform* getTransform() const;

    /**
     * @brief 设置组件名称
     * @param name 组件名称
     */
    void setName(const std::string& name);

    /**
     * @brief 获取组件名称
     * @return 组件名称
     */
    const std::string& getName() const;

    /**
     * @brief 设置组件激活状态
     * @param active 是否激活
     */
    void setActive(bool active);

    /**
     * @brief 获取组件激活状态
     * @return 是否激活
     */
    bool isActive() const;

protected:
    /**
     * @brief 获取指定类型的组件
     * @tparam T 组件类型
     * @return 组件指针
     */
    template<typename T>
    T* getComponent() const;

    /**
     * @brief 添加指定类型的组件
     * @tparam T 组件类型
     * @param args 组件构造参数
     * @return 组件指针
     */
    template<typename T, typename... Args>
    T* addComponent(Args&&... args);

private:
    GameObject* m_gameObject;  // 所属游戏对象
    std::string m_name;        // 组件名称
    bool m_active;             // 激活状态
};

// 模板方法实现
template<typename T>
T* Component::getComponent() const {
    if (m_gameObject) {
        return m_gameObject->getComponent<T>();
    }
    return nullptr;
}

template<typename T, typename... Args>
T* Component::addComponent(Args&&... args) {
    if (m_gameObject) {
        return m_gameObject->addComponent<T>(std::forward<Args>(args)...);
    }
    return nullptr;
}

} // namespace Engine2D 