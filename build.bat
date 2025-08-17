@echo off
echo 正在构建 Engine2D...

REM 创建构建目录
if not exist build mkdir build
cd build

REM 配置项目
echo 配置项目...
cmake .. -G "Visual Studio 16 2019" -A x64

REM 构建项目
echo 构建项目...
cmake --build . --config Release

echo 构建完成！
pause 