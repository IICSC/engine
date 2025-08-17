@echo off
setlocal enabledelayedexpansion

echo ========================================
echo Engine2D 智能构建脚本
echo ========================================

REM 尝试查找CMake
set CMAKE_FOUND=0
set CMAKE_PATH=

REM 检查PATH中的cmake
where cmake >nul 2>nul
if %errorlevel% equ 0 (
    set CMAKE_FOUND=1
    set CMAKE_PATH=cmake
    echo 找到CMake: cmake
    goto :found_cmake
)

REM 检查常见的CMake安装路径
set CMAKE_PATHS=^
"C:\Program Files\CMake\bin\cmake.exe" ^
"C:\Program Files (x86)\CMake\bin\cmake.exe" ^
"C:\cmake\bin\cmake.exe" ^
"C:\tools\cmake\bin\cmake.exe"

for %%p in (%CMAKE_PATHS%) do (
    if exist %%p (
        set CMAKE_FOUND=1
        set CMAKE_PATH=%%p
        echo 找到CMake: %%p
        goto :found_cmake
    )
)

REM 如果还是没找到，提示用户
echo CMake未找到！
echo.
echo 请选择以下选项之一：
echo 1. 安装CMake并添加到PATH
echo 2. 手动指定CMake路径
echo 3. 退出
echo.
set /p choice="请输入选择 (1-3): "

if "%choice%"=="1" (
    echo 请访问 https://cmake.org/download/ 下载并安装CMake
    echo 安装时请确保勾选"Add CMake to the system PATH"
    pause
    exit /b 1
) else if "%choice%"=="2" (
    set /p CMAKE_PATH="请输入CMake完整路径: "
    if exist "!CMAKE_PATH!" (
        set CMAKE_FOUND=1
        echo 使用指定的CMake路径: !CMAKE_PATH!
    ) else (
        echo 指定的路径不存在！
        pause
        exit /b 1
    )
) else (
    echo 退出构建
    exit /b 1
)

:found_cmake
echo.
echo 开始构建Engine2D...

REM 创建构建目录
if not exist build mkdir build
cd build

REM 配置项目
echo 配置项目...
%CMAKE_PATH% .. -G "Visual Studio 16 2019" -A x64
if %errorlevel% neq 0 (
    echo CMake配置失败
    echo 请检查：
    echo 1. 是否安装了Visual Studio 2019或更高版本
    echo 2. 是否安装了SDL2开发库
    echo 3. CMake版本是否支持
    pause
    exit /b 1
)

REM 构建项目
echo 构建项目...
%CMAKE_PATH% --build . --config Release
if %errorlevel% neq 0 (
    echo 构建失败
    echo 请检查编译错误信息
    pause
    exit /b 1
)

echo.
echo ========================================
echo 构建成功完成！
echo 输出文件位于: build\bin\Release\
echo ========================================
pause 