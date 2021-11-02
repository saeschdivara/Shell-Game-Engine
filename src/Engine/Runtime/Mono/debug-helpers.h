#pragma once

#include <mono/jit/jit.h>

namespace Shell::Runtime::Mono {
    void PrintClassDescription(MonoClass *klass);

    void PrintClassInterfaces(MonoClass *klass);

    void PrintNestedClasses(MonoClass *klass);

    void PrintClassFields(MonoClass *klass);

    void PrintClassMethods(MonoClass *klass);

    void PrintClassProperties(MonoClass *klass);

    void PrintClassEvents(MonoClass *klass);
    
    inline void PrintEverythingFromClass(MonoClass * klass) {
        PrintClassDescription(klass);
        PrintClassInterfaces(klass);
        PrintNestedClasses(klass);
        PrintClassFields(klass);
        PrintClassMethods(klass);
        PrintClassProperties(klass);
        PrintClassEvents(klass);
    }
}