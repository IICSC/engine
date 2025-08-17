#include "Engine2D/Core/Engine.h"
#include "Engine2D/Core/SceneManager.h"
#include "Engine2D/Graphics/Renderer.h"
#include "Engine2D/Input/InputManager.h"
#include "Engine2D/Physics/PhysicsWorld.h"
#include "Engine2D/Audio/AudioManager.h"
#include "Engine2D/Utils/ResourceManager.h"
#include "Engine2D/Utils/Timer.h"
#include "Engine2D/Utils/Logger.h"
#include "Engine2D/Utils/Exception.h"
#include <SDL.h>

namespace Engine2D {

// 单例实例
Engine& Engine::getInstance() {
    static Engine instance;
    return instance;
}

Engine::Engine() 
    : m_running(false)
    , m_fps(0.0f)
    , m_frameCount(0)
    , m_frameTime(0.0f) {
}

Engine::~Engine() {
    shutdown();
}

bool Engine::initialize(const std::string& title, int width, int height, bool fullscreen) {
    try {
        // 初始化日志系统
        Logger::getInstance().initialize("engine.log", LogLevel::INFO);
        LOG_INFO("引擎初始化开始");
        
        // 初始化SDL
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
            throw InitializationException("SDL初始化失败: " + std::string(SDL_GetError()));
        }
        LOG_INFO("SDL初始化成功");

        // 创建并初始化子系统
        m_renderer = std::make_unique<Renderer>();
        if (!m_renderer->initialize(title, width, height, fullscreen)) {
            throw InitializationException("渲染器初始化失败");
        }
        LOG_INFO("渲染器初始化成功");

        m_inputManager = std::make_unique<InputManager>();
        m_inputManager->initialize();
        LOG_INFO("输入管理器初始化成功");

        m_physicsWorld = std::make_unique<PhysicsWorld>();
        m_physicsWorld->initialize();
        LOG_INFO("物理世界初始化成功");

        m_audioManager = std::make_unique<AudioManager>();
        if (!m_audioManager->initialize()) {
            LOG_WARN("音频系统初始化失败，继续执行");
        } else {
            LOG_INFO("音频管理器初始化成功");
        }

        m_resourceManager = std::make_unique<ResourceManager>();
        m_resourceManager->initialize();
        LOG_INFO("资源管理器初始化成功");

        m_sceneManager = std::make_unique<SceneManager>();
        m_sceneManager->initialize();
        LOG_INFO("场景管理器初始化成功");

        m_timer = std::make_unique<Timer>();
        m_timer->initialize();
        m_timer->setFrameRateCap(60); // 设置默认帧率上限为60FPS
        m_timer->start();
        LOG_INFO("定时器初始化成功");

        m_running = true;
        LOG_INFO("引擎初始化完成");
        return true;
    } catch (const EngineException& e) {
        LOG_FATAL("引擎初始化失败: " + std::string(e.what()));
        return false;
    } catch (const std::exception& e) {
        LOG_FATAL("未知错误: " + std::string(e.what()));
        return false;
    }
}

void Engine::run() {
    while (m_running) {
        m_timer->startFrame();

        // 处理输入
        processEvents();

        // 更新逻辑
        update();

        // 渲染
        render();

        // 计算帧率
        calculateFPS();

        // 限制帧率
        m_timer->delayFrame();
        m_timer->endFrame();
    }
}

void Engine::shutdown() {
    LOG_INFO("引擎关闭开始");
    m_running = false;

    // 按相反顺序关闭子系统
    if (m_sceneManager) {
        m_sceneManager->shutdown();
        LOG_INFO("场景管理器已关闭");
    }
    if (m_resourceManager) {
        m_resourceManager->shutdown();
        LOG_INFO("资源管理器已关闭");
    }
    if (m_audioManager) {
        m_audioManager->shutdown();
        LOG_INFO("音频管理器已关闭");
    }
    if (m_physicsWorld) {
        m_physicsWorld->shutdown();
        LOG_INFO("物理世界已关闭");
    }
    if (m_inputManager) {
        m_inputManager->shutdown();
        LOG_INFO("输入管理器已关闭");
    }
    if (m_renderer) {
        m_renderer->shutdown();
        LOG_INFO("渲染器已关闭");
    }

    // 退出SDL
    SDL_Quit();
    LOG_INFO("SDL已退出");
    
    // 关闭日志系统
    Logger::getInstance().shutdown();
}

void Engine::processEvents() {
    // 更新输入状态，如果返回false说明收到了退出事件
    if (!m_inputManager->update()) {
        setRunning(false);
    }
}

void Engine::update() {
    float deltaTime = m_timer->getDeltaTime();

    // 更新物理世界
    m_physicsWorld->update(deltaTime);

    // 更新场景中的所有游戏对象
    m_sceneManager->update(deltaTime);
}

void Engine::render() {
    // 清除屏幕
    m_renderer->clear();

    // 渲染当前场景
    m_sceneManager->render();

    // 呈现画面
    m_renderer->present();
}

void Engine::calculateFPS() {
    m_frameCount++;
    m_frameTime += m_timer->getDeltaTime();

    // 每秒更新一次FPS计数
    if (m_frameTime >= 1.0f) {
        m_fps = static_cast<float>(m_frameCount) / m_frameTime;
        m_frameCount = 0;
        m_frameTime = 0.0f;
    }
}

SceneManager* Engine::getSceneManager() const {
    return m_sceneManager.get();
}

Renderer* Engine::getRenderer() const {
    return m_renderer.get();
}

InputManager* Engine::getInputManager() const {
    return m_inputManager.get();
}

PhysicsWorld* Engine::getPhysicsWorld() const {
    return m_physicsWorld.get();
}

AudioManager* Engine::getAudioManager() const {
    return m_audioManager.get();
}

ResourceManager* Engine::getResourceManager() const {
    return m_resourceManager.get();
}

Timer* Engine::getTimer() const {
    return m_timer.get();
}

void Engine::setRunning(bool running) {
    m_running = running;
}

bool Engine::isRunning() const {
    return m_running;
}

float Engine::getFPS() const {
    return m_fps;
}

} // namespace Engine2D 