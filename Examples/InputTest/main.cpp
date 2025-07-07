#include <Engine2D/Engine2D.h>
#include <iostream>
#include <string>
#include <sstream>

// 输入测试组件
class InputTester : public Engine2D::Component {
public:
    InputTester() 
        : m_textTimeout(0.0f)
    {}
    
    void initialize() override {
        m_inputManager = Engine2D::Engine::getInstance().getInputManager();
        
        // 注册键盘回调
        m_inputManager->registerKeyCallback(SDLK_SPACE, Engine2D::KeyState::PRESSED, [this]() {
            displayMessage("空格键被按下!");
        });
        
        // 注册鼠标回调
        m_inputManager->registerMouseCallback(Engine2D::MouseButton::LEFT, Engine2D::KeyState::PRESSED, 
            [this](const Engine2D::Vector2& pos) {
                std::stringstream ss;
                ss << "鼠标左键点击在: (" << pos.x << ", " << pos.y << ")";
                displayMessage(ss.str());
            });
    }
    
    void update(float deltaTime) override {
        if (!m_inputManager) return;
        
        // 显示按键状态
        std::stringstream keysInfo;
        keysInfo << "按键状态: ";
        
        if (m_inputManager->isKeyHeld(SDLK_w) || m_inputManager->isKeyHeld(SDLK_UP)) {
            keysInfo << "W/上 ";
            moveObject(0.0f, -1.0f, deltaTime);
        }
        if (m_inputManager->isKeyHeld(SDLK_s) || m_inputManager->isKeyHeld(SDLK_DOWN)) {
            keysInfo << "S/下 ";
            moveObject(0.0f, 1.0f, deltaTime);
        }
        if (m_inputManager->isKeyHeld(SDLK_a) || m_inputManager->isKeyHeld(SDLK_LEFT)) {
            keysInfo << "A/左 ";
            moveObject(-1.0f, 0.0f, deltaTime);
        }
        if (m_inputManager->isKeyHeld(SDLK_d) || m_inputManager->isKeyHeld(SDLK_RIGHT)) {
            keysInfo << "D/右 ";
            moveObject(1.0f, 0.0f, deltaTime);
        }
        
        // 更新状态消息
        m_textTimeout -= deltaTime;
        if (m_textTimeout <= 0.0f) {
            m_statusMessage = keysInfo.str();
        }
    }
    
    const std::string& getStatusMessage() const {
        return m_statusMessage;
    }
    
private:
    Engine2D::InputManager* m_inputManager;
    std::string m_statusMessage;
    float m_textTimeout;
    
    void displayMessage(const std::string& message) {
        m_statusMessage = message;
        m_textTimeout = 2.0f; // 显示2秒
    }
    
    void moveObject(float x, float y, float deltaTime) {
        const float speed = 200.0f;
        getTransform()->translate(x * speed * deltaTime, y * speed * deltaTime);
    }
};

// 游戏类
class InputTestGame {
public:
    bool initialize() {
        // 初始化引擎
        if (!Engine2D::Engine::getInstance().initialize("Input Test - Engine2D Demo", 800, 600)) {
            std::cerr << "引擎初始化失败!" << std::endl;
            return false;
        }
        
        // 创建场景
        auto sceneManager = Engine2D::Engine::getInstance().getSceneManager();
        auto scene = sceneManager->createScene("InputTestScene");
        sceneManager->loadScene("InputTestScene");
        
        // 创建测试对象
        auto testObject = scene->createGameObject("TestObject");
        testObject->getTransform()->setPosition(400.0f, 300.0f);
        
        // 添加碰撞体让对象更容易看到
        testObject->addComponent<Engine2D::BoxCollider>(50.0f, 50.0f);
        
        // 添加输入测试组件
        m_inputTester = testObject->addComponent<InputTester>();
        
        return true;
    }
    
    void run() {
        Engine2D::Engine::getInstance().run();
    }
    
private:
    InputTester* m_inputTester;
};

int main(int argc, char* argv[]) {
    InputTestGame game;
    if (game.initialize()) {
        game.run();
    }
    return 0;
} 