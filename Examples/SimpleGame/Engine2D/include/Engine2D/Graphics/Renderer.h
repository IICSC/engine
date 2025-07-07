#pragma once

#include <string>
#include <memory>
#include <vector>
#include <SDL.h>

namespace Engine2D {

// 前向声明
class Camera;
class Sprite;
class SpriteSheet;
class Animation;
struct Vector2;

/**
 * @brief 颜色结构体，表示RGBA颜色
 */
struct Color {
    uint8_t r, g, b, a;
    
    Color() : r(255), g(255), b(255), a(255) {}
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : r(r), g(g), b(b), a(a) {}
    
    static const Color WHITE;
    static const Color BLACK;
    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color YELLOW;
    static const Color CYAN;
    static const Color MAGENTA;
    static const Color TRANSPARENT;
};

/**
 * @brief 渲染器类，负责所有图形渲染
 * 
 * 封装SDL2渲染功能，提供高级渲染接口
 */
class Renderer {
public:
    /**
     * @brief 构造函数
     */
    Renderer();
    ~Renderer();
    
    /**
     * @brief 初始化渲染器
     * @param title 窗口标题
     * @param width 窗口宽度
     * @param height 窗口高度
     * @param fullscreen 是否全屏
     * @return 是否成功初始化
     */
    bool initialize(const std::string& title, int width, int height, bool fullscreen = false);
    
    /**
     * @brief 清理资源
     */
    void shutdown();
    
    /**
     * @brief 清除屏幕
     * @param color 清除颜色
     */
    void clear(const Color& color = Color::BLACK);
    
    /**
     * @brief 呈现画面
     */
    void present();
    
    /**
     * @brief 设置当前摄像机
     * @param camera 摄像机指针
     */
    void setCamera(Camera* camera);
    
    /**
     * @brief 获取当前摄像机
     * @return 摄像机指针
     */
    Camera* getCamera() const;
    
    /**
     * @brief 获取窗口宽度
     * @return 窗口宽度
     */
    int getWidth() const;
    
    /**
     * @brief 获取窗口高度
     * @return 窗口高度
     */
    int getHeight() const;
    
    /**
     * @brief 绘制精灵
     * @param sprite 精灵指针
     * @param position 位置
     * @param rotation 旋转角度（弧度）
     * @param scale 缩放
     * @param color 颜色调制
     */
    void drawSprite(Sprite* sprite, const Vector2& position, float rotation = 0.0f, 
                    const Vector2& scale = Vector2(1.0f, 1.0f), const Color& color = Color::WHITE);
    
    /**
     * @brief 绘制精灵表中的帧
     * @param spriteSheet 精灵表指针
     * @param frameIndex 帧索引
     * @param position 位置
     * @param rotation 旋转角度（弧度）
     * @param scale 缩放
     * @param color 颜色调制
     */
    void drawSpriteFrame(SpriteSheet* spriteSheet, int frameIndex, const Vector2& position, 
                        float rotation = 0.0f, const Vector2& scale = Vector2(1.0f, 1.0f), 
                        const Color& color = Color::WHITE);
    
    /**
     * @brief 绘制动画
     * @param animation 动画指针
     * @param position 位置
     * @param rotation 旋转角度（弧度）
     * @param scale 缩放
     * @param color 颜色调制
     */
    void drawAnimation(Animation* animation, const Vector2& position, float rotation = 0.0f, 
                        const Vector2& scale = Vector2(1.0f, 1.0f), const Color& color = Color::WHITE);
    
    /**
     * @brief 绘制矩形
     * @param x X坐标
     * @param y Y坐标
     * @param width 宽度
     * @param height 高度
     * @param color 颜色
     * @param filled 是否填充
     */
    void drawRect(float x, float y, float width, float height, const Color& color, bool filled = true);
    
    /**
     * @brief 绘制线条
     * @param x1 起点X坐标
     * @param y1 起点Y坐标
     * @param x2 终点X坐标
     * @param y2 终点Y坐标
     * @param color 颜色
     */
    void drawLine(float x1, float y1, float x2, float y2, const Color& color);
    
    /**
     * @brief 绘制圆形
     * @param x 中心X坐标
     * @param y 中心Y坐标
     * @param radius 半径
     * @param color 颜色
     * @param filled 是否填充
     */
    void drawCircle(float x, float y, float radius, const Color& color, bool filled = true);
    
    /**
     * @brief 获取SDL渲染器
     * @return SDL渲染器指针
     */
    SDL_Renderer* getSDLRenderer() const;
    
private:
    SDL_Window* m_window;         // SDL窗口
    SDL_Renderer* m_renderer;     // SDL渲染器
    Camera* m_camera;             // 当前摄像机
    int m_width;                  // 窗口宽度
    int m_height;                 // 窗口高度
    bool m_initialized;           // 是否已初始化
    
    // 将世界坐标转换为屏幕坐标
    Vector2 worldToScreen(const Vector2& worldPos) const;
};

} // namespace Engine2D 