#pragma once

// 核心系统
#include "Core/Engine.h"
#include "Core/GameObject.h"
#include "Core/Component.h"
#include "Core/Transform.h"
#include "Core/Scene.h"
#include "Core/SceneManager.h"

// 图形系统
#include "Graphics/Renderer.h"
#include "Graphics/Sprite.h"
#include "Graphics/SpriteSheet.h"
#include "Graphics/Animation.h"
#include "Graphics/Camera.h"

// 输入系统
#include "Input/InputManager.h"

// 物理系统
#include "Physics/PhysicsWorld.h"
#include "Physics/Collider.h"
#include "Physics/Rigidbody.h"

// 音频系统
#include "Audio/AudioManager.h"
#include "Audio/Sound.h"
#include "Audio/Music.h"

// 工具
#include "Utils/Timer.h"
#include "Utils/ResourceManager.h"
#include "Utils/Logger.h"

/**
 * Engine2D - 一个基于组件的2D游戏引擎
 * 
 * 设计理念：
 * 1. 组件式架构：游戏对象由多个组件组成，每个组件负责特定功能
 * 2. 易用性：提供简单直观的API，降低游戏开发的学习曲线
 * 3. 高性能：优化的渲染和物理系统，支持高效的游戏开发
 * 4. 模块化：各系统相对独立，可以根据需要选择使用哪些功能
 * 
 * 主要特性：
 * - 灵活的场景和游戏对象管理
 * - 高性能2D图形渲染
 * - 完整的物理系统，支持刚体动力学和碰撞检测
 * - 强大的输入系统，支持键盘、鼠标和触摸
 * - 音频系统，支持音效和音乐
 * - 资源管理系统，高效加载和管理游戏资源
 * 
 * 用法示例：
 * 
 * ```cpp
 * #include <Engine2D/Engine2D.h>
 * 
 * class Game {
 * public:
 *     bool initialize() {
 *         // 初始化引擎
 *         if (!Engine2D::Engine::getInstance().initialize("My Game", 800, 600)) {
 *             return false;
 *         }
 *         
 *         // 创建场景
 *         auto sceneManager = Engine2D::Engine::getInstance().getSceneManager();
 *         auto scene = sceneManager->createScene("MainScene");
 *         sceneManager->loadScene("MainScene");
 *         
 *         // 创建游戏对象
 *         auto player = scene->createGameObject("Player");
 *         
 *         // 添加组件
 *         auto sprite = player->addComponent<Engine2D::Sprite>();
 *         sprite->loadFromFile(Engine2D::Engine::getInstance().getRenderer()->getSDLRenderer(), "player.png");
 *         
 *         // 添加物理组件
 *         auto rigidbody = player->addComponent<Engine2D::Rigidbody>();
 *         auto collider = player->addComponent<Engine2D::BoxCollider>(32, 32);
 *         
 *         return true;
 *     }
 *     
 *     void run() {
 *         // 运行游戏
 *         Engine2D::Engine::getInstance().run();
 *     }
 * };
 * 
 * int main(int argc, char* argv[]) {
 *     Game game;
 *     if (game.initialize()) {
 *         game.run();
 *     }
 *     return 0;
 * }
 * ```
 */

namespace Engine2D {
    
/**
 * @brief 引擎版本信息
 */
struct Version {
    static constexpr int MAJOR = 0;
    static constexpr int MINOR = 1;
    static constexpr int PATCH = 0;
    
    static constexpr const char* STRING = "0.1.0";
};

} // namespace Engine2D 