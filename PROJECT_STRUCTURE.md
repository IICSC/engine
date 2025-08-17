# Engine2D 项目结构

## 📁 目录结构

```
Engine2D/
├── Engine2D/                    # 引擎核心库
│   ├── include/                 # 头文件
│   │   └── Engine2D/
│   │       ├── Core/           # 核心系统
│   │       │   ├── Engine.h    # 引擎主类
│   │       │   ├── GameObject.h # 游戏对象
│   │       │   ├── Component.h # 组件基类
│   │       │   ├── Transform.h # 变换组件
│   │       │   ├── Scene.h     # 场景类
│   │       │   └── SceneManager.h # 场景管理器
│   │       ├── Graphics/       # 图形系统
│   │       │   ├── Renderer.h  # 渲染器
│   │       │   ├── Sprite.h    # 精灵
│   │       │   ├── Camera.h    # 摄像机
│   │       │   └── ...
│   │       ├── Input/          # 输入系统
│   │       │   └── InputManager.h
│   │       ├── Physics/        # 物理系统
│   │       │   ├── PhysicsWorld.h
│   │       │   ├── Rigidbody.h
│   │       │   └── Collider.h
│   │       ├── Audio/          # 音频系统
│   │       │   ├── AudioManager.h
│   │       │   ├── Sound.h
│   │       │   └── Music.h
│   │       └── Utils/          # 工具系统
│   │           ├── Logger.h    # 日志系统
│   │           ├── Timer.h     # 定时器
│   │           ├── Config.h    # 配置管理
│   │           ├── Profiler.h  # 性能分析
│   │           ├── Exception.h # 异常处理
│   │           └── SmartPtr.h  # 智能指针
│   ├── src/                    # 源文件
│   │   ├── Core/              # 核心系统实现
│   │   ├── Graphics/          # 图形系统实现
│   │   ├── Input/             # 输入系统实现
│   │   ├── Physics/           # 物理系统实现
│   │   ├── Audio/             # 音频系统实现
│   │   └── Utils/             # 工具系统实现
│   └── CMakeLists.txt         # 引擎库构建配置
├── Examples/                   # 示例项目
│   ├── SimpleGame/            # 简单游戏示例
│   ├── InputTest/             # 输入测试示例
│   └── FallingBlocks/         # 掉落方块示例
├── Tests/                      # 单元测试
│   ├── test_main.cpp          # 测试主文件
│   ├── test_core.cpp          # 核心系统测试
│   ├── test_utils.cpp         # 工具系统测试
│   └── test_math.cpp          # 数学库测试
├── CMakeLists.txt             # 主构建配置
├── README.md                  # 项目说明
├── LICENSE                    # 许可证
├── config.ini                # 默认配置文件
├── build.bat                 # Windows构建脚本
├── build.sh                  # Linux/macOS构建脚本
└── .gitignore                # Git忽略文件
```

## 🏗️ 架构设计

### 核心系统 (Core)
- **Engine**: 引擎主类，负责初始化和协调所有子系统
- **GameObject**: 游戏对象，组件的容器
- **Component**: 组件基类，提供功能模块化
- **Transform**: 变换组件，处理位置、旋转、缩放
- **Scene**: 场景类，管理游戏对象集合
- **SceneManager**: 场景管理器，处理场景切换

### 图形系统 (Graphics)
- **Renderer**: 渲染器，负责2D图形渲染
- **Sprite**: 精灵组件，处理图像渲染
- **Camera**: 摄像机，控制视图变换
- **Animation**: 动画系统，处理精灵动画

### 物理系统 (Physics)
- **PhysicsWorld**: 物理世界，管理物理模拟
- **Rigidbody**: 刚体组件，处理物理运动
- **Collider**: 碰撞器，处理碰撞检测

### 输入系统 (Input)
- **InputManager**: 输入管理器，处理键盘、鼠标、触摸输入

### 音频系统 (Audio)
- **AudioManager**: 音频管理器，管理音频播放
- **Sound**: 音效类，处理短音频
- **Music**: 音乐类，处理背景音乐

### 工具系统 (Utils)
- **Logger**: 日志系统，提供调试和错误记录
- **Timer**: 定时器，处理时间和帧率控制
- **Config**: 配置管理，处理引擎配置
- **Profiler**: 性能分析，测量代码执行时间
- **Exception**: 异常处理，提供错误处理机制
- **SmartPtr**: 智能指针，提供内存管理工具

## 🔧 构建系统

项目使用CMake作为构建系统，支持：
- 跨平台构建
- 多配置支持 (Debug/Release)
- 可选测试构建
- 自动依赖管理

## 📦 依赖管理

主要依赖：
- **SDL2**: 跨平台多媒体库
- **SDL2_image**: 图像加载扩展
- **SDL2_ttf**: 字体渲染扩展
- **SDL2_mixer**: 音频播放扩展
- **Google Test**: 单元测试框架（可选）

## 🧪 测试框架

项目包含完整的单元测试套件：
- 使用Google Test框架
- 覆盖核心功能测试
- 支持持续集成
- 性能基准测试

## 📊 性能优化

引擎经过以下优化：
- 智能指针管理内存
- 对象池减少分配
- 批量渲染优化
- 空间分区碰撞检测
- 帧率控制和同步 