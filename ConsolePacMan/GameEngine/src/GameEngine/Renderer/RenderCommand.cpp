#include "gepch.h"
#include "RenderCommand.h"

#include "Platform/ConsoleRender/ConsoleRendererAPI.h"

namespace GameEngine
{
	RendererAPI* RenderCommand::s_RendererAPI = new ConsoleRendererAPI;
}