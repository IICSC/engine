#include "Engine2D/Utils/Logger.h"
#include <iostream>
#include <algorithm>
#include <filesystem>

namespace Engine2D {

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::initialize(const std::string& logFile, LogLevel level) {
    std::lock_guard<std::mutex> lock(m_mutex);
    
    if (m_initialized) {
        return;
    }

    m_logLevel = level;
    m_initialized = true;

    if (!logFile.empty()) {
        m_logFile.open(logFile, std::ios::app);
        if (!m_logFile.is_open()) {
            std::cerr << "无法打开日志文件: " << logFile << std::endl;
        }
    }

    info("日志系统初始化完成");
}

void Logger::setLogLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_logLevel = level;
}

void Logger::log(LogLevel level, const std::string& message, const std::string& file, int line) {
    if (!m_initialized || level < m_logLevel) {
        return;
    }

    std::lock_guard<std::mutex> lock(m_mutex);

    std::stringstream ss;
    ss << getCurrentTimestamp() << " [" << getLogLevelString(level) << "] ";
    
    if (!file.empty()) {
        ss << "[" << getFileName(file) << ":" << line << "] ";
    }
    
    ss << message << std::endl;

    std::string logMessage = ss.str();

    // 输出到控制台
    if (level >= LogLevel::ERROR) {
        std::cerr << logMessage;
    } else {
        std::cout << logMessage;
    }

    // 输出到文件
    if (m_logFile.is_open()) {
        m_logFile << logMessage;
        m_logFile.flush();
    }
}

void Logger::trace(const std::string& message, const std::string& file, int line) {
    log(LogLevel::TRACE, message, file, line);
}

void Logger::debug(const std::string& message, const std::string& file, int line) {
    log(LogLevel::DEBUG, message, file, line);
}

void Logger::info(const std::string& message, const std::string& file, int line) {
    log(LogLevel::INFO, message, file, line);
}

void Logger::warn(const std::string& message, const std::string& file, int line) {
    log(LogLevel::WARN, message, file, line);
}

void Logger::error(const std::string& message, const std::string& file, int line) {
    log(LogLevel::ERROR, message, file, line);
}

void Logger::fatal(const std::string& message, const std::string& file, int line) {
    log(LogLevel::FATAL, message, file, line);
}

void Logger::shutdown() {
    std::lock_guard<std::mutex> lock(m_mutex);
    
    if (m_initialized) {
        info("日志系统关闭");
        if (m_logFile.is_open()) {
            m_logFile.close();
        }
        m_initialized = false;
    }
}

std::string Logger::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return ss.str();
}

std::string Logger::getLogLevelString(LogLevel level) {
    switch (level) {
        case LogLevel::TRACE: return "TRACE";
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO:  return "INFO ";
        case LogLevel::WARN:  return "WARN ";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::FATAL: return "FATAL";
        default: return "UNKNOWN";
    }
}

std::string Logger::getFileName(const std::string& path) {
    size_t pos = path.find_last_of("/\\");
    if (pos != std::string::npos) {
        return path.substr(pos + 1);
    }
    return path;
}

} // namespace Engine2D 