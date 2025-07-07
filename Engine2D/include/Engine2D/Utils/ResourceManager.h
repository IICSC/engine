#pragma once

#include <string>
#include <unordered_map>
#include <memory>

namespace Engine2D {

// 前向声明
class Sprite;
class SpriteSheet;
class Sound;
class Music;
class Shader;

/**
 * @brief 资源管理器，负责加载和管理游戏资源
 */
class ResourceManager {
public:
    /**
     * @brief 构造函数
     */
    ResourceManager();
    ~ResourceManager();

    /**
     * @brief 初始化资源管理器
     * @return 是否成功初始化
     */
    bool initialize();

    /**
     * @brief 清理资源
     */
    void shutdown();

    /**
     * @brief 加载精灵
     * @param filepath 图像文件路径
     * @param name 精灵名称
     * @return 是否成功加载
     */
    bool loadSprite(const std::string& filepath, const std::string& name);

    /**
     * @brief 加载精灵表
     * @param filepath 图像文件路径
     * @param name 精灵表名称
     * @param frameWidth 帧宽度
     * @param frameHeight 帧高度
     * @param numFrames 帧数量
     * @return 是否成功加载
     */
    bool loadSpriteSheet(const std::string& filepath, const std::string& name, 
                        int frameWidth, int frameHeight, int numFrames);

    /**
     * @brief 加载音效
     * @param filepath 音效文件路径
     * @param name 音效名称
     * @return 是否成功加载
     */
    bool loadSound(const std::string& filepath, const std::string& name);

    /**
     * @brief 加载音乐
     * @param filepath 音乐文件路径
     * @param name 音乐名称
     * @return 是否成功加载
     */
    bool loadMusic(const std::string& filepath, const std::string& name);

    /**
     * @brief 加载着色器
     * @param vertexShaderPath 顶点着色器文件路径
     * @param fragmentShaderPath 片段着色器文件路径
     * @param name 着色器名称
     * @return 是否成功加载
     */
    bool loadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, 
                   const std::string& name);

    /**
     * @brief 获取精灵
     * @param name 精灵名称
     * @return 精灵指针，不存在则返回nullptr
     */
    Sprite* getSprite(const std::string& name) const;

    /**
     * @brief 获取精灵表
     * @param name 精灵表名称
     * @return 精灵表指针，不存在则返回nullptr
     */
    SpriteSheet* getSpriteSheet(const std::string& name) const;

    /**
     * @brief 获取音效
     * @param name 音效名称
     * @return 音效指针，不存在则返回nullptr
     */
    Sound* getSound(const std::string& name) const;

    /**
     * @brief 获取音乐
     * @param name 音乐名称
     * @return 音乐指针，不存在则返回nullptr
     */
    Music* getMusic(const std::string& name) const;

    /**
     * @brief 获取着色器
     * @param name 着色器名称
     * @return 着色器指针，不存在则返回nullptr
     */
    Shader* getShader(const std::string& name) const;

    /**
     * @brief 释放精灵
     * @param name 精灵名称
     * @return 是否成功释放
     */
    bool releaseSprite(const std::string& name);

    /**
     * @brief 释放精灵表
     * @param name 精灵表名称
     * @return 是否成功释放
     */
    bool releaseSpriteSheet(const std::string& name);

    /**
     * @brief 释放音效
     * @param name 音效名称
     * @return 是否成功释放
     */
    bool releaseSound(const std::string& name);

    /**
     * @brief 释放音乐
     * @param name 音乐名称
     * @return 是否成功释放
     */
    bool releaseMusic(const std::string& name);

    /**
     * @brief 释放着色器
     * @param name 着色器名称
     * @return 是否成功释放
     */
    bool releaseShader(const std::string& name);

    /**
     * @brief 释放所有资源
     */
    void releaseAll();

    /**
     * @brief 设置资源基础路径
     * @param path 基础路径
     */
    void setBasePath(const std::string& path);

    /**
     * @brief 获取资源基础路径
     * @return 基础路径
     */
    const std::string& getBasePath() const;

private:
    std::unordered_map<std::string, std::unique_ptr<Sprite>> m_sprites;          // 精灵映射表
    std::unordered_map<std::string, std::unique_ptr<SpriteSheet>> m_spriteSheets; // 精灵表映射表
    std::unordered_map<std::string, std::unique_ptr<Sound>> m_sounds;            // 音效映射表
    std::unordered_map<std::string, std::unique_ptr<Music>> m_music;             // 音乐映射表
    std::unordered_map<std::string, std::unique_ptr<Shader>> m_shaders;          // 着色器映射表
    std::string m_basePath;                                                      // 资源基础路径
};

} // namespace Engine2D 