#pragma once

#include "../Core/Component.h"
#include "../Core/Transform.h"
#include <vector>
#include <functional>

namespace Engine2D {

class Rigidbody;
struct CollisionInfo;

/**
 * @brief 碰撞体类型枚举
 */
enum class ColliderType {
    BOX,      // 矩形碰撞体
    CIRCLE,   // 圆形碰撞体
    POLYGON   // 多边形碰撞体
};

/**
 * @brief 碰撞体基类，用于定义物体的形状用于碰撞检测
 */
class Collider : public Component {
public:
    /**
     * @brief 构造函数
     */
    Collider();
    virtual ~Collider() override;

    /**
     * @brief 初始化碰撞体
     */
    virtual void initialize() override;

    /**
     * @brief 更新碰撞体
     * @param deltaTime 帧间隔时间
     */
    virtual void update(float deltaTime) override;

    /**
     * @brief 获取碰撞体类型
     * @return 碰撞体类型
     */
    virtual ColliderType getType() const = 0;

    /**
     * @brief 设置碰撞体是否为触发器
     * @param isTrigger 是否为触发器
     */
    void setTrigger(bool isTrigger);

    /**
     * @brief A碰撞体是否为触发器
     * @return 是否为触发器
     */
    bool isTrigger() const;

    /**
     * @brief 获取中心点位置
     * @return 中心点世界坐标
     */
    Vector2 getCenter() const;

    /**
     * @brief 获取碰撞体的包围盒
     * @param min 左下角坐标
     * @param max 右上角坐标
     */
    virtual void getBoundingBox(Vector2& min, Vector2& max) const = 0;

    /**
     * @brief 设置偏移位置
     * @param offset 相对于游戏对象的偏移位置
     */
    void setOffset(const Vector2& offset);

    /**
     * @brief 获取偏移位置
     * @return 偏移位置
     */
    const Vector2& getOffset() const;

    /**
     * @brief 检查是否与另一个碰撞体碰撞
     * @param other 另一个碰撞体
     * @param info 碰撞信息输出
     * @return 是否碰撞
     */
    virtual bool checkCollision(Collider* other, CollisionInfo& info) const = 0;

    /**
     * @brief 绘制碰撞体（调试用）
     */
    virtual void debugDraw() const = 0;

    /**
     * @brief 设置碰撞层
     * @param layer 碰撞层
     */
    void setLayer(int layer);

    /**
     * @brief 获取碰撞层
     * @return 碰撞层
     */
    int getLayer() const;

    /**
     * @brief 检查是否与指定层碰撞
     * @param layer 要检查的层
     * @return 是否碰撞
     */
    bool collideWithLayer(int layer) const;

    /**
     * @brief 设置碰撞掩码（指定与哪些层碰撞）
     * @param mask 碰撞掩码
     */
    void setCollisionMask(uint32_t mask);

    /**
     * @brief 获取碰撞掩码
     * @return 碰撞掩码
     */
    uint32_t getCollisionMask() const;

    /**
     * @brief 获取关联的刚体
     * @return 刚体指针，如果没有则返回nullptr
     */
    Rigidbody* getRigidbody() const;

    /**
     * @brief 设置碰撞回调
     * @param callback 碰撞开始回调
     */
    void setOnCollisionEnter(std::function<void(Collider*)> callback);

    /**
     * @brief 设置碰撞持续回调
     * @param callback 碰撞持续回调
     */
    void setOnCollisionStay(std::function<void(Collider*)> callback);

    /**
     * @brief 设置碰撞结束回调
     * @param callback 碰撞结束回调
     */
    void setOnCollisionExit(std::function<void(Collider*)> callback);

    /**
     * @brief 设置触发器进入回调
     * @param callback 触发器进入回调
     */
    void setOnTriggerEnter(std::function<void(Collider*)> callback);

    /**
     * @brief 设置触发器持续回调
     * @param callback 触发器持续回调
     */
    void setOnTriggerStay(std::function<void(Collider*)> callback);

    /**
     * @brief 设置触发器退出回调
     * @param callback 触发器退出回调
     */
    void setOnTriggerExit(std::function<void(Collider*)> callback);

    /**
     * @brief 处理碰撞事件
     * @param other 另一个碰撞体
     * @param isEntering 是否刚开始碰撞
     */
    void handleCollision(Collider* other, bool isEntering);

    /**
     * @brief 处理触发器事件
     * @param other 另一个碰撞体
     * @param isEntering 是否刚进入触发器
     */
    void handleTrigger(Collider* other, bool isEntering);

private:
    Vector2 m_offset;                          // 相对于游戏对象的偏移位置
    bool m_isTrigger;                          // 是否为触发器
    int m_layer;                               // 碰撞层
    uint32_t m_collisionMask;                  // 碰撞掩码
    std::vector<Collider*> m_collidingWith;    // 当前正在碰撞的碰撞体列表

    // 回调函数
    std::function<void(Collider*)> m_onCollisionEnter;
    std::function<void(Collider*)> m_onCollisionStay;
    std::function<void(Collider*)> m_onCollisionExit;
    std::function<void(Collider*)> m_onTriggerEnter;
    std::function<void(Collider*)> m_onTriggerStay;
    std::function<void(Collider*)> m_onTriggerExit;
};

/**
 * @brief 矩形碰撞体
 */
class BoxCollider : public Collider {
public:
    /**
     * @brief 构造函数
     * @param width 宽度
     * @param height 高度
     */
    BoxCollider(float width = 1.0f, float height = 1.0f);
    virtual ~BoxCollider() override;

    /**
     * @brief 获取碰撞体类型
     * @return 矩形碰撞体类型
     */
    virtual ColliderType getType() const override;

    /**
     * @brief 设置宽度
     * @param width 宽度
     */
    void setWidth(float width);

    /**
     * @brief 获取宽度
     * @return 宽度
     */
    float getWidth() const;

    /**
     * @brief 设置高度
     * @param height 高度
     */
    void setHeight(float height);

    /**
     * @brief 获取高度
     * @return 高度
     */
    float getHeight() const;

    /**
     * @brief 设置大小
     * @param width 宽度
     * @param height 高度
     */
    void setSize(float width, float height);

    /**
     * @brief 获取包围盒
     * @param min 左下角坐标
     * @param max 右上角坐标
     */
    virtual void getBoundingBox(Vector2& min, Vector2& max) const override;

    /**
     * @brief 检查是否与另一个碰撞体碰撞
     * @param other 另一个碰撞体
     * @param info 碰撞信息输出
     * @return 是否碰撞
     */
    virtual bool checkCollision(Collider* other, CollisionInfo& info) const override;

    /**
     * @brief 绘制碰撞体（调试用）
     */
    virtual void debugDraw() const override;

private:
    float m_width;    // 宽度
    float m_height;   // 高度
};

/**
 * @brief 圆形碰撞体
 */
class CircleCollider : public Collider {
public:
    /**
     * @brief 构造函数
     * @param radius 半径
     */
    CircleCollider(float radius = 0.5f);
    virtual ~CircleCollider() override;

    /**
     * @brief 获取碰撞体类型
     * @return 圆形碰撞体类型
     */
    virtual ColliderType getType() const override;

    /**
     * @brief 设置半径
     * @param radius 半径
     */
    void setRadius(float radius);

    /**
     * @brief 获取半径
     * @return 半径
     */
    float getRadius() const;

    /**
     * @brief 获取包围盒
     * @param min 左下角坐标
     * @param max 右上角坐标
     */
    virtual void getBoundingBox(Vector2& min, Vector2& max) const override;

    /**
     * @brief 检查是否与另一个碰撞体碰撞
     * @param other 另一个碰撞体
     * @param info 碰撞信息输出
     * @return 是否碰撞
     */
    virtual bool checkCollision(Collider* other, CollisionInfo& info) const override;

    /**
     * @brief 绘制碰撞体（调试用）
     */
    virtual void debugDraw() const override;

private:
    float m_radius;  // 半径
};

} // namespace Engine2D 