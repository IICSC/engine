@echo off
echo 正在构建 Engine2D...

REM 检查CMake是否在PATH中
where cmake >nul 2>nul
if %errorlevel% neq 0 (
    echo CMake未找到，请确保已安装CMake并添加到系统PATH中
    echo 或者修改此脚本中的CMAKE_PATH变量指向CMake安装目录
    pause
    exit /b 1
)

REM 如果CMake不在PATH中，可以手动设置路径
REM set CMAKE_PATH="C:\Program Files\CMake\bin\cmake.exe"
REM 然后使用 %CMAKE_PATH% 替代 cmake

REM 创建构建目录
if not exist build mkdir build
cd build

REM 配置项目
echo 配置项目...
cmake .. -G "Visual Studio 16 2019" -A x64
if %errorlevel% neq 0 (
    echo CMake配置失败
    pause
    exit /b 1
)

REM 构建项目
echo 构建项目...
cmake --build . --config Release
if %errorlevel% neq 0 (
    echo 构建失败
    pause
    exit /b 1
)

echo 构建完成！
pause 