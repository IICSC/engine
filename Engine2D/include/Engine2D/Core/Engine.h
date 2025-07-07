#pragma once

#include <memory>
#include <string>

// 前向声明
namespace Engine2D {
    class SceneManager;
    class Renderer;
    class InputManager;
    class PhysicsWorld;
    class AudioManager;
    class ResourceManager;
    class Timer;
}

namespace Engine2D {

/**
 * @brief 引擎主类，负责初始化和管理所有子系统
 */
class Engine {
public:
    /**
     * @brief 获取引擎实例（单例模式）
     * @return 引擎实例的引用
     */
    static Engine& getInstance();

    /**
     * @brief 初始化引擎及所有子系统
     * @param title 窗口标题
     * @param width 窗口宽度
     * @param height 窗口高度
     * @param fullscreen 是否全屏
     * @return 初始化是否成功
     */
    bool initialize(const std::string& title, int width, int height, bool fullscreen = false);

    /**
     * @brief 运行引擎主循环
     */
    void run();

    /**
     * @brief 清理引擎资源
     */
    void shutdown();

    /**
     * @brief 获取场景管理器
     * @return 场景管理器指针
     */
    SceneManager* getSceneManager() const;

    /**
     * @brief 获取渲染器
     * @return 渲染器指针
     */
    Renderer* getRenderer() const;

    /**
     * @brief 获取输入管理器
     * @return 输入管理器指针
     */
    InputManager* getInputManager() const;

    /**
     * @brief 获取物理世界
     * @return 物理世界指针
     */
    PhysicsWorld* getPhysicsWorld() const;

    /**
     * @brief 获取音频管理器
     * @return 音频管理器指针
     */
    AudioManager* getAudioManager() const;

    /**
     * @brief 获取资源管理器
     * @return 资源管理器指针
     */
    ResourceManager* getResourceManager() const;

    /**
     * @brief 获取定时器
     * @return 定时器指针
     */
    Timer* getTimer() const;

    /**
     * @brief 设置引擎是否运行
     * @param running 运行状态
     */
    void setRunning(bool running);

    /**
     * @brief 获取引擎是否运行
     * @return 运行状态
     */
    bool isRunning() const;

    /**
     * @brief 获取帧率
     * @return 当前帧率
     */
    float getFPS() const;

private:
    // 私有构造函数（单例模式）
    Engine();
    ~Engine();

    // 禁止拷贝和赋值（单例模式）
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    // 处理事件
    void processEvents();
    // 更新逻辑
    void update();
    // 渲染
    void render();
    // 计算帧率
    void calculateFPS();

    // 系统组件
    std::unique_ptr<SceneManager> m_sceneManager;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<InputManager> m_inputManager;
    std::unique_ptr<PhysicsWorld> m_physicsWorld;
    std::unique_ptr<AudioManager> m_audioManager;
    std::unique_ptr<ResourceManager> m_resourceManager;
    std::unique_ptr<Timer> m_timer;

    // 引擎状态
    bool m_running;
    float m_fps;
    uint32_t m_frameCount;
    float m_frameTime;
};

} // namespace Engine2D 