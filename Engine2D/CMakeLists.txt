set(ENGINE_SOURCES
    src/Core/Engine.cpp
    src/Core/GameObject.cpp
    src/Core/Component.cpp
    src/Core/Transform.cpp
    src/Core/Scene.cpp
    src/Core/SceneManager.cpp
    src/Graphics/Renderer.cpp
    src/Graphics/Sprite.cpp
    src/Graphics/SpriteSheet.cpp
    src/Graphics/Animation.cpp
    src/Graphics/Camera.cpp
    src/Input/InputManager.cpp
    src/Physics/PhysicsWorld.cpp
    src/Physics/Collider.cpp
    src/Physics/Rigidbody.cpp
    src/Audio/AudioManager.cpp
    src/Audio/Sound.cpp
    src/Audio/Music.cpp
    src/Utils/Timer.cpp
    src/Utils/ResourceManager.cpp
    src/Utils/Logger.cpp
    src/Utils/Config.cpp
    src/Utils/Profiler.cpp
)

set(ENGINE_HEADERS
    include/Engine2D/Core/Engine.h
    include/Engine2D/Core/GameObject.h
    include/Engine2D/Core/Component.h
    include/Engine2D/Core/Transform.h
    include/Engine2D/Core/Scene.h
    include/Engine2D/Core/SceneManager.h
    include/Engine2D/Graphics/Renderer.h
    include/Engine2D/Graphics/Sprite.h
    include/Engine2D/Graphics/SpriteSheet.h
    include/Engine2D/Graphics/Animation.h
    include/Engine2D/Graphics/Camera.h
    include/Engine2D/Input/InputManager.h
    include/Engine2D/Physics/PhysicsWorld.h
    include/Engine2D/Physics/Collider.h
    include/Engine2D/Physics/Rigidbody.h
    include/Engine2D/Audio/AudioManager.h
    include/Engine2D/Audio/Sound.h
    include/Engine2D/Audio/Music.h
    include/Engine2D/Utils/Timer.h
    include/Engine2D/Utils/ResourceManager.h
    include/Engine2D/Utils/Logger.h
    include/Engine2D/Utils/Exception.h
    include/Engine2D/Utils/SmartPtr.h
    include/Engine2D/Utils/Config.h
    include/Engine2D/Utils/Profiler.h
    include/Engine2D/Engine2D.h
)

# 创建库
add_library(Engine2D STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS})

# 链接第三方库
target_link_libraries(Engine2D
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
)

# 安装目标
install(TARGETS Engine2D
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# 安装头文件
install(DIRECTORY include/ DESTINATION include) 