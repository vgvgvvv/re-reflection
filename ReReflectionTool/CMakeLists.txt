
# ��������� add_clang_executable �Żṹ��
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
    annotations.h
    annotations.cpp
    fieldgenerator.h
    functiongenerator.h
)

target_link_libraries(${targetName}
    PRIVATE
    clangTooling
    clangBasic
    clangASTMatchers
)
