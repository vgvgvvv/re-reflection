
# 如果定义了 add_clang_executable 才会构建
if(NOT COMMAND add_clang_executable)
    return()
endif()

set(LLVM_LINK_COMPONENTS Support)

ReMake_ExpandSources(sources .)

set(targetName re-reflection-tool)

add_clang_executable(${targetName}
    ${sources}
)

target_link_libraries(${targetName}
    PRIVATE
    clangTooling
    clangBasic
    clangASTMatchers
)
