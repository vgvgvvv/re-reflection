#pragma once

#include "FieldInfo.h"
#include "MethodInfo.h"
#include <string>

class Type {
public:
    FieldInfo& GetFieldInfo(const std::string& fieldName);
    MethodInfo& GetMethodInfo(const std::string& methodName);
};