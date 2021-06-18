PROJECT(wwa-engine-unit-tests)

SET(ENGINE_DIR ${CMAKE_SOURCE_DIR}/engine)
SET(GTEST ${CMAKE_SOURCE_DIR}/googletest/googletest/include)

INCLUDE_DIRECTORIES(${ENGINE_DIR} ${GTEST})

ADD_EXECUTABLE(${PROJECT_NAME} main.cpp Test.cpp)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC gtest wwa-engine-graphics)
