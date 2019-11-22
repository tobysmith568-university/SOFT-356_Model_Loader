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

	void GetConfigData();
	void CreateDefaultConfigData();

	std::string GetBoolValue(BoolSetting boolSetting);
	std::string GetIntValue(IntSetting intSetting);
	std::string GetFloatValue(FloatSetting floatSetting);
	std::string GetStringValue(StringSetting stringSetting);
	std::string GetKeyBindingValue(KeyBinding keybinding);

	std::string configFileFolder = "media";
	std::string configFileLocation = "media/config.dat";
	std::string defaultFileData =
"windowWidth=800\n\
windowHeight=600\n\
windowTitle=My Window\n\
fullScreenOnStartup=0\n\
\n\
backgroundR=127\n\
backgroundG=202\n\
backgroundB=240\n\
backgroundA=1\n\
\n\
useWireframes=0\n\
backfaceCull=0\n\
autoRotate=0\n\
\n\
vertexShader=media/shader.vert\n\
fragmentShader=media/shader.frag\n\
\n\
\n\
\n\
KeyBinding_RotateXPositive=262\n\
KeyBinding_RotateXNegative=263\n\
KeyBinding_RotateYPositive=264\n\
KeyBinding_RotateYNegative=265\n\
\n\
KeyBinding_MoveUp=81\n\
KeyBinding_MoveDown=69\n\
KeyBinding_MoveForward=87\n\
KeyBinding_MoveBackward=83\n\
KeyBinding_MoveLeft=65\n\
KeyBinding_MoveRight=68\n\
\n\
KeyBinding_ScaleUp=334\n\
KeyBinding_ScaleDown=333\n\
\n\
KeyBinding_NewModel=78\n\
KeyBinding_DeleteModel=261\n\
KeyBinding_Reset=82\n\
\n\
KeyBinding_Quit=256\n\
\n\
KeyBinding_FirstModel=49\n\
KeyBinding_SecondModel=50\n\
KeyBinding_ThirdModel=51\n\
KeyBinding_FourthModel=52\n\
KeyBinding_FifthModel=53\n\
KeyBinding_SixthModel=54\n\
KeyBinding_SeventhModel=55\n\
KeyBinding_EighthModel=56\n\
KeyBinding_NinthModel=57\n\
\n\
KeyBinding_SaveModelAsBasic=290";

	std::string vertexShaderLocation = "media/shader.vert";
	std::string defaultVertexShaderData =
"#version 400 core\n\
\n\
layout(location = 0) in vec3 vPosition;\n\
layout(location = 1) in vec4 vColour;\n\
layout(location = 2) in vec2 aTexCoord;\n\
uniform mat4 mvp;\n\
	\n\
out vec4 fragColour;\n\
out vec2 TexCoord;\n\
void\n\
	main()\n\
{\n\
	gl_Position = mvp * vec4(vPosition, 1.0);\n\
	fragColour = vColour;\n\
	TexCoord = aTexCoord;\n\
}\n\
";

	std::string fragmentShaderLocation = "media/shader.frag";
	std::string defaultFragmentShaderData =
"#version 450 core\n\
\n\
out vec4 fColor;\n\
in vec4 fragColour;\n\
in vec2 TexCoord;\n\
\n\
uniform sampler2D ourTexture;\n\
\n\
void main()\n\
{\n\
	fColor = texture(ourTexture, TexCoord) * fragColour;\n\
}\n\
";
};