#include "Engine/Core/Application.h"
#include "Engine/Core/Logger.h"
#include "Engine/Scripting/ScriptExecutionManager.h"

#include <backward.hpp>

namespace backward {
    backward::SignalHandling sh;
} // namespace backward

class SandboxApplication : public Shell::Application {
public:
//    void Run() override {
//        SHELL_INFO("Run application");
//
//        scriptExecutionManager.simpleExecute();
//
//        m_Window->Render();
//    }

private:
    Shell::ScriptExecutionManager scriptExecutionManager;
};

int main() {

    auto app = new SandboxApplication;
    app->Init();
    app->Run();
    delete app;

    return 0;
}
