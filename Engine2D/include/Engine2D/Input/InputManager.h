#pragma once

#include <SDL.h>
#include <unordered_map>
#include <string>
#include <functional>

namespace Engine2D {

struct Vector2;

/**
 * @brief 按键状态枚举
 */
enum class KeyState {
    NONE,     // 无状态
    PRESSED,  // 按下
    HELD,     // 保持按下
    RELEASED  // 释放
};

/**
 * @brief 鼠标按键枚举
 */
enum class MouseButton {
    LEFT,    // 左键
    MIDDLE,  // 中键
    RIGHT    // 右键
};

/**
 * @brief 输入管理器，处理键盘、鼠标和触摸输入
 */
class InputManager {
public:
    /**
     * @brief 构造函数
     */
    InputManager();
    ~InputManager();

    /**
     * @brief 初始化输入管理器
     */
    void initialize();

    /**
     * @brief 更新输入状态
     * @return 是否继续运行（如果收到退出事件则返回false）
     */
    bool update();

    /**
     * @brief 清理资源
     */
    void shutdown();

    /**
     * @brief 检查键是否处于指定状态
     * @param key SDL键码
     * @param state 要检查的状态
     * @return 如果键处于指定状态则返回true
     */
    bool isKeyState(SDL_Keycode key, KeyState state) const;

    /**
     * @brief 检查键是否刚被按下
     * @param key SDL键码
     * @return 如果键刚被按下则返回true
     */
    bool isKeyPressed(SDL_Keycode key) const;

    /**
     * @brief 检查键是否持续按下
     * @param key SDL键码
     * @return 如果键持续按下则返回true
     */
    bool isKeyHeld(SDL_Keycode key) const;

    /**
     * @brief 检查键是否刚被释放
     * @param key SDL键码
     * @return 如果键刚被释放则返回true
     */
    bool isKeyReleased(SDL_Keycode key) const;

    /**
     * @brief 检查鼠标按键是否处于指定状态
     * @param button 鼠标按键
     * @param state 要检查的状态
     * @return 如果鼠标按键处于指定状态则返回true
     */
    bool isMouseButtonState(MouseButton button, KeyState state) const;

    /**
     * @brief 获取鼠标位置
     * @return 鼠标位置
     */
    Vector2 getMousePosition() const;

    /**
     * @brief 获取鼠标位置变化
     * @return 鼠标位置变化
     */
    Vector2 getMouseDelta() const;

    /**
     * @brief 获取鼠标滚轮变化
     * @return 鼠标滚轮变化
     */
    Vector2 getMouseWheel() const;

    /**
     * @brief 注册按键回调函数
     * @param key SDL键码
     * @param state 触发回调的按键状态
     * @param callback 回调函数
     * @return 回调ID，用于移除回调
     */
    int registerKeyCallback(SDL_Keycode key, KeyState state, std::function<void()> callback);

    /**
     * @brief 注册鼠标按键回调函数
     * @param button 鼠标按键
     * @param state 触发回调的按键状态
     * @param callback 回调函数
     * @return 回调ID，用于移除回调
     */
    int registerMouseCallback(MouseButton button, KeyState state, std::function<void(const Vector2&)> callback);

    /**
     * @brief 注册鼠标移动回调函数
     * @param callback 回调函数
     * @return 回调ID，用于移除回调
     */
    int registerMouseMoveCallback(std::function<void(const Vector2&, const Vector2&)> callback);

    /**
     * @brief 注册鼠标滚轮回调函数
     * @param callback 回调函数
     * @return 回调ID，用于移除回调
     */
    int registerMouseWheelCallback(std::function<void(const Vector2&)> callback);

    /**
     * @brief 移除回调函数
     * @param callbackId 回调ID
     * @return 是否成功移除
     */
    bool removeCallback(int callbackId);

private:
    // 存储键盘按键的当前和上一帧状态
    std::unordered_map<SDL_Keycode, KeyState> m_currentKeyStates;
    std::unordered_map<SDL_Keycode, KeyState> m_previousKeyStates;

    // 存储鼠标按键的当前和上一帧状态
    std::unordered_map<MouseButton, KeyState> m_currentMouseStates;
    std::unordered_map<MouseButton, KeyState> m_previousMouseStates;

    // 鼠标位置和变化
    int m_mouseX, m_mouseY;
    int m_previousMouseX, m_previousMouseY;
    int m_mouseWheelX, m_mouseWheelY;

    // 回调结构体和相关容器
    struct KeyCallback {
        SDL_Keycode key;
        KeyState state;
        std::function<void()> callback;
    };

    struct MouseButtonCallback {
        MouseButton button;
        KeyState state;
        std::function<void(const Vector2&)> callback;
    };

    struct MouseMoveCallback {
        std::function<void(const Vector2&, const Vector2&)> callback;
    };

    struct MouseWheelCallback {
        std::function<void(const Vector2&)> callback;
    };

    std::unordered_map<int, KeyCallback> m_keyCallbacks;
    std::unordered_map<int, MouseButtonCallback> m_mouseButtonCallbacks;
    std::unordered_map<int, MouseMoveCallback> m_mouseMoveCallbacks;
    std::unordered_map<int, MouseWheelCallback> m_mouseWheelCallbacks;
    int m_nextCallbackId;

    // 处理事件
    void processEvent(const SDL_Event& event);
};

} // namespace Engine2D 