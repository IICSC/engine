#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <type_traits>

namespace Engine2D {

class Component;
class Transform;
class Scene;

/**
 * @brief 游戏对象类，是场景中所有实体的基础
 * 
 * 游戏对象是组件的容器，采用组件式架构设计，每个游戏对象可以附加多个组件
 */
class GameObject {
public:
    /**
     * @brief 构造函数
     * @param name 游戏对象名称
     */
    explicit GameObject(const std::string& name = "GameObject");
    virtual ~GameObject();

    /**
     * @brief 初始化游戏对象
     */
    virtual void initialize();

    /**
     * @brief 更新游戏对象
     * @param deltaTime 帧间隔时间
     */
    virtual void update(float deltaTime);

    /**
     * @brief 渲染游戏对象
     */
    virtual void render();

    /**
     * @brief 销毁游戏对象
     */
    virtual void destroy();

    /**
     * @brief 添加组件
     * @tparam T 组件类型
     * @param args 组件构造参数
     * @return 组件指针
     */
    template<typename T, typename... Args>
    T* addComponent(Args&&... args);

    /**
     * @brief 获取组件
     * @tparam T 组件类型
     * @return 组件指针，如果不存在则返回nullptr
     */
    template<typename T>
    T* getComponent() const;

    /**
     * @brief 检查是否包含某类组件
     * @tparam T 组件类型
     * @return 是否包含该组件
     */
    template<typename T>
    bool hasComponent() const;

    /**
     * @brief 移除组件
     * @tparam T 组件类型
     * @return 是否成功移除
     */
    template<typename T>
    bool removeComponent();

    /**
     * @brief 设置游戏对象名称
     * @param name 新名称
     */
    void setName(const std::string& name);

    /**
     * @brief 获取游戏对象名称
     * @return 游戏对象名称
     */
    const std::string& getName() const;

    /**
     * @brief 设置游戏对象激活状态
     * @param active 是否激活
     */
    void setActive(bool active);

    /**
     * @brief 获取游戏对象激活状态
     * @return 是否激活
     */
    bool isActive() const;

    /**
     * @brief 获取Transform组件
     * @return Transform组件指针
     */
    Transform* getTransform() const;

    /**
     * @brief 设置所属场景
     * @param scene 场景指针
     */
    void setScene(Scene* scene);

    /**
     * @brief 获取所属场景
     * @return 场景指针
     */
    Scene* getScene() const;

    /**
     * @brief 获取所有组件
     * @return 组件列表的引用
     */
    const std::vector<std::unique_ptr<Component>>& getComponents() const;

private:
    std::string m_name;               // 游戏对象名称
    bool m_active;                    // 激活状态
    Scene* m_scene;                   // 所属场景
    Transform* m_transform;           // 变换组件
    std::vector<std::unique_ptr<Component>> m_components;  // 组件列表
    std::unordered_map<std::type_index, Component*> m_componentMap;  // 组件映射表
};

// 模板方法实现
template<typename T, typename... Args>
T* GameObject::addComponent(Args&&... args) {
    static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
    
    // 检查是否已存在该类型组件
    if (hasComponent<T>()) {
        return getComponent<T>();
    }
    
    // 创建组件
    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    T* componentPtr = component.get();
    
    // 设置组件所属的游戏对象
    componentPtr->setGameObject(this);
    
    // 初始化组件
    componentPtr->initialize();
    
    // 添加到映射表和列表
    m_componentMap[typeid(T)] = componentPtr;
    m_components.push_back(std::move(component));
    
    return componentPtr;
}

template<typename T>
T* GameObject::getComponent() const {
    static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
    
    auto it = m_componentMap.find(typeid(T));
    if (it != m_componentMap.end()) {
        return static_cast<T*>(it->second);
    }
    
    return nullptr;
}

template<typename T>
bool GameObject::hasComponent() const {
    static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
    return m_componentMap.find(typeid(T)) != m_componentMap.end();
}

template<typename T>
bool GameObject::removeComponent() {
    static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
    
    // 查找组件
    auto typeIt = m_componentMap.find(typeid(T));
    if (typeIt == m_componentMap.end()) {
        return false;
    }
    
    Component* componentToRemove = typeIt->second;
    
    // 从映射表中移除
    m_componentMap.erase(typeIt);
    
    // 从列表中移除
    for (auto it = m_components.begin(); it != m_components.end(); ++it) {
        if (it->get() == componentToRemove) {
            // 在移除前调用组件的销毁方法
            componentToRemove->destroy();
            m_components.erase(it);
            return true;
        }
    }
    
    return false;
}

} // namespace Engine2D 