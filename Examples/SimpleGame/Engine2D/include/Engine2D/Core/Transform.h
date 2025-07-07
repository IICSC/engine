#pragma once

#include "Component.h"
#include <vector>
#include <memory>

namespace Engine2D {

/**
 * @brief 表示2D向量
 */
struct Vector2 {
    float x, y;

    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float x, float y) : x(x), y(y) {}

    // 向量加法
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    // 向量减法
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    // 向量乘以标量
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    // 向量除以标量
    Vector2 operator/(float scalar) const {
        return Vector2(x / scalar, y / scalar);
    }

    // 向量长度
    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    // 向量归一化
    Vector2 normalized() const {
        float mag = magnitude();
        if (mag > 0) {
            return Vector2(x / mag, y / mag);
        }
        return Vector2();
    }

    // 点积
    float dot(const Vector2& other) const {
        return x * other.x + y * other.y;
    }

    // 叉积（在2D中，叉积返回标量，表示两个向量所成平行四边形的面积）
    float cross(const Vector2& other) const {
        return x * other.y - y * other.x;
    }
};

/**
 * @brief Transform组件，负责处理游戏对象的位置、旋转和缩放
 * 
 * 每个GameObject必须且只能有一个Transform组件，负责控制对象的空间属性
 */
class Transform : public Component {
public:
    /**
     * @brief 构造函数
     */
    Transform();
    virtual ~Transform() override;

    /**
     * @brief 初始化Transform组件
     */
    virtual void initialize() override;

    /**
     * @brief 设置位置
     * @param position 新位置
     */
    void setPosition(const Vector2& position);

    /**
     * @brief 设置位置
     * @param x X坐标
     * @param y Y坐标
     */
    void setPosition(float x, float y);

    /**
     * @brief 获取位置
     * @return 当前位置
     */
    const Vector2& getPosition() const;

    /**
     * @brief 平移位置
     * @param translation 平移向量
     */
    void translate(const Vector2& translation);

    /**
     * @brief 平移位置
     * @param x X方向平移量
     * @param y Y方向平移量
     */
    void translate(float x, float y);

    /**
     * @brief 设置旋转角度（以弧度为单位）
     * @param rotation 旋转角度
     */
    void setRotation(float rotation);

    /**
     * @brief 获取旋转角度（以弧度为单位）
     * @return 当前旋转角度
     */
    float getRotation() const;

    /**
     * @brief 旋转（以弧度为单位）
     * @param angle 旋转角度
     */
    void rotate(float angle);

    /**
     * @brief 设置缩放
     * @param scale 新缩放
     */
    void setScale(const Vector2& scale);

    /**
     * @brief 设置缩放
     * @param x X方向缩放
     * @param y Y方向缩放
     */
    void setScale(float x, float y);

    /**
     * @brief 设置缩放（等比例）
     * @param scale 缩放因子
     */
    void setScale(float scale);

    /**
     * @brief 获取缩放
     * @return 当前缩放
     */
    const Vector2& getScale() const;

    /**
     * @brief 设置父Transform
     * @param parent 父Transform指针
     */
    void setParent(Transform* parent);

    /**
     * @brief 获取父Transform
     * @return 父Transform指针
     */
    Transform* getParent() const;

    /**
     * @brief 添加子Transform
     * @param child 子Transform指针
     */
    void addChild(Transform* child);

    /**
     * @brief 移除子Transform
     * @param child 子Transform指针
     * @return 是否成功移除
     */
    bool removeChild(Transform* child);

    /**
     * @brief 获取子Transform列表
     * @return 子Transform列表
     */
    const std::vector<Transform*>& getChildren() const;

    /**
     * @brief 获取本地位置（相对于父对象）
     * @return 本地位置
     */
    const Vector2& getLocalPosition() const;

    /**
     * @brief 设置本地位置（相对于父对象）
     * @param position 本地位置
     */
    void setLocalPosition(const Vector2& position);

    /**
     * @brief 获取本地旋转（相对于父对象）
     * @return 本地旋转
     */
    float getLocalRotation() const;

    /**
     * @brief 设置本地旋转（相对于父对象）
     * @param rotation 本地旋转
     */
    void setLocalRotation(float rotation);

    /**
     * @brief 获取本地缩放（相对于父对象）
     * @return 本地缩放
     */
    const Vector2& getLocalScale() const;

    /**
     * @brief 设置本地缩放（相对于父对象）
     * @param scale 本地缩放
     */
    void setLocalScale(const Vector2& scale);

    /**
     * @brief 获取向前方向（根据旋转角度）
     * @return 向前单位向量
     */
    Vector2 getForward() const;

    /**
     * @brief 获取右方向（根据旋转角度）
     * @return 向右单位向量
     */
    Vector2 getRight() const;

    /**
     * @brief 更新全局位置、旋转和缩放
     */
    void updateWorldTransform();

private:
    Vector2 m_localPosition;     // 本地位置
    float m_localRotation;       // 本地旋转
    Vector2 m_localScale;        // 本地缩放

    Vector2 m_worldPosition;     // 全局位置
    float m_worldRotation;       // 全局旋转
    Vector2 m_worldScale;        // 全局缩放

    Transform* m_parent;         // 父Transform
    std::vector<Transform*> m_children;  // 子Transform列表

    bool m_dirty;                // 是否需要更新世界变换
};

} // namespace Engine2D 