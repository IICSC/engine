# 测试配置
enable_testing()

# 查找Google Test
find_package(GTest QUIET)
if(NOT GTest_FOUND)
    # 如果系统没有安装Google Test，尝试使用FetchContent
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
    )
    FetchContent_MakeAvailable(googletest)
endif()

# 测试源文件
set(TEST_SOURCES
    test_main.cpp
    test_core.cpp
    test_utils.cpp
    test_math.cpp
)

# 创建测试可执行文件
add_executable(Engine2DTests ${TEST_SOURCES})

# 链接库
target_link_libraries(Engine2DTests
    Engine2D
    gtest
    gtest_main
    gmock
)

# 设置包含目录
target_include_directories(Engine2DTests PRIVATE
    ${CMAKE_SOURCE_DIR}/Engine2D/include
)

# 添加测试
add_test(NAME Engine2DTests COMMAND Engine2DTests)

# 设置测试属性
set_tests_properties(Engine2DTests PROPERTIES
    TIMEOUT 300
    ENVIRONMENT "ENGINE2D_TEST_MODE=1"
) 