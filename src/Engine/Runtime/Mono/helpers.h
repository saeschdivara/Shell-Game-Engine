#pragma once

#include <mono/metadata/object-forward.h>

MonoMethod * GetMethodInClassHierarchy(MonoClass * cls, const char * methodName, int paramsCount);