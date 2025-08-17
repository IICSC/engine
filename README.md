# Engine2D

一个现代化的、高性能的2D游戏引擎，使用C++17开发，采用组件式架构设计。

## 🚀 特性

* **现代化C++**: 使用C++17标准，支持智能指针、移动语义等现代特性
* **组件式架构**: 游戏对象由多个组件组成，每个组件负责特定功能
* **高性能**: 优化的渲染和物理系统，支持高效的游戏开发
* **完整的工具链**: 包含日志系统、性能分析器、配置管理等工具
* **跨平台**: 支持Windows、Linux、macOS
* **易于使用**: 提供简单直观的API，降低游戏开发的学习曲线
* **模块化设计**: 各系统相对独立，可以根据需要选择使用哪些功能

## 🎯 核心功能

* **场景管理**: 灵活的场景和游戏对象管理系统
* **图形渲染**: 基于SDL2的高性能2D图形渲染
* **物理系统**: 完整的物理模拟，包括刚体动力学和碰撞检测
* **输入处理**: 键盘、鼠标和触摸输入处理
* **音频系统**: 音效和音乐支持
* **资源管理**: 高效的资源加载和管理
* **日志系统**: 完整的日志记录和调试支持
* **性能分析**: 内置性能分析工具
* **配置管理**: 灵活的配置系统

## 📋 系统要求

* **编译器**: C++17兼容的编译器 (GCC 7+, Clang 5+, MSVC 2017+)
* **构建系统**: CMake 3.12+
* **依赖库**: SDL2 及相关库 (SDL2_image, SDL2_ttf, SDL2_mixer)
* **内存**: 至少 512MB RAM
* **存储**: 至少 100MB 可用空间

## 🔨 构建说明

### Windows (Visual Studio)

1. 安装必要的依赖:
   * [Visual Studio](https://visualstudio.microsoft.com/) 2019或更高版本
   * [CMake](https://cmake.org/download/)
   * [SDL2 开发库](https://www.libsdl.org/download-2.0.php)
   * [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
   * [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)
   * [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)

2. 配置SDL2环境变量或在CMake配置中指定SDL2路径

3. 创建构建目录并生成项目文件:
   ```
   mkdir build
   cd build
   cmake ..
   ```

4. 打开生成的Visual Studio解决方案并构建项目

### Linux

1. 安装必要的依赖:
   ```
   sudo apt-get install cmake libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
   ```

2. 创建构建目录并构建项目:
   ```
   mkdir build
   cd build
   cmake ..
   make
   ```

### macOS

1. 安装必要的依赖:
   ```
   brew install cmake sdl2 sdl2_image sdl2_ttf sdl2_mixer
   ```

2. 创建构建目录并构建项目:
   ```
   mkdir build
   cd build
   cmake ..
   make
   ```

## 💡 使用示例

下面是一个简单的使用示例:

```cpp
#include <Engine2D/Engine2D.h>

class Game {
public:
    bool initialize() {
        // 初始化引擎
        if (!Engine2D::Engine::getInstance().initialize("My Game", 800, 600)) {
            return false;
        }
        
        // 创建场景
        auto sceneManager = Engine2D::Engine::getInstance().getSceneManager();
        auto scene = sceneManager->createScene("MainScene");
        sceneManager->loadScene("MainScene");
        
        // 创建游戏对象
        auto player = scene->createGameObject("Player");
        
        // 添加组件
        auto sprite = player->addComponent<Engine2D::Sprite>();
        sprite->loadFromFile(Engine2D::Engine::getInstance().getRenderer()->getSDLRenderer(), "player.png");
        
        // 添加物理组件
        auto rigidbody = player->addComponent<Engine2D::Rigidbody>();
        auto collider = player->addComponent<Engine2D::BoxCollider>(32, 32);
        
        return true;
    }
    
    void run() {
        // 运行游戏
        Engine2D::Engine::getInstance().run();
    }
};

int main(int argc, char* argv[]) {
    Game game;
    if (game.initialize()) {
        game.run();
    }
    return 0;
}
```

## 🧪 测试

项目包含完整的单元测试套件：

```bash
# 启用测试构建
cmake -DBUILD_TESTS=ON ..

# 运行测试
make test
```

## 📊 性能

引擎经过优化，支持：
- 60+ FPS 稳定运行
- 1000+ 游戏对象同时渲染
- 高效的物理模拟
- 内存使用优化

## 🤝 贡献

欢迎贡献代码！请遵循以下步骤：

1. Fork 项目
2. 创建功能分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 打开 Pull Request

## 📄 许可证

本项目采用MIT许可证。详情请参见[LICENSE](LICENSE)文件。 