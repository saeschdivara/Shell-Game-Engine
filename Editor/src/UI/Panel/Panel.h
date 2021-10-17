#pragma once

namespace Shell::Editor {

    struct UIState;

    class Panel {
    public:
        virtual ~Panel() {}

        virtual void Render() = 0;
        void SetState(UIState * state) { m_UiState = state; }

    protected:
        UIState * m_UiState;
    };

}