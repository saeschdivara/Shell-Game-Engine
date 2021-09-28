#include <Engine/Core/Application.h>
#include <Engine/Core/Logger.h>

class EditorApplication : public Shell::Application {
public:
    void Init() override {
        Application::Init();

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