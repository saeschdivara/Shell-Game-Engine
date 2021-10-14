#pragma once

namespace Shell::Editor {

    class Panel {
    public:
        virtual ~Panel() {}

        virtual void Render() = 0;
    };

}