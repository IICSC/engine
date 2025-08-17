#pragma once

// 核心系统
#include "Engine2D/Core/Engine.h"
#include "Engine2D/Core/GameObject.h"
#include "Engine2D/Core/Component.h"
#include "Engine2D/Core/Transform.h"
#include "Engine2D/Core/Scene.h"
#include "Engine2D/Core/SceneManager.h"

// 图形系统
#include "Engine2D/Graphics/Renderer.h"
#include "Engine2D/Graphics/Sprite.h"
#include "Engine2D/Graphics/SpriteSheet.h"
#include "Engine2D/Graphics/Animation.h"
#include "Engine2D/Graphics/Camera.h"

// 输入系统
#include "Engine2D/Input/InputManager.h"

// 物理系统
#include "Engine2D/Physics/PhysicsWorld.h"
#include "Engine2D/Physics/Collider.h"
#include "Engine2D/Physics/Rigidbody.h"

// 音频系统
#include "Engine2D/Audio/AudioManager.h"
#include "Engine2D/Audio/Sound.h"
#include "Engine2D/Audio/Music.h"

// 工具系统
#include "Engine2D/Utils/Timer.h"
#include "Engine2D/Utils/ResourceManager.h"
#include "Engine2D/Utils/Logger.h"
#include "Engine2D/Utils/Exception.h"
#include "Engine2D/Utils/SmartPtr.h"
#include "Engine2D/Utils/Config.h"
#include "Engine2D/Utils/Profiler.h"

// 版本信息
#define ENGINE2D_VERSION_MAJOR 0
#define ENGINE2D_VERSION_MINOR 1
#define ENGINE2D_VERSION_PATCH 0

#define ENGINE2D_VERSION_STRING "0.1.0"

namespace Engine2D {
    /**
     * @brief 获取引擎版本字符串
     */
    inline const char* getVersion() {
        return ENGINE2D_VERSION_STRING;
    }
    
    /**
     * @brief 获取引擎版本主号
     */
    inline int getVersionMajor() {
        return ENGINE2D_VERSION_MAJOR;
    }
    
    /**
     * @brief 获取引擎版本次号
     */
    inline int getVersionMinor() {
        return ENGINE2D_VERSION_MINOR;
    }
    
    /**
     * @brief 获取引擎版本补丁号
     */
    inline int getVersionPatch() {
        return ENGINE2D_VERSION_PATCH;
    }
} 