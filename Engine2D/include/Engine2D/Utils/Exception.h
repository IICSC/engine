#pragma once

#include <string>
#include <exception>
#include <stdexcept>

namespace Engine2D {

/**
 * @brief 引擎基础异常类
 */
class EngineException : public std::runtime_error {
public:
    explicit EngineException(const std::string& message) 
        : std::runtime_error(message) {}
    
    explicit EngineException(const char* message) 
        : std::runtime_error(message) {}
};

/**
 * @brief 初始化异常
 */
class InitializationException : public EngineException {
public:
    explicit InitializationException(const std::string& message) 
        : EngineException("初始化失败: " + message) {}
};

/**
 * @brief 资源加载异常
 */
class ResourceException : public EngineException {
public:
    explicit ResourceException(const std::string& message) 
        : EngineException("资源错误: " + message) {}
};

/**
 * @brief 渲染异常
 */
class RenderException : public EngineException {
public:
    explicit RenderException(const std::string& message) 
        : EngineException("渲染错误: " + message) {}
};

/**
 * @brief 音频异常
 */
class AudioException : public EngineException {
public:
    explicit AudioException(const std::string& message) 
        : EngineException("音频错误: " + message) {}
};

/**
 * @brief 物理异常
 */
class PhysicsException : public EngineException {
public:
    explicit PhysicsException(const std::string& message) 
        : EngineException("物理错误: " + message) {}
};

} // namespace Engine2D 