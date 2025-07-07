#pragma once

#include <string>
#include <memory>
#include <SDL.h>

namespace Engine2D {

struct Color;

/**
 * @brief 精灵类，表示一个可渲染的图像
 */
class Sprite {
public:
    /**
     * @brief 构造函数
     */
    Sprite();
    ~Sprite();

    /**
     * @brief 从文件加载精灵
     * @param renderer SDL渲染器
     * @param filepath 图像文件路径
     * @return 是否成功加载
     */
    bool loadFromFile(SDL_Renderer* renderer, const std::string& filepath);

    /**
     * @brief 从表面创建精灵
     * @param renderer SDL渲染器
     * @param surface SDL表面
     * @return 是否成功创建
     */
    bool createFromSurface(SDL_Renderer* renderer, SDL_Surface* surface);

    /**
     * @brief 获取精灵宽度
     * @return 宽度
     */
    int getWidth() const;

    /**
     * @brief 获取精灵高度
     * @return 高度
     */
    int getHeight() const;

    /**
     * @brief 设置精灵的颜色调制
     * @param color 颜色
     */
    void setColor(const Color& color);

    /**
     * @brief 设置混合模式
     * @param blendMode 混合模式
     */
    void setBlendMode(SDL_BlendMode blendMode);

    /**
     * @brief 设置透明度
     * @param alpha 透明度值 (0-255)
     */
    void setAlpha(uint8_t alpha);

    /**
     * @brief 获取SDL纹理
     * @return SDL纹理指针
     */
    SDL_Texture* getTexture() const;

    /**
     * @brief 检查精灵是否有效
     * @return 是否有效
     */
    bool isValid() const;

    /**
     * @brief 设置精灵的源矩形（裁剪区域）
     * @param x X坐标
     * @param y Y坐标
     * @param width 宽度
     * @param height 高度
     */
    void setSourceRect(int x, int y, int width, int height);

    /**
     * @brief 重置源矩形为整个纹理
     */
    void resetSourceRect();

    /**
     * @brief 获取源矩形
     * @return 源矩形
     */
    const SDL_Rect& getSourceRect() const;

private:
    SDL_Texture* m_texture;  // 精灵纹理
    SDL_Rect m_sourceRect;   // 源矩形
    int m_width;             // 宽度
    int m_height;            // 高度
    bool m_valid;            // 是否有效

    // 释放纹理资源
    void free();
};

} // namespace Engine2D 