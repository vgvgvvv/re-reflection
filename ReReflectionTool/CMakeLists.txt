
# 如果定义了 add_clang_executable 才会构建
if(NOT COMMAND add_clang_executable)
    return()
endif()

set(LLVM_LINK_COMPONENTS Support)

ReMake_ExpandSources(sources .)

add_clang_executable(metareflect
    ${sources}
)

target_link_libraries(metareflect
    PRIVATE
    clangTooling
    clangBasic
    clangASTMatchers
)
