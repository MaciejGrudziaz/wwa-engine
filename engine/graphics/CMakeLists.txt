project(wwa-engine-graphics)

set(SOURCE_FILES
    ApplicationWindow.cpp
)

find_package(Vulkan REQUIRED FATAL_ERROR)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CONAN_INCLUDE_DIRS_GLM}
        ${CONAN_INCLUDE_DIRS_BOOST}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${CONAN_LIBS_GLFW}
        vulkan
        dl
        pthread
        X11
        Xxf86vm
        Xrandr
        Xi
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wpedantic -Werror -O0)
