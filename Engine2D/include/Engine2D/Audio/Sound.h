#pragma once

#include <string>
#include <SDL_mixer.h>

namespace Engine2D {

/**
 * @brief 音效类，表示短音频片段
 */
class Sound {
public:
    /**
     * @brief 构造函数
     */
    Sound();
    ~Sound();

    /**
     * @brief 从文件加载音效
     * @param filepath 音效文件路径
     * @return 是否成功加载
     */
    bool loadFromFile(const std::string& filepath);

    /**
     * @brief 播放音效
     * @param loops 循环次数（-1为无限循环）
     * @param volume 音量（0-128）
     * @param pan 声道平衡（-1.0左侧到1.0右侧）
     * @return 分配的通道号，错误则返回-1
     */
    int play(int loops = 0, int volume = 128, float pan = 0.0f);

    /**
     * @brief 暂停音效
     * @param channel 通道号，-1暂停所有通道
     */
    void pause(int channel = -1);

    /**
     * @brief 恢复音效
     * @param channel 通道号，-1恢复所有通道
     */
    void resume(int channel = -1);

    /**
     * @brief 停止音效
     * @param channel 通道号，-1停止所有通道
     */
    void stop(int channel = -1);

    /**
     * @brief 检查音效是否正在播放
     * @param channel 通道号
     * @return 是否正在播放
     */
    bool isPlaying(int channel) const;

    /**
     * @brief 设置音量
     * @param volume 音量（0-128）
     * @param channel 通道号，-1设置音效的默认音量
     */
    void setVolume(int volume, int channel = -1);

    /**
     * @brief 设置声道平衡
     * @param pan 声道平衡（-1.0左侧到1.0右侧）
     * @param channel 通道号
     */
    void setPan(float pan, int channel);

    /**
     * @brief 获取音效时长（毫秒）
     * @return 时长
     */
    int getDuration() const;

    /**
     * @brief 检查音效是否有效
     * @return 是否有效
     */
    bool isValid() const;

    /**
     * @brief 获取原始的Mix_Chunk指针
     * @return Mix_Chunk指针
     */
    Mix_Chunk* getChunk() const;

    /**
     * @brief 释放资源
     */
    void free();

private:
    Mix_Chunk* m_chunk;      // 音效数据
    std::string m_filepath;  // 文件路径
    int m_defaultVolume;     // 默认音量
};

} // namespace Engine2D 