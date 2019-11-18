#include "ConfigUtil.h"
#include <string>

using namespace std;

ConfigUtil::ConfigUtil(FileUtils& _fileUtils) : fileUtils(_fileUtils)
{
	config = map<string, string>();

	vector<string> configFile = fileUtils.ReadFileAsLines("media/config.dat");

	for (int i = 0; i < configFile.size(); i++)
	{
		string line = configFile.at(i);

		string key = "";
		string value = "";
		bool atEquals = false;

		for (char& c : line)
		{
			if (c == '=' && !atEquals)
			{
				atEquals = true;
				continue;
			}

			if (!atEquals)
			{
				key += c;
				continue;
			}

			value += c;
		}

		config[key] = value;
	}
}

bool ConfigUtil::GetBool(BoolSetting boolSetting)
{
	string stringValue = config[GetBoolValue(boolSetting)];
	return stringValue == "1";
}

int ConfigUtil::GetInt(IntSetting intSetting)
{
	string stringValue = config[GetIntValue(intSetting)];
	return stoi(stringValue);
}

float ConfigUtil::GetFloat(FloatSetting floatSetting)
{
	string stringValue = config[GetFloatValue(floatSetting)];
	return stof(stringValue);
}

std::string ConfigUtil::GetString(StringSetting stringSetting)
{
	return config[GetStringValue(stringSetting)];
}

int ConfigUtil::GetKeyBinding(KeyBinding keybinding)
{
	string stringValue = config[GetKeyBindingValue(keybinding)];
	return stoi(stringValue);
}

string ConfigUtil::GetBoolValue(BoolSetting boolSetting)
{
	switch (boolSetting)
	{
	case BoolSetting::UseWireframes:
		return "useWireframes";
	case BoolSetting::BackfaceCull:
		return "backfaceCull";
	case BoolSetting::AutoRotate:
		return "autoRotate";
	case BoolSetting::FullScreenOnStartup:
		return "fullScreenOnStartup";
	default:
		return "";
	}
}

string ConfigUtil::GetIntValue(IntSetting intSetting)
{
	switch (intSetting)
	{
	case IntSetting::WindowWidth:
		return "windowWidth";
	case IntSetting::WindowHeight:
		return "windowHeight";
	default:
		return "";
	}
}

string ConfigUtil::GetFloatValue(FloatSetting floatSetting)
{
	switch (floatSetting)
	{
	case FloatSetting::BackgroundR:
		return "backgroundR";
	case FloatSetting::BackgroundG:
		return "backgroundG";
	case FloatSetting::BackgroundB:
		return "backgroundB";
	case FloatSetting::BackgroundA:
		return "backgroundA";
	default:
		return "";
	}
}

string ConfigUtil::GetStringValue(StringSetting stringSetting)
{
	switch (stringSetting)
	{
	case StringSetting::WindowTitle:
		return "windowTitle";
	case StringSetting::VertexShader:
		return "vertexShader";
	case StringSetting::FragmentShader:
		return "fragmentShader";
	default:
		return "";
	}
}

string ConfigUtil::GetKeyBindingValue(KeyBinding keyBinding)
{
	switch (keyBinding)
	{
	case KeyBinding::RotateXPositive:
		return "KeyBinding_RotateXPositive";
	case KeyBinding::RotateXNegative:
		return "KeyBinding_RotateXNegative";
	case KeyBinding::RotateYPositive:
		return "KeyBinding_RotateYPositive";
	case KeyBinding::RotateYNegative:
		return "KeyBinding_RotateYNegative";

	case KeyBinding::MoveUp:
		return "KeyBinding_MoveUp";
	case KeyBinding::MoveDown:
		return "KeyBinding_MoveDown";
	case KeyBinding::MoveForward:
		return "KeyBinding_MoveForward";
	case KeyBinding::MoveBackward:
		return "KeyBinding_MoveBackward";
	case KeyBinding::MoveLeft:
		return "KeyBinding_MoveLeft";
	case KeyBinding::MoveRight:
		return "KeyBinding_MoveRight";

	case KeyBinding::ScaleUp:
		return "KeyBinding_ScaleUp";
	case KeyBinding::ScaleDown:
		return "KeyBinding_ScaleDown";

	case KeyBinding::NewModel:
		return "KeyBinding_NewModel";
	case KeyBinding::DeleteModel:
		return "KeyBinding_DeleteModel";
	case KeyBinding::Reset:
		return "KeyBinding_Reset";
	case KeyBinding::Quit:
		return "KeyBinding_Quit";

	case KeyBinding::FirstModel:
		return "KeyBinding_FirstModel";
	case KeyBinding::SecondModel:
		return "KeyBinding_SecondModel";
	case KeyBinding::ThirdModel:
		return "KeyBinding_ThirdModel";
	case KeyBinding::FourthModel:
		return "KeyBinding_FourthModel";
	case KeyBinding::FifthModel:
		return "KeyBinding_FifthModel";
	case KeyBinding::SixthModel:
		return "KeyBinding_SixthModel";
	case KeyBinding::SeventhModel:
		return "KeyBinding_SeventhModel";
	case KeyBinding::EighthModel:
		return "KeyBinding_EighthModel";
	case KeyBinding::NinthModel:
		return "KeyBinding_NinthModel";

	case KeyBinding::SaveModelAsBasic:
		return "KeyBinding_SaveModelAsBasic";

	default:
		return "";
	}
}