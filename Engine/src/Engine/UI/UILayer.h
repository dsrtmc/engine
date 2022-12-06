#pragma once

#include "Layer.h"

namespace Engine
{
    class UILayer : public Layer
    {
    public:
        UILayer();
        ~UILayer();

        void OnImGuiUpdate() override;

        void Begin();
        void End();
    };
}