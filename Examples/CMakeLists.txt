add_executable(SimpleGame SimpleGame/main.cpp)
target_link_libraries(SimpleGame PRIVATE Engine2D)
set_target_properties(SimpleGame PROPERTIES CXX_STANDARD 17)

add_executable(FallingBlocks FallingBlocks/main.cpp)
target_link_libraries(FallingBlocks PRIVATE Engine2D)
set_target_properties(FallingBlocks PROPERTIES CXX_STANDARD 17)

add_executable(InputTest InputTest/main.cpp)
target_link_libraries(InputTest PRIVATE Engine2D)
set_target_properties(InputTest PROPERTIES CXX_STANDARD 17)

# 复制资源文件到输出目录
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}) 