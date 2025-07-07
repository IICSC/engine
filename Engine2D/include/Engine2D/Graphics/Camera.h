#pragma once

#include "../Core/Component.h"
#include "../Core/Transform.h"

namespace Engine2D {

/**
 * @brief 相机组件，负责控制视口和渲染视角
 */
class Camera : public Component {
public:
    /**
     * @brief 构造函数
     */
    Camera();
    virtual ~Camera() override;

    /**
     * @brief 初始化相机
     */
    virtual void initialize() override;

    /**
     * @brief 更新相机
     * @param deltaTime 帧间隔时间
     */
    virtual void update(float deltaTime) override;

    /**
     * @brief 设置相机位置
     * @param position 新位置
     */
    void setPosition(const Vector2& position);

    /**
     * @brief 获取相机位置
     * @return 相机位置
     */
    const Vector2& getPosition() const;

    /**
     * @brief 设置相机旋转角度（弧度）
     * @param rotation 旋转角度
     */
    void setRotation(float rotation);

    /**
     * @brief 获取相机旋转角度（弧度）
     * @return 旋转角度
     */
    float getRotation() const;

    /**
     * @brief 设置相机缩放
     * @param zoom 缩放因子
     */
    void setZoom(float zoom);

    /**
     * @brief 获取相机缩放
     * @return 缩放因子
     */
    float getZoom() const;

    /**
     * @brief 设置视口大小
     * @param width 宽度
     * @param height 高度
     */
    void setViewport(int width, int height);

    /**
     * @brief 获取视口宽度
     * @return 视口宽度
     */
    int getViewportWidth() const;

    /**
     * @brief 获取视口高度
     * @return 视口高度
     */
    int getViewportHeight() const;

    /**
     * @brief 世界坐标转换为屏幕坐标
     * @param worldPos 世界坐标
     * @return 屏幕坐标
     */
    Vector2 worldToScreen(const Vector2& worldPos) const;

    /**
     * @brief 屏幕坐标转换为世界坐标
     * @param screenPos 屏幕坐标
     * @return 世界坐标
     */
    Vector2 screenToWorld(const Vector2& screenPos) const;

    /**
     * @brief 跟随目标
     * @param target 目标Transform
     * @param smoothing 平滑因子 (0-1)
     */
    void follow(Transform* target, float smoothing = 0.1f);

    /**
     * @brief 停止跟随
     */
    void stopFollowing();

    /**
     * @brief 设置是否使用平滑跟随
     * @param smooth 是否平滑
     */
    void setSmoothFollowing(bool smooth);

    /**
     * @brief 设置相机边界
     * @param left 左边界
     * @param right 右边界
     * @param top 上边界
     * @param bottom 下边界
     */
    void setBounds(float left, float right, float top, float bottom);

    /**
     * @brief 清除相机边界
     */
    void clearBounds();

private:
    Vector2 m_position;       // 相机位置
    float m_rotation;         // 相机旋转
    float m_zoom;             // 相机缩放
    int m_viewportWidth;      // 视口宽度
    int m_viewportHeight;     // 视口高度
    Transform* m_target;      // 跟随目标
    float m_followSmoothing;  // 跟随平滑因子
    bool m_smoothFollow;      // 是否平滑跟随
    
    bool m_hasBounds;         // 是否有边界限制
    float m_boundLeft;        // 左边界
    float m_boundRight;       // 右边界
    float m_boundTop;         // 上边界
    float m_boundBottom;      // 下边界
    
    // 应用边界限制
    void enforceBounds();
};

} // namespace Engine2D 