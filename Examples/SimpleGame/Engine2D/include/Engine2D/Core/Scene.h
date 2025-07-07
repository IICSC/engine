#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace Engine2D {

class GameObject;

/**
 * @brief 场景类，管理游戏对象的集合
 * 
 * 场景是游戏中的一个独立环境，包含多个游戏对象
 */
class Scene {
public:
    /**
     * @brief 构造函数
     * @param name 场景名称
     */
    explicit Scene(const std::string& name = "Scene");
    virtual ~Scene();

    /**
     * @brief 初始化场景
     */
    virtual void initialize();

    /**
     * @brief 更新场景中的所有游戏对象
     * @param deltaTime 帧间隔时间
     */
    virtual void update(float deltaTime);

    /**
     * @brief 渲染场景中的所有游戏对象
     */
    virtual void render();

    /**
     * @brief 销毁场景
     */
    virtual void destroy();

    /**
     * @brief 创建新的游戏对象
     * @param name 游戏对象名称
     * @return 创建的游戏对象指针
     */
    GameObject* createGameObject(const std::string& name = "GameObject");

    /**
     * @brief 根据名称查找游戏对象
     * @param name 游戏对象名称
     * @return 游戏对象指针，如果不存在则返回nullptr
     */
    GameObject* findGameObject(const std::string& name) const;

    /**
     * @brief 添加游戏对象到场景
     * @param gameObject 游戏对象指针
     */
    void addGameObject(std::unique_ptr<GameObject> gameObject);

    /**
     * @brief 移除游戏对象
     * @param gameObject 要移除的游戏对象
     * @return 是否成功移除
     */
    bool removeGameObject(GameObject* gameObject);

    /**
     * @brief 根据名称移除游戏对象
     * @param name 游戏对象名称
     * @return 是否成功移除
     */
    bool removeGameObject(const std::string& name);

    /**
     * @brief 获取场景中的所有游戏对象
     * @return 游戏对象列表
     */
    const std::vector<std::unique_ptr<GameObject>>& getGameObjects() const;

    /**
     * @brief 清空场景中的所有游戏对象
     */
    void clear();

    /**
     * @brief 设置场景名称
     * @param name 场景名称
     */
    void setName(const std::string& name);

    /**
     * @brief 获取场景名称
     * @return 场景名称
     */
    const std::string& getName() const;

    /**
     * @brief 设置场景是否激活
     * @param active 是否激活
     */
    void setActive(bool active);

    /**
     * @brief 获取场景是否激活
     * @return 是否激活
     */
    bool isActive() const;

private:
    std::string m_name;                               // 场景名称
    bool m_active;                                    // 是否激活
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;  // 游戏对象列表
    std::unordered_map<std::string, GameObject*> m_gameObjectMap;  // 游戏对象映射表（按名称索引）
};

} // namespace Engine2D 