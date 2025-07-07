#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace Engine2D {

class Scene;

/**
 * @brief 场景管理器，负责管理游戏中的所有场景
 */
class SceneManager {
public:
    /**
     * @brief 构造函数
     */
    SceneManager();
    ~SceneManager();

    /**
     * @brief 初始化场景管理器
     */
    void initialize();

    /**
     * @brief 更新当前活动场景
     * @param deltaTime 帧间隔时间
     */
    void update(float deltaTime);

    /**
     * @brief 渲染当前活动场景
     */
    void render();

    /**
     * @brief 清理资源
     */
    void shutdown();

    /**
     * @brief 创建新场景
     * @param name 场景名称
     * @return 场景指针
     */
    Scene* createScene(const std::string& name);

    /**
     * @brief 添加已创建的场景
     * @param scene 场景指针
     */
    void addScene(std::unique_ptr<Scene> scene);

    /**
     * @brief 根据名称获取场景
     * @param name 场景名称
     * @return 场景指针，不存在则返回nullptr
     */
    Scene* getScene(const std::string& name) const;

    /**
     * @brief 获取当前活动场景
     * @return 当前活动场景指针
     */
    Scene* getCurrentScene() const;

    /**
     * @brief 根据名称加载场景
     * @param name 场景名称
     * @return 是否成功加载
     */
    bool loadScene(const std::string& name);

    /**
     * @brief 卸载场景
     * @param name 场景名称
     * @return 是否成功卸载
     */
    bool unloadScene(const std::string& name);

    /**
     * @brief 获取所有场景
     * @return 场景列表
     */
    const std::vector<std::unique_ptr<Scene>>& getScenes() const;

private:
    std::vector<std::unique_ptr<Scene>> m_scenes;  // 场景列表
    std::unordered_map<std::string, Scene*> m_sceneMap;  // 场景映射表
    Scene* m_currentScene;  // 当前活动场景
};

} // namespace Engine2D 