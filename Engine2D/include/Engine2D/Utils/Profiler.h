#pragma once

#include <string>
#include <chrono>
#include <unordered_map>
#include <vector>
#include <memory>

namespace Engine2D {

/**
 * @brief 性能分析器类
 * 用于测量和记录代码执行时间
 */
class Profiler {
public:
    /**
     * @brief 获取性能分析器实例（单例模式）
     */
    static Profiler& getInstance();

    /**
     * @brief 开始计时
     * @param name 计时器名称
     */
    void beginFrame(const std::string& name = "Frame");

    /**
     * @brief 结束计时
     */
    void endFrame();

    /**
     * @brief 开始测量
     * @param name 测量名称
     */
    void begin(const std::string& name);

    /**
     * @brief 结束测量
     * @param name 测量名称
     */
    void end(const std::string& name);

    /**
     * @brief 获取测量结果
     * @param name 测量名称
     * @return 平均执行时间（毫秒）
     */
    float getAverageTime(const std::string& name) const;

    /**
     * @brief 获取最小执行时间
     * @param name 测量名称
     * @return 最小执行时间（毫秒）
     */
    float getMinTime(const std::string& name) const;

    /**
     * @brief 获取最大执行时间
     * @param name 测量名称
     * @return 最大执行时间（毫秒）
     */
    float getMaxTime(const std::string& name) const;

    /**
     * @brief 获取调用次数
     * @param name 测量名称
     * @return 调用次数
     */
    uint32_t getCallCount(const std::string& name) const;

    /**
     * @brief 重置所有测量数据
     */
    void reset();

    /**
     * @brief 输出性能报告
     * @param filename 输出文件名，为空则输出到控制台
     */
    void printReport(const std::string& filename = "") const;

    /**
     * @brief 关闭性能分析器
     */
    void shutdown();

private:
    Profiler() = default;
    ~Profiler() = default;
    Profiler(const Profiler&) = delete;
    Profiler& operator=(const Profiler&) = delete;

    struct ProfileData {
        std::chrono::high_resolution_clock::time_point startTime;
        std::vector<float> times;
        float minTime = std::numeric_limits<float>::max();
        float maxTime = 0.0f;
        float totalTime = 0.0f;
        uint32_t callCount = 0;
        bool isActive = false;
    };

    std::unordered_map<std::string, ProfileData> m_profiles;
    std::string m_currentFrame;
    bool m_initialized;
};

/**
 * @brief 自动性能测量类
 * 在构造时开始测量，析构时结束测量
 */
class ScopedProfiler {
public:
    ScopedProfiler(const std::string& name);
    ~ScopedProfiler();

private:
    std::string m_name;
};

} // namespace Engine2D

// 便捷宏定义
#define PROFILE_BEGIN(name) Engine2D::Profiler::getInstance().begin(name)
#define PROFILE_END(name) Engine2D::Profiler::getInstance().end(name)
#define PROFILE_SCOPE(name) Engine2D::ScopedProfiler profiler##__LINE__(name) 