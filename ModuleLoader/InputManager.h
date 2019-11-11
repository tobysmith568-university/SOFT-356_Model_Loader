#pragma once
#include "ConfigUtil.h"
#include <functional>
#include <GLFW/glfw3.h>

class InputManager
{
public:
	InputManager(ConfigUtil& _configUtil);
	void BindWindow(GLFWwindow* window);

	void RegisterKeyPress(KeyBinding keyBinding, std::function<void()> callback);
	void RegisterKeyRepeat(KeyBinding keyBinding, std::function<void()> callback);
	void RegisterKeyRelease(KeyBinding keyBinding, std::function<void()> callback);

	std::map<int, std::vector<std::function<void()>>> GetKeyPresses();
	std::map<int, std::vector<std::function<void()>>> GetKeyRepeats();
	std::map<int, std::vector<std::function<void()>>> GetKeyReleases();

private:
	ConfigUtil& configUtil;
	std::map<int, std::vector<std::function<void()>>> keyPresses;
	std::map<int, std::vector<std::function<void()>>> keyRepeats;
	std::map<int, std::vector<std::function<void()>>> keyReleases;
};