#include "Engine/Runtime/Mono/debug-helpers.h"

namespace Shell::Runtime::Mono {

    void PrintClassDescription(MonoClass *klass) {
        printf("Class name: %s.%s\n", mono_class_get_namespace(klass), mono_class_get_name(klass));
        printf("Rank: %d, flags 0x%0x\n", mono_class_get_rank(klass), mono_class_get_flags(klass));
    }

    void PrintClassInterfaces(MonoClass *klass)  {
        MonoClass *iface;
        void * iter = nullptr;

        printf("Implements: ");
        while ((iface = mono_class_get_interfaces(klass, &iter))) {
            printf("%s ", mono_class_get_name(iface));
        }
        printf("\n");
    }

    void PrintNestedClasses(MonoClass *klass) {
        MonoClass *nested;
        void * iter = nullptr;

        printf("Has nested types: ");
        while ((nested = mono_class_get_nested_types(klass, &iter))) {
            printf("%s ", mono_class_get_name(nested));
        }
        printf("\n");
    }

    void PrintClassFields(MonoClass *klass) {
        MonoClassField *field;
        void * iter = nullptr;

        while ((field = mono_class_get_fields(klass, &iter))) {
            printf("Field: %s, flags 0x%x\n", mono_field_get_name(field), mono_field_get_flags(field));
        }
    }

    void PrintClassMethods(MonoClass *klass) {
        MonoMethod *method;
        void * iter = nullptr;

        while ((method = mono_class_get_methods(klass, &iter))) {
            uint32_t flags, iflags;
            flags = mono_method_get_flags(method, &iflags);
            printf("Method: %s, flags 0x%x, iflags 0x%x\n", mono_method_get_name(method), flags, iflags);
        }
    }

    void PrintClassProperties(MonoClass *klass) {
        MonoProperty *prop;
        void * iter = NULL;

        while ((prop = mono_class_get_properties(klass, &iter))) {
            printf("Property: %s, flags 0x%x\n", mono_property_get_name(prop), mono_property_get_flags(prop));
        }
    }

    void PrintClassEvents(MonoClass *klass) {
        MonoEvent *event;
        void * iter = NULL;

        while ((event = mono_class_get_events(klass, &iter))) {
            printf("Event: %s, flags: 0x%x\n", mono_event_get_name(event), mono_event_get_flags(event));
        }
    }
}

