#pragma once

#include "ConfigUtil.h"

#include "GLFW/glfw3.h"
#include "InputManager.h"

class GLFWUtil
{
public:
	GLFWUtil(ConfigUtil& _configUtil, InputManager& _inputManager);
	void Init();
	void Update();
	void WireFrameOnly();
	bool GetShouldClose();
	void SetShouldClose(bool shouldClose);
	void Exit();
private:
	ConfigUtil& configUtil;
	InputManager& inputManager;

	GLFWwindow* window;
};