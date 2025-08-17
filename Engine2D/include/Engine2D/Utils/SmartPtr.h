#pragma once

#include <memory>
#include <type_traits>

namespace Engine2D {

/**
 * @brief 引擎对象智能指针别名
 */
template<typename T>
using Ptr = std::unique_ptr<T>;

/**
 * @brief 引擎对象共享指针别名
 */
template<typename T>
using SharedPtr = std::shared_ptr<T>;

/**
 * @brief 引擎对象弱指针别名
 */
template<typename T>
using WeakPtr = std::weak_ptr<T>;

/**
 * @brief 创建引擎对象智能指针
 */
template<typename T, typename... Args>
Ptr<T> MakePtr(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

/**
 * @brief 创建引擎对象共享指针
 */
template<typename T, typename... Args>
SharedPtr<T> MakeShared(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

/**
 * @brief 安全的动态转换
 */
template<typename To, typename From>
Ptr<To> DynamicCast(Ptr<From>&& ptr) {
    if (auto* p = dynamic_cast<To*>(ptr.get())) {
        ptr.release();
        return Ptr<To>(p);
    }
    return nullptr;
}

/**
 * @brief 安全的共享指针动态转换
 */
template<typename To, typename From>
SharedPtr<To> DynamicCast(const SharedPtr<From>& ptr) {
    return std::dynamic_pointer_cast<To>(ptr);
}

/**
 * @brief 检查指针是否有效
 */
template<typename T>
bool IsValid(const Ptr<T>& ptr) {
    return ptr != nullptr;
}

template<typename T>
bool IsValid(const SharedPtr<T>& ptr) {
    return ptr != nullptr;
}

template<typename T>
bool IsValid(const WeakPtr<T>& ptr) {
    return !ptr.expired();
}

} // namespace Engine2D 