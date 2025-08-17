@echo off
echo ========================================
echo Engine2D 依赖检查工具
echo ========================================

echo 检查构建工具...

REM 检查CMake
echo [1/4] 检查CMake...
where cmake >nul 2>nul
if %errorlevel% equ 0 (
    for /f "tokens=*" %%i in ('cmake --version 2^>^&1') do (
        echo     ✓ CMake: %%i
    )
) else (
    echo     ✗ CMake未找到
    echo       请从 https://cmake.org/download/ 下载安装
)

REM 检查Visual Studio
echo [2/4] 检查Visual Studio...
where cl >nul 2>nul
if %errorlevel% equ 0 (
    echo     ✓ Visual Studio编译器已找到
) else (
    echo     ✗ Visual Studio编译器未找到
    echo       请安装Visual Studio 2019或更高版本
    echo       或运行"Developer Command Prompt for VS"
)

REM 检查Git
echo [3/4] 检查Git...
where git >nul 2>nul
if %errorlevel% equ 0 (
    for /f "tokens=*" %%i in ('git --version 2^>^&1') do (
        echo     ✓ Git: %%i
    )
) else (
    echo     ✗ Git未找到
    echo       请从 https://git-scm.com/ 下载安装
)

REM 检查SDL2
echo [4/4] 检查SDL2...
if exist "C:\SDL2" (
    echo     ✓ SDL2目录存在: C:\SDL2
) else if exist "%SDL2DIR%" (
    echo     ✓ SDL2环境变量: %SDL2DIR%
) else (
    echo     ✗ SDL2未找到
    echo       请下载SDL2开发库并设置环境变量
    echo       或使用vcpkg安装: vcpkg install sdl2
)

echo.
echo ========================================
echo 检查完成！
echo.
echo 如果所有项目都显示✓，则可以开始构建
echo 如果有✗项目，请先解决依赖问题
echo ========================================
pause 