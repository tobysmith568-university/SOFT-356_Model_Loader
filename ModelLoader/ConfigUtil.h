#pragma once
#include "FileUtils.h"
#include <map> 
#include <iterator>
#include <string>

enum class BoolSetting
{
	UseWireframes,
	BackfaceCull,
	AutoRotate,
	FullScreenOnStartup
};

enum class IntSetting
{
	WindowWidth,
	WindowHeight
};

enum class FloatSetting
{
	BackgroundR,
	BackgroundG,
	BackgroundB,
	BackgroundA,
};

enum class StringSetting
{
	WindowTitle,
	VertexShader,
	FragmentShader
};

enum class KeyBinding
{
	RotateXPositive,
	RotateXNegative,
	RotateYPositive,
	RotateYNegative,
	MoveUp,
	MoveDown,
	MoveForward,
	MoveBackward,
	MoveLeft,
	MoveRight,
	ScaleUp,
	ScaleDown,
	NewModel,
	DeleteModel,
	Reset,
	Quit,
	FirstModel,
	SecondModel,
	ThirdModel,
	FourthModel,
	FifthModel,
	SixthModel,
	SeventhModel,
	EighthModel,
	NinthModel,
	SaveModelAsBasic
};

class ConfigUtil
{
public:
	ConfigUtil(FileUtils& _fileUtils);
	bool GetBool(BoolSetting boolSetting);
	int GetInt(IntSetting intSetting);
	float GetFloat(FloatSetting floatSetting);
	std::string GetString(StringSetting stringSetting);
	int GetKeyBinding(KeyBinding keybinding);

private:
	std::map<std::string, std::string> config;
	FileUtils& fileUtils;

	std::string GetBoolValue(BoolSetting boolSetting);
	std::string GetIntValue(IntSetting intSetting);
	std::string GetFloatValue(FloatSetting floatSetting);
	std::string GetStringValue(StringSetting stringSetting);
	std::string GetKeyBindingValue(KeyBinding keybinding);
};