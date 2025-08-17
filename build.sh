#!/bin/bash

echo "正在构建 Engine2D..."

# 创建构建目录
mkdir -p build
cd build

# 配置项目
echo "配置项目..."
cmake .. -DCMAKE_BUILD_TYPE=Release

# 构建项目
echo "构建项目..."
make -j$(nproc)

echo "构建完成！" 