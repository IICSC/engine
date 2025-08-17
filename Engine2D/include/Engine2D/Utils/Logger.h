#pragma once

#include <string>
#include <memory>
#include <mutex>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>

namespace Engine2D {

/**
 * @brief 日志级别枚举
 */
enum class LogLevel {
    TRACE = 0,
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4,
    FATAL = 5
};

/**
 * @brief 日志系统类
 * 提供线程安全的日志记录功能
 */
class Logger {
public:
    /**
     * @brief 获取日志实例（单例模式）
     */
    static Logger& getInstance();

    /**
     * @brief 初始化日志系统
     * @param logFile 日志文件路径，如果为空则只输出到控制台
     * @param level 最小日志级别
     */
    void initialize(const std::string& logFile = "", LogLevel level = LogLevel::INFO);

    /**
     * @brief 设置日志级别
     */
    void setLogLevel(LogLevel level);

    /**
     * @brief 记录日志
     */
    void log(LogLevel level, const std::string& message, const std::string& file = "", int line = 0);

    /**
     * @brief 便捷日志方法
     */
    void trace(const std::string& message, const std::string& file = "", int line = 0);
    void debug(const std::string& message, const std::string& file = "", int line = 0);
    void info(const std::string& message, const std::string& file = "", int line = 0);
    void warn(const std::string& message, const std::string& file = "", int line = 0);
    void error(const std::string& message, const std::string& file = "", int line = 0);
    void fatal(const std::string& message, const std::string& file = "", int line = 0);

    /**
     * @brief 关闭日志系统
     */
    void shutdown();

private:
    Logger() = default;
    ~Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::string getCurrentTimestamp();
    std::string getLogLevelString(LogLevel level);
    std::string getFileName(const std::string& path);

    std::ofstream m_logFile;
    LogLevel m_logLevel;
    std::mutex m_mutex;
    bool m_initialized;
};

} // namespace Engine2D

// 便捷宏定义
#define LOG_TRACE(msg) Engine2D::Logger::getInstance().trace(msg, __FILE__, __LINE__)
#define LOG_DEBUG(msg) Engine2D::Logger::getInstance().debug(msg, __FILE__, __LINE__)
#define LOG_INFO(msg)  Engine2D::Logger::getInstance().info(msg, __FILE__, __LINE__)
#define LOG_WARN(msg)  Engine2D::Logger::getInstance().warn(msg, __FILE__, __LINE__)
#define LOG_ERROR(msg) Engine2D::Logger::getInstance().error(msg, __FILE__, __LINE__)
#define LOG_FATAL(msg) Engine2D::Logger::getInstance().fatal(msg, __FILE__, __LINE__) 