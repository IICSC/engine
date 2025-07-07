#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <SDL_mixer.h>

namespace Engine2D {

// 前向声明
class Sound;
class Music;

/**
 * @brief 音频管理器，负责管理音效和音乐
 */
class AudioManager {
public:
    /**
     * @brief 构造函数
     */
    AudioManager();
    ~AudioManager();

    /**
     * @brief 初始化音频系统
     * @param frequency 采样频率
     * @param channels 通道数
     * @param chunkSize 音效缓冲区大小
     * @return 是否成功初始化
     */
    bool initialize(int frequency = 44100, int channels = 2, int chunkSize = 1024);

    /**
     * @brief 清理资源
     */
    void shutdown();

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
     * @brief 播放音效
     * @param name 音效名称
     * @param loops 循环次数（-1为无限循环）
     * @param volume 音量（0-128）
     * @param pan 声道平衡（-1.0左侧到1.0右侧）
     * @return 音效播放的通道，失败则返回-1
     */
    int playSound(const std::string& name, int loops = 0, int volume = 128, float pan = 0.0f);

    /**
     * @brief 播放音乐
     * @param name 音乐名称
     * @param loops 循环次数（-1为无限循环）
     * @param volume 音量（0-128）
     * @return 是否成功播放
     */
    bool playMusic(const std::string& name, int loops = -1, int volume = 128);

    /**
     * @brief 暂停音效
     * @param channel 通道号，-1暂停所有通道
     */
    void pauseSound(int channel = -1);

    /**
     * @brief 恢复音效
     * @param channel 通道号，-1恢复所有通道
     */
    void resumeSound(int channel = -1);

    /**
     * @brief 停止音效
     * @param channel 通道号，-1停止所有通道
     */
    void stopSound(int channel = -1);

    /**
     * @brief 暂停音乐
     */
    void pauseMusic();

    /**
     * @brief 恢复音乐
     */
    void resumeMusic();

    /**
     * @brief 停止音乐
     */
    void stopMusic();

    /**
     * @brief 设置音效音量
     * @param volume 音量（0-128）
     * @param channel 通道号，-1设置所有通道
     */
    void setSoundVolume(int volume, int channel = -1);

    /**
     * @brief 设置音乐音量
     * @param volume 音量（0-128）
     */
    void setMusicVolume(int volume);

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
     * @brief 释放所有音频资源
     */
    void releaseAll();

    /**
     * @brief 检查是否有音乐正在播放
     * @return 是否有音乐正在播放
     */
    bool isMusicPlaying() const;

    /**
     * @brief 检查指定通道是否正在播放音效
     * @param channel 通道号
     * @return 是否正在播放
     */
    bool isChannelPlaying(int channel) const;

    /**
     * @brief 设置主音量
     * @param volume 音量（0.0-1.0）
     */
    void setMasterVolume(float volume);

    /**
     * @brief 获取主音量
     * @return 主音量
     */
    float getMasterVolume() const;

    /**
     * @brief 设置音效主音量
     * @param volume 音量（0.0-1.0）
     */
    void setSoundMasterVolume(float volume);

    /**
     * @brief 获取音效主音量
     * @return 音效主音量
     */
    float getSoundMasterVolume() const;

    /**
     * @brief 设置音乐主音量
     * @param volume 音量（0.0-1.0）
     */
    void setMusicMasterVolume(float volume);

    /**
     * @brief 获取音乐主音量
     * @return 音乐主音量
     */
    float getMusicMasterVolume() const;

    /**
     * @brief 启用/禁用音频
     * @param enabled 是否启用
     */
    void setEnabled(bool enabled);

    /**
     * @brief 检查音频是否启用
     * @return 是否启用
     */
    bool isEnabled() const;

private:
    std::unordered_map<std::string, std::unique_ptr<Sound>> m_sounds;  // 音效映射表
    std::unordered_map<std::string, std::unique_ptr<Music>> m_music;   // 音乐映射表
    float m_masterVolume;        // 主音量
    float m_soundMasterVolume;   // 音效主音量
    float m_musicMasterVolume;   // 音乐主音量
    bool m_enabled;              // 是否启用
    bool m_initialized;          // 是否初始化
};

} // namespace Engine2D 