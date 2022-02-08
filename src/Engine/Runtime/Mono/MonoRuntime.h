#pragma once

#include "Engine/Runtime/RuntimeManager.h"
#include "Engine/Runtime/Mono/RuntimeData.h"

namespace Shell::Runtime::Mono {

    class MonoRuntime : public Runtime {
    public:
        MonoRuntime(RuntimeData * data);

        MonoObject * CreateSimpleEngineObject(const char * clsNamespaceStr, const char * clsStr);
        MonoObject * CreateVec2(float x, float y);

        MonoObject * GetObjectField(MonoObject * obj, const char * fieldName);
        void SetObjectField(MonoObject * obj, const char * fieldName, MonoObject * value);

        MonoObject * GetObjectProperty(MonoObject * obj, const char * propertyName);
        template<typename T>
        T GetSimpleObjectProperty(MonoObject * obj, const char * propertyName);
        void SetObjectProperty(MonoObject * obj, const char * propertyName, MonoObject * value);

    private:
        RuntimeData * m_Data;
    };
}


