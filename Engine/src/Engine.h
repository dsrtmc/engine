#pragma once

#include "Engine/Application.h"
#include "Engine/Window.h"
#include "Engine/Log.h"
#include "Engine/Layer.h"
#include "Engine/OrthographicCamera.h"
#include "Engine/OrthographicCameraController.h"
#include "Engine/Input.h"
#include "Engine/KeyCodes.h"

#include "Engine/Events/Event.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/ApplicationEvent.h"

#include "Engine/UI/UILayer.h"

#include "OpenGL/Shader.h"
#include "OpenGL/Renderer.h"
#include "OpenGL/Buffer.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/Texture.h"

/*
-- Entry point --
Should be included only in the app that's going to use the Engine
e.g. Sandbox/src/Sandbox.*
#include "Engine/EntryPoint.h"
*/