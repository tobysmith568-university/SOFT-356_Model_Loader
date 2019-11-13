#define STB_IMAGE_IMPLEMENTATION

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include "GLFWUtil.h"
#include "GLEWUtil.h"
#include "MVPBuilder.h"
#include "Scene.h"
#include "ConfigUtil.h"
#include "InputManager.h"
#include "ConsoleUtil.h"
#include "ModelLoaderFactory.h"

using namespace std;

void RunScene(FileUtils& fileUtils, ConsoleUtil& consoleUtil, ConfigUtil& configUtil, InputManager& inputManager,
	ModelLoaderFactory& modelLoaderFactory, GLFWUtil& glfwUtil, GLEWUtil& glewUtil, BasicModelExporter& basicModelExporter);

int main(int argc, char** argv)
{
	FileUtils fileUtils = FileUtils();
	ConsoleUtil consoleUtil = ConsoleUtil(fileUtils);
	ConfigUtil configUtil = ConfigUtil(fileUtils);
	InputManager inputManager = InputManager(configUtil);
	ModelLoaderFactory modelLoaderFactory = ModelLoaderFactory(fileUtils, consoleUtil);
	GLFWUtil glfwUtil = GLFWUtil(configUtil, inputManager);
	GLEWUtil glewUtil = GLEWUtil();
	BasicModelExporter basicModelExporter = BasicModelExporter(fileUtils);

	RunScene(fileUtils, consoleUtil, configUtil, inputManager, modelLoaderFactory, glfwUtil, glewUtil, basicModelExporter);
}

void RunScene(FileUtils& fileUtils, ConsoleUtil& consoleUtil, ConfigUtil& configUtil, InputManager& inputManager,
	ModelLoaderFactory& modelLoaderFactory, GLFWUtil& glfwUtil, GLEWUtil& glewUtil, BasicModelExporter& basicModelExporter)
{
	consoleUtil.ClearConsole();

	glfwUtil.Init();

	glewUtil.Init();
	
	Scene scene = Scene(configUtil, fileUtils, inputManager, consoleUtil, modelLoaderFactory, basicModelExporter);

	bool wireframesOnly = configUtil.GetBool(BoolSetting::UseWireframes);
	while (!glfwUtil.GetShouldClose())
	{
		if (wireframesOnly)
		{
			glfwUtil.WireFrameOnly();
		}

		scene.Update();
		glfwUtil.Update();
	}

	glfwUtil.Exit();
}