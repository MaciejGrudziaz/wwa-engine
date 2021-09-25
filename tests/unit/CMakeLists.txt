project(wwa-engine-unit-tests)

set(ENGINE_DIR ${CMAKE_SOURCE_DIR}/engine)

add_executable(${PROJECT_NAME} main.cpp Test.cpp)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${CONAN_LIBS_GTEST}
        wwa-engine-graphics
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CONAN_INCLUDE_DIRS_GTEST}
        ${ENGINE_DIR}
)
