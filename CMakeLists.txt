cmake_minimum_required(VERSION 3.17)

project(Re-reflection)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
        re-cmake
        GIT_REPOSITORY https://github.com/vgvgvvv/re-cmake
        GIT_TAG        "test-1.1"
)
FetchContent_MakeAvailable(re-cmake)

message(STATUS "re-cmake_SOURCE_DIR ${re-cmake_SOURCE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${re-cmake_SOURCE_DIR}")
include(Init)

message(STATUS "Init Re-Reflection Project")
ReMake_InitProject()

IsRootProject(IsRootProject)


if(${IsRootProject})
    add_subdirectory(ReReflection)
    add_subdirectory(ReReflectionTool)
endif()



