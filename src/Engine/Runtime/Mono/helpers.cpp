#include "Engine/Runtime/Mono/helpers.h"

#include <mono/metadata/class.h>

MonoMethod * GetMethodInClassHierarchy(MonoClass * cls, const char * methodName, int paramsCount) {
    auto method = mono_class_get_method_from_name(cls, methodName, paramsCount);

    if (!method) {
        auto parentClass = mono_class_get_parent(cls);

        if (parentClass) {
            return GetMethodInClassHierarchy(parentClass, methodName, paramsCount);
        } else {
            return nullptr;
        }
    } else {
        return method;
    }
}