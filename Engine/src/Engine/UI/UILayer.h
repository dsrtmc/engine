#pragma once

#include "Layer.h"

namespace Engine
{
    class UILayer : public Layer
    {
    public:
        UILayer();
        ~UILayer() override;

        void Begin();
        void End();
    };
}