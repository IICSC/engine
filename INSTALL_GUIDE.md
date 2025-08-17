# Engine2D 安装指南

## 🚀 快速开始

### 1. 运行依赖检查
```bash
check_dependencies.bat
```

### 2. 运行智能构建
```bash
build_smart.bat
```

## 📋 详细安装步骤

### 步骤1：安装CMake

1. **下载CMake**
   - 访问 [CMake官网](https://cmake.org/download/)
   - 下载 "Windows x64 Installer"
   - 选择最新稳定版本（如3.28.0）

2. **安装CMake**
   - 运行安装程序
   - **重要**：勾选 "Add CMake to the system PATH for all users"
   - 完成安装

3. **验证安装**
   ```bash
   cmake --version
   ```

### 步骤2：安装Visual Studio

1. **下载Visual Studio**
   - 访问 [Visual Studio官网](https://visualstudio.microsoft.com/)
   - 下载 "Visual Studio Community 2022"（免费版）

2. **安装必要组件**
   - 运行安装程序
   - 选择 "Desktop development with C++"
   - 确保包含以下组件：
     - MSVC v143编译器
     - Windows 10/11 SDK
     - CMake工具

3. **验证安装**
   ```bash
   cl
   ```

### 步骤3：安装SDL2

#### 方法1：使用vcpkg（推荐）
```bash
# 安装vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat

# 安装SDL2
.\vcpkg install sdl2 sdl2-image sdl2-ttf sdl2-mixer

# 集成到Visual Studio
.\vcpkg integrate install
```

#### 方法2：手动安装
1. 下载SDL2开发库：https://www.libsdl.org/download-2.0.php
2. 解压到 `C:\SDL2`
3. 设置环境变量：
   - `SDL2DIR=C:\SDL2`
   - 将 `C:\SDL2\lib\x64` 添加到 `PATH`

### 步骤4：构建项目

1. **检查依赖**
   ```bash
   check_dependencies.bat
   ```

2. **构建项目**
   ```bash
   build_smart.bat
   ```

3. **运行示例**
   ```bash
   cd build\bin\Release
   SimpleGame.exe
   ```

## 🔧 故障排除

### 问题1：CMake未找到
**解决方案**：
- 确保CMake已安装并添加到PATH
- 重启命令提示符
- 或使用 `build_smart.bat` 手动指定路径

### 问题2：Visual Studio编译器未找到
**解决方案**：
- 安装Visual Studio 2019或更高版本
- 运行 "Developer Command Prompt for VS"
- 或设置环境变量指向编译器

### 问题3：SDL2未找到
**解决方案**：
- 使用vcpkg安装SDL2（推荐）
- 或手动下载并设置环境变量
- 确保包含所有SDL2扩展库

### 问题4：编译错误
**解决方案**：
- 检查Visual Studio版本是否支持C++17
- 确保所有依赖库版本匹配
- 查看详细的错误信息

## 📦 可选工具

### Git（用于版本控制）
- 下载：https://git-scm.com/
- 安装时选择默认选项即可

### Visual Studio Code（推荐编辑器）
- 下载：https://code.visualstudio.com/
- 安装C++扩展包

## 🎯 验证安装

运行以下命令验证所有组件：
```bash
cmake --version
cl
git --version
```

如果所有命令都正常输出，说明安装成功！

## 📞 获取帮助

如果遇到问题：
1. 运行 `check_dependencies.bat` 检查依赖
2. 查看错误信息
3. 参考故障排除部分
4. 提交Issue到项目仓库 