project(wwa-engine-game)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED FATAL_ERROR)

SET(ENGINE_DIR ${CMAKE_SOURCE_DIR}/engine)

set(SOURCE_FILES
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${ENGINE_DIR}
)

target_link_libraries(${PROJECT_NAME} wwa-engine-graphics)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wall
        -Wpedantic
        -Werror
        -O0
)