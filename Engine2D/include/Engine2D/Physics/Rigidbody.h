#pragma once

#include "../Core/Component.h"
#include "../Core/Transform.h"

namespace Engine2D {

/**
 * @brief 刚体类型枚举
 */
enum class BodyType {
    STATIC,    // 静态刚体，不受物理影响
    DYNAMIC,   // 动态刚体，受重力和力的影响
    KINEMATIC  // 运动学刚体，不受重力影响但可手动设置速度
};

/**
 * @brief 刚体组件，负责物理模拟
 */
class Rigidbody : public Component {
public:
    /**
     * @brief 构造函数
     * @param type 刚体类型
     */
    Rigidbody(BodyType type = BodyType::DYNAMIC);
    virtual ~Rigidbody() override;

    /**
     * @brief 初始化刚体
     */
    virtual void initialize() override;

    /**
     * @brief 更新刚体
     * @param deltaTime 帧间隔时间
     */
    virtual void update(float deltaTime) override;

    /**
     * @brief 设置刚体类型
     * @param type 刚体类型
     */
    void setBodyType(BodyType type);

    /**
     * @brief 获取刚体类型
     * @return 刚体类型
     */
    BodyType getBodyType() const;

    /**
     * @brief 设置质量
     * @param mass 质量
     */
    void setMass(float mass);

    /**
     * @brief 获取质量
     * @return 质量
     */
    float getMass() const;

    /**
     * @brief 设置线性阻尼
     * @param damping 线性阻尼
     */
    void setLinearDamping(float damping);

    /**
     * @brief 获取线性阻尼
     * @return 线性阻尼
     */
    float getLinearDamping() const;

    /**
     * @brief 设置角阻尼
     * @param damping 角阻尼
     */
    void setAngularDamping(float damping);

    /**
     * @brief 获取角阻尼
     * @return 角阻尼
     */
    float getAngularDamping() const;

    /**
     * @brief 设置重力缩放
     * @param scale 重力缩放
     */
    void setGravityScale(float scale);

    /**
     * @brief 获取重力缩放
     * @return 重力缩放
     */
    float getGravityScale() const;

    /**
     * @brief 是否为固定旋转
     * @param fixed 是否固定旋转
     */
    void setFixedRotation(bool fixed);

    /**
     * @brief 检查是否固定旋转
     * @return 是否固定旋转
     */
    bool isFixedRotation() const;

    /**
     * @brief 设置线性速度
     * @param velocity 线性速度
     */
    void setVelocity(const Vector2& velocity);

    /**
     * @brief 获取线性速度
     * @return 线性速度
     */
    const Vector2& getVelocity() const;

    /**
     * @brief 设置角速度
     * @param angularVelocity 角速度
     */
    void setAngularVelocity(float angularVelocity);

    /**
     * @brief 获取角速度
     * @return 角速度
     */
    float getAngularVelocity() const;

    /**
     * @brief 应用力
     * @param force 力向量
     * @param point 作用点（世界坐标）
     */
    void applyForce(const Vector2& force, const Vector2& point = Vector2());

    /**
     * @brief 应用冲量
     * @param impulse 冲量向量
     * @param point 作用点（世界坐标）
     */
    void applyImpulse(const Vector2& impulse, const Vector2& point = Vector2());

    /**
     * @brief 应用扭矩
     * @param torque 扭矩
     */
    void applyTorque(float torque);

    /**
     * @brief 应用角冲量
     * @param impulse 角冲量
     */
    void applyAngularImpulse(float impulse);

    /**
     * @brief 设置是否受重力影响
     * @param affected 是否受重力影响
     */
    void setAffectedByGravity(bool affected);

    /**
     * @brief 检查是否受重力影响
     * @return 是否受重力影响
     */
    bool isAffectedByGravity() const;

    /**
     * @brief 设置摩擦系数
     * @param friction 摩擦系数
     */
    void setFriction(float friction);

    /**
     * @brief 获取摩擦系数
     * @return 摩擦系数
     */
    float getFriction() const;

    /**
     * @brief 设置弹性系数
     * @param restitution 弹性系数
     */
    void setRestitution(float restitution);

    /**
     * @brief 获取弹性系数
     * @return 弹性系数
     */
    float getRestitution() const;

    /**
     * @brief 设置是否使用连续碰撞检测
     * @param use 是否使用
     */
    void setUseCCD(bool use);

    /**
     * @brief 检查是否使用连续碰撞检测
     * @return 是否使用
     */
    bool usesCCD() const;

    /**
     * @brief 设置是否处于休眠状态
     * @param asleep 是否休眠
     */
    void setAsleep(bool asleep);

    /**
     * @brief 检查是否处于休眠状态
     * @return 是否休眠
     */
    bool isAsleep() const;

    /**
     * @brief 设置是否可以休眠
     * @param canSleep 是否可以休眠
     */
    void setCanSleep(bool canSleep);

    /**
     * @brief 检查是否可以休眠
     * @return 是否可以休眠
     */
    bool canSleep() const;

private:
    BodyType m_bodyType;            // 刚体类型
    float m_mass;                   // 质量
    float m_inverseMass;            // 质量倒数
    float m_inertia;                // 转动惯量
    float m_inverseInertia;         // 转动惯量倒数
    float m_linearDamping;          // 线性阻尼
    float m_angularDamping;         // 角阻尼
    float m_gravityScale;           // 重力缩放
    Vector2 m_velocity;             // 线性速度
    float m_angularVelocity;        // 角速度
    Vector2 m_force;                // 合力
    float m_torque;                 // 合扭矩
    bool m_fixedRotation;           // 是否固定旋转
    bool m_affectedByGravity;       // 是否受重力影响
    float m_friction;               // 摩擦系数
    float m_restitution;            // 弹性系数
    bool m_useCCD;                  // 是否使用连续碰撞检测
    bool m_asleep;                  // 是否休眠
    bool m_canSleep;                // 是否可以休眠

    // 重新计算质量属性
    void recalculateMassData();
};

} // namespace Engine2D 