#include "Layers/UILayer.h"

#include <Engine/Core/Application.h>
#include <backward.hpp>

namespace backward {
    backward::SignalHandling sh;
} // namespace backward

class EditorApplication : public Shell::Application {
public:
    void Init() override {
        Application::Init();

        PushLayer(new Shell::Editor::EditorUILayer);

        SHELL_INFO("Editor start");
    }
};

int main() {
    auto app = new EditorApplication;
    app->Init();
    app->Run();
    delete app;

    return 0;
}