
# 如果定义了 add_clang_executable 才会构建
if(NOT COMMAND add_clang_executable)
    return()
endif()

set(LLVM_LINK_COMPONENTS Support)

set(targetName re-reflection-tool)

add_clang_executable(${targetName}
    re_reflection_tool.cpp
    reflected_class.cpp
    reflected_class.h
    util.cpp
    util.h
    class_finder.h
    class_finder.cpp
)

target_link_libraries(${targetName}
    PRIVATE
    clangTooling
    clangBasic
    clangASTMatchers
)
