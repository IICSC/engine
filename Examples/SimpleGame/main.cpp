#include "Engine2D/Engine2D.h"
#include <iostream>

// 玩家控制组件
class PlayerController : public Engine2D::Component {
public:
    PlayerController() : speed(200.0f) {}
    
    void initialize() override {
        // 获取输入管理器
        m_inputManager = Engine2D::Engine::getInstance().getInputManager();
    }
    
    void update(float deltaTime) override {
        if (!isActive() || !m_inputManager) {
            return;
        }
        
        // 获取移动方向
        Engine2D::Vector2 direction;
        if (m_inputManager->isKeyHeld(SDLK_w) || m_inputManager->isKeyHeld(SDLK_UP)) {
            direction.y -= 1.0f;
        }
        if (m_inputManager->isKeyHeld(SDLK_s) || m_inputManager->isKeyHeld(SDLK_DOWN)) {
            direction.y += 1.0f;
        }
        if (m_inputManager->isKeyHeld(SDLK_a) || m_inputManager->isKeyHeld(SDLK_LEFT)) {
            direction.x -= 1.0f;
        }
        if (m_inputManager->isKeyHeld(SDLK_d) || m_inputManager->isKeyHeld(SDLK_RIGHT)) {
            direction.x += 1.0f;
        }
        
        // 归一化方向，确保斜向移动不会更快
        if (direction.x != 0.0f || direction.y != 0.0f) {
            direction = direction.normalized();
        }
        
        // 应用移动
        auto rigidbody = getComponent<Engine2D::Rigidbody>();
        if (rigidbody) {
            rigidbody->setVelocity(direction * speed);
        } else {
            auto transform = getTransform();
            if (transform) {
                transform->translate(direction * speed * deltaTime);
            }
        }
    }
    
    float speed;  // 移动速度
    
private:
    Engine2D::InputManager* m_inputManager;
};

class SimpleGame {
public:
    bool initialize() {
        // 初始化引擎
        if (!Engine2D::Engine::getInstance().initialize("Simple Game - Engine2D Demo", 800, 600)) {
            std::cerr << "引擎初始化失败!" << std::endl;
            return false;
        }
        
        // 创建场景
        auto sceneManager = Engine2D::Engine::getInstance().getSceneManager();
        auto scene = sceneManager->createScene("GameScene");
        sceneManager->loadScene("GameScene");
        
        // 创建玩家对象
        auto player = scene->createGameObject("Player");
        player->getTransform()->setPosition(400.0f, 300.0f);
        
        // 添加红色方块作为玩家图形
        auto renderer = Engine2D::Engine::getInstance().getRenderer();
        
        // 添加物理组件
        auto rigidbody = player->addComponent<Engine2D::Rigidbody>();
        rigidbody->setBodyType(Engine2D::BodyType::DYNAMIC);
        rigidbody->setMass(1.0f);
        rigidbody->setLinearDamping(5.0f);  // 添加阻尼，使其停止移动
        
        auto collider = player->addComponent<Engine2D::BoxCollider>(50.0f, 50.0f);
        
        // 添加玩家控制器
        player->addComponent<PlayerController>();
        
        // 创建边界墙
        createWall(scene, 400.0f, 10.0f, 800.0f, 20.0f);  // 上墙
        createWall(scene, 400.0f, 590.0f, 800.0f, 20.0f); // 下墙
        createWall(scene, 10.0f, 300.0f, 20.0f, 600.0f);  // 左墙
        createWall(scene, 790.0f, 300.0f, 20.0f, 600.0f); // 右墙
        
        return true;
    }
    
    void run() {
        // 运行游戏主循环
        Engine2D::Engine::getInstance().run();
    }
    
private:
    // 创建静态墙体
    Engine2D::GameObject* createWall(Engine2D::Scene* scene, float x, float y, float width, float height) {
        auto wall = scene->createGameObject("Wall");
        wall->getTransform()->setPosition(x, y);
        
        auto rigidbody = wall->addComponent<Engine2D::Rigidbody>();
        rigidbody->setBodyType(Engine2D::BodyType::STATIC);
        
        auto collider = wall->addComponent<Engine2D::BoxCollider>(width, height);
        
        return wall;
    }
};

int main(int argc, char* argv[]) {
    SimpleGame game;
    if (game.initialize()) {
        game.run();
    }
    return 0;
} 