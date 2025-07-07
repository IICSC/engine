#include <Engine2D/Engine2D.h>
#include <iostream>
#include <random>
#include <ctime>

// 方块生成器组件
class BlockSpawner : public Engine2D::Component {
public:
    BlockSpawner() 
        : m_spawnTimer(0.0f)
        , m_spawnInterval(1.0f)
        , m_blockSize(30.0f)
        , m_screenWidth(800.0f)
        , m_rng(static_cast<unsigned int>(time(nullptr)))
    {}
    
    void initialize() override {
        m_scene = getGameObject()->getScene();
    }
    
    void update(float deltaTime) override {
        // 定时生成新方块
        m_spawnTimer += deltaTime;
        if (m_spawnTimer >= m_spawnInterval) {
            spawnBlock();
            m_spawnTimer = 0.0f;
        }
    }
    
    void spawnBlock() {
        if (!m_scene) return;
        
        // 随机位置生成方块
        std::uniform_real_distribution<float> positionDist(m_blockSize, m_screenWidth - m_blockSize);
        std::uniform_real_distribution<float> colorDist(0.0f, 1.0f);
        
        auto block = m_scene->createGameObject("Block");
        
        // 随机位置
        float xPos = positionDist(m_rng);
        block->getTransform()->setPosition(xPos, 0.0f);
        
        // 添加物理组件
        auto rigidbody = block->addComponent<Engine2D::Rigidbody>();
        rigidbody->setBodyType(Engine2D::BodyType::DYNAMIC);
        rigidbody->setMass(1.0f);
        
        // 添加碰撞体
        block->addComponent<Engine2D::BoxCollider>(m_blockSize, m_blockSize);
        
        // 添加方块行为组件
        block->addComponent<BlockBehavior>();
    }
    
    void setSpawnInterval(float interval) {
        m_spawnInterval = interval;
    }
    
    void setBlockSize(float size) {
        m_blockSize = size;
    }
    
private:
    float m_spawnTimer;
    float m_spawnInterval;
    float m_blockSize;
    float m_screenWidth;
    Engine2D::Scene* m_scene;
    std::mt19937 m_rng;
};

// 方块行为组件
class BlockBehavior : public Engine2D::Component {
public:
    BlockBehavior() : m_lifetime(0.0f), m_maxLifetime(10.0f) {}
    
    void update(float deltaTime) override {
        // 方块生命周期
        m_lifetime += deltaTime;
        if (m_lifetime >= m_maxLifetime) {
            getGameObject()->destroy();
        }
        
        // 检查是否掉出屏幕
        const float bottomBoundary = 600.0f + 100.0f; // 屏幕高度 + 额外缓冲
        if (getTransform()->getPosition().y > bottomBoundary) {
            getGameObject()->destroy();
        }
    }
    
private:
    float m_lifetime;
    float m_maxLifetime;
};

// 游戏类
class FallingBlocksGame {
public:
    bool initialize() {
        // 初始化引擎
        if (!Engine2D::Engine::getInstance().initialize("Falling Blocks - Engine2D Demo", 800, 600)) {
            std::cerr << "引擎初始化失败!" << std::endl;
            return false;
        }
        
        // 配置物理世界 - 设置重力
        auto physicsWorld = Engine2D::Engine::getInstance().getPhysicsWorld();
        physicsWorld->setGravity(Engine2D::Vector2(0.0f, 9.8f * 10.0f)); // 加大重力效果
        
        // 创建游戏场景
        auto sceneManager = Engine2D::Engine::getInstance().getSceneManager();
        auto scene = sceneManager->createScene("GameScene");
        sceneManager->loadScene("GameScene");
        
        // 创建方块生成器
        auto spawner = scene->createGameObject("BlockSpawner");
        auto spawnerComponent = spawner->addComponent<BlockSpawner>();
        spawnerComponent->setSpawnInterval(0.5f); // 每0.5秒生成一个方块
        
        // 创建地面
        createGround(scene);
        
        // 创建左右边界墙
        createWall(scene, 0.0f, 300.0f, 20.0f, 600.0f); // 左墙
        createWall(scene, 800.0f, 300.0f, 20.0f, 600.0f); // 右墙
        
        return true;
    }
    
    void run() {
        Engine2D::Engine::getInstance().run();
    }
    
private:
    // 创建地面
    Engine2D::GameObject* createGround(Engine2D::Scene* scene) {
        auto ground = scene->createGameObject("Ground");
        ground->getTransform()->setPosition(400.0f, 580.0f);
        
        auto rigidbody = ground->addComponent<Engine2D::Rigidbody>();
        rigidbody->setBodyType(Engine2D::BodyType::STATIC);
        
        auto collider = ground->addComponent<Engine2D::BoxCollider>(800.0f, 40.0f);
        
        return ground;
    }
    
    // 创建墙体
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
    FallingBlocksGame game;
    if (game.initialize()) {
        game.run();
    }
    return 0;
} 