#pragma once

#include <cstdint>
#include <string>

namespace Engine2D {

/**
 * @brief 计时器类，用于测量时间和帧率
 */
class Timer {
public:
    /**
     * @brief 构造函数
     */
    Timer();
    ~Timer();

    /**
     * @brief 初始化计时器
     */
    void initialize();

    /**
     * @brief 开始新的帧
     */
    void startFrame();

    /**
     * @brief 结束当前帧
     */
    void endFrame();

    /**
     * @brief 开始计时
     */
    void start();

    /**
     * @brief 暂停计时
     */
    void pause();

    /**
     * @brief 恢复计时
     */
    void resume();

    /**
     * @brief 停止计时
     */
    void stop();

    /**
     * @brief 重置计时器
     */
    void reset();

    /**
     * @brief 获取自计时器启动以来的总时间（毫秒）
     * @return 总时间
     */
    uint32_t getTicks() const;

    /**
     * @brief 获取帧间隔时间（秒）
     * @return 帧间隔时间
     */
    float getDeltaTime() const;

    /**
     * @brief 获取帧间隔时间（毫秒）
     * @return 帧间隔时间
     */
    float getDeltaTimeMS() const;

    /**
     * @brief 获取当前帧率
     * @return 帧率
     */
    float getFPS() const;

    /**
     * @brief 获取帧数
     * @return 总帧数
     */
    uint64_t getFrameCount() const;

    /**
     * @brief 检查计时器是否正在运行
     * @return 是否正在运行
     */
    bool isRunning() const;

    /**
     * @brief 检查计时器是否已暂停
     * @return 是否已暂停
     */
    bool isPaused() const;

    /**
     * @brief 设置帧率上限
     * @param fps 帧率上限，0表示无限制
     */
    void setFrameRateCap(uint32_t fps);

    /**
     * @brief 获取帧率上限
     * @return 帧率上限
     */
    uint32_t getFrameRateCap() const;

    /**
     * @brief 根据帧率上限延迟当前帧
     */
    void delayFrame();

private:
    uint32_t m_startTicks;      // 计时器启动时间
    uint32_t m_pausedTicks;     // 暂停时间
    uint32_t m_frameStartTime;  // 帧开始时间
    uint32_t m_lastFrameTime;   // 上一帧时间
    uint32_t m_frameRateCap;    // 帧率上限
    
    float m_deltaTime;          // 帧间隔时间（秒）
    float m_fps;                // 当前帧率
    uint64_t m_frameCount;      // 总帧数
    
    bool m_running;             // 是否正在运行
    bool m_paused;              // 是否已暂停
};

} // namespace Engine2D 