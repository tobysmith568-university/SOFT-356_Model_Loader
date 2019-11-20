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
#include "BasicModelLoader.h"

using namespace std;

void RunScene(FileUtils& fileUtils, ConsoleUtil& consoleUtil, ConfigUtil& configUtil, InputManager& inputManager,
	ModelLoaderFactory& modelLoaderFactory, GLFWUtil& glfwUtil, GLEWUtil& glewUtil, BasicModelLoader& basicModelLoader);

// Main method
int main(int argc, char** argv)
{
	FileUtils fileUtils = FileUtils();// Init dependencies
	ConsoleUtil consoleUtil = ConsoleUtil(fileUtils);
	ConfigUtil configUtil = ConfigUtil(fileUtils);
	InputManager inputManager = InputManager(configUtil);
	ModelLoaderFactory modelLoaderFactory = ModelLoaderFactory(fileUtils, consoleUtil);
	GLFWUtil glfwUtil = GLFWUtil(configUtil, inputManager);
	GLEWUtil glewUtil = GLEWUtil();
	BasicModelLoader basicModelLoader = BasicModelLoader(fileUtils, consoleUtil);

	RunScene(fileUtils, consoleUtil, configUtil, inputManager, modelLoaderFactory, glfwUtil, glewUtil, basicModelLoader);// Run a scene
}

void RunScene(FileUtils& fileUtils, ConsoleUtil& consoleUtil, ConfigUtil& configUtil, InputManager& inputManager,
	ModelLoaderFactory& modelLoaderFactory, GLFWUtil& glfwUtil, GLEWUtil& glewUtil, BasicModelLoader& basicModelLoader)
{
	consoleUtil.ClearConsole();

	glfwUtil.Init();

	glewUtil.Init();
	
	Scene scene = Scene(configUtil, fileUtils, inputManager, consoleUtil, modelLoaderFactory, basicModelLoader);

	bool wireframesOnly = configUtil.GetBool(BoolSetting::UseWireframes);
	while (!glfwUtil.GetShouldClose())// Loop while the window has not been told to close
	{
		if (wireframesOnly)
		{
			glfwUtil.WireFrameOnly();
		}

		scene.Update();// Update the scene
		glfwUtil.Update();// Update the window
	}

	glfwUtil.Exit();
}