#pragma once

#include <vector>
#include <memory>
#include <functional>
#include "../Core/Transform.h"

namespace Engine2D {

class Collider;
class Rigidbody;

/**
 * @brief 碰撞信息结构体
 */
struct CollisionInfo {
    Collider* colliderA;        // 第一个碰撞体
    Collider* colliderB;        // 第二个碰撞体
    Vector2 contactPoint;       // 碰撞点
    Vector2 normal;             // 碰撞法线
    float penetration;          // 穿透深度
    
    CollisionInfo() : colliderA(nullptr), colliderB(nullptr), penetration(0.0f) {}
};

/**
 * @brief 碰撞回调函数类型
 */
using CollisionCallback = std::function<void(const CollisionInfo&)>;

/**
 * @brief 物理世界类，负责模拟和处理物理
 */
class PhysicsWorld {
public:
    /**
     * @brief 构造函数
     */
    PhysicsWorld();
    ~PhysicsWorld();

    /**
     * @brief 初始化物理世界
     */
    void initialize();

    /**
     * @brief 更新物理世界
     * @param deltaTime 时间步长
     * @param iterations 求解迭代次数
     */
    void update(float deltaTime, int iterations = 6);

    /**
     * @brief 清理资源
     */
    void shutdown();

    /**
     * @brief 添加刚体
     * @param rigidbody 刚体指针
     */
    void addRigidbody(Rigidbody* rigidbody);

    /**
     * @brief 移除刚体
     * @param rigidbody 刚体指针
     * @return 是否成功移除
     */
    bool removeRigidbody(Rigidbody* rigidbody);

    /**
     * @brief 添加碰撞体
     * @param collider 碰撞体指针
     */
    void addCollider(Collider* collider);

    /**
     * @brief 移除碰撞体
     * @param collider 碰撞体指针
     * @return 是否成功移除
     */
    bool removeCollider(Collider* collider);

    /**
     * @brief 设置重力
     * @param gravity 重力向量
     */
    void setGravity(const Vector2& gravity);

    /**
     * @brief 获取重力
     * @return 重力向量
     */
    const Vector2& getGravity() const;

    /**
     * @brief 设置碰撞回调
     * @param callback 碰撞回调函数
     */
    void setCollisionCallback(const CollisionCallback& callback);

    /**
     * @brief 检查两个碰撞体是否碰撞
     * @param colliderA 第一个碰撞体
     * @param colliderB 第二个碰撞体
     * @param info 碰撞信息输出
     * @return 是否碰撞
     */
    bool checkCollision(Collider* colliderA, Collider* colliderB, CollisionInfo& info);

    /**
     * @brief 执行射线检测
     * @param origin 射线起点
     * @param direction 射线方向
     * @param maxDistance 最大检测距离
     * @param hitInfo 碰撞信息输出
     * @return 是否有碰撞
     */
    bool raycast(const Vector2& origin, const Vector2& direction, float maxDistance, CollisionInfo& hitInfo);

    /**
     * @brief 启用或禁用物理世界
     * @param enabled 是否启用
     */
    void setEnabled(bool enabled);

    /**
     * @brief 检查物理世界是否启用
     * @return 是否启用
     */
    bool isEnabled() const;

private:
    std::vector<Rigidbody*> m_rigidbodies;   // 刚体列表
    std::vector<Collider*> m_colliders;      // 碰撞体列表
    Vector2 m_gravity;                        // 重力
    bool m_enabled;                           // 是否启用
    CollisionCallback m_collisionCallback;    // 碰撞回调

    // 私有辅助方法
    void integrateForces(float deltaTime);    // 积分力
    void detectCollisions();                  // 检测碰撞
    void resolveCollisions();                 // 解决碰撞
    void integrateVelocities(float deltaTime); // 积分速度
};

} // namespace Engine2D 