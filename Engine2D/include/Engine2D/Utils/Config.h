#pragma once

#include <string>
#include <unordered_map>
#include <variant>
#include <memory>
#include <fstream>

namespace Engine2D {

/**
 * @brief 配置值类型
 */
using ConfigValue = std::variant<bool, int, float, std::string>;

/**
 * @brief 配置管理器类
 * 负责管理引擎的配置参数
 */
class Config {
public:
    /**
     * @brief 获取配置实例（单例模式）
     */
    static Config& getInstance();

    /**
     * @brief 初始化配置系统
     * @param configFile 配置文件路径
     */
    void initialize(const std::string& configFile = "config.ini");

    /**
     * @brief 设置配置值
     */
    template<typename T>
    void set(const std::string& key, const T& value);

    /**
     * @brief 获取配置值
     */
    template<typename T>
    T get(const std::string& key, const T& defaultValue = T{}) const;

    /**
     * @brief 检查配置是否存在
     */
    bool has(const std::string& key) const;

    /**
     * @brief 移除配置项
     */
    void remove(const std::string& key);

    /**
     * @brief 保存配置到文件
     */
    void save(const std::string& filename = "");

    /**
     * @brief 加载配置从文件
     */
    void load(const std::string& filename);

    /**
     * @brief 重置为默认配置
     */
    void reset();

    /**
     * @brief 关闭配置系统
     */
    void shutdown();

private:
    Config() = default;
    ~Config() = default;
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

    void loadDefaultConfig();
    void parseConfigLine(const std::string& line);
    std::string serializeValue(const ConfigValue& value) const;
    ConfigValue deserializeValue(const std::string& value, const std::string& type) const;

    std::unordered_map<std::string, ConfigValue> m_config;
    std::string m_configFile;
    bool m_initialized;
};

// 模板方法实现
template<typename T>
void Config::set(const std::string& key, const T& value) {
    m_config[key] = ConfigValue(value);
}

template<typename T>
T Config::get(const std::string& key, const T& defaultValue) const {
    auto it = m_config.find(key);
    if (it != m_config.end()) {
        try {
            return std::get<T>(it->second);
        } catch (const std::bad_variant_access&) {
            return defaultValue;
        }
    }
    return defaultValue;
}

} // namespace Engine2D 