#include "ConfigUtil.h"
#include <string>

using namespace std;

ConfigUtil::ConfigUtil(FileUtils& _fileUtils) : fileUtils(_fileUtils)
{
	try
	{
		fileUtils.EnsureFolderExists(configFileFolder);
		GetConfigData();
	}
	catch (runtime_error ex)
	{
		CreateDefaultConfigData();
		GetConfigData();
	}
}

// Gets the value of a boolean setting from the config
bool ConfigUtil::GetBool(BoolSetting boolSetting)
{
	string stringValue = config[GetBoolValue(boolSetting)];
	return stringValue == "1";
}

// Gets the value of an int setting from the config
int ConfigUtil::GetInt(IntSetting intSetting)
{
	string stringValue = config[GetIntValue(intSetting)];
	return stoi(stringValue);
}

// Gets the value of a float setting from the config
float ConfigUtil::GetFloat(FloatSetting floatSetting)
{
	string stringValue = config[GetFloatValue(floatSetting)];
	return stof(stringValue);
}

// Gets the value of a string setting from the config
std::string ConfigUtil::GetString(StringSetting stringSetting)
{
	return config[GetStringValue(stringSetting)];
}


// Gets the value of a keybinding from the config
int ConfigUtil::GetKeyBinding(KeyBinding keybinding)
{
	string stringValue = config[GetKeyBindingValue(keybinding)];
	return stoi(stringValue);
}

// Loads in the config data from file
void ConfigUtil::GetConfigData()
{
	config = map<string, string>();

	vector<string> configFile = fileUtils.ReadFileAsLines(configFileLocation);// Read in the config file into lines

	for (int i = 0; i < configFile.size(); i++)// For every line in the file
	{
		string line = configFile.at(i);

		string key = "";
		string value = "";
		bool atEquals = false;

		for (char& c : line)// For every character in the line
		{
			if (c == '=' && !atEquals)// If it is an equals
			{
				atEquals = true;// Declare that an equals has been found and continue the loop
				continue;
			}

			if (!atEquals)// Otherwise, either add it to the key
			{
				key += c;
				continue;
			}

			value += c;// Or the value
		}

		config[key] = value;
	}
}

// Creates the config file with the default config
void ConfigUtil::CreateDefaultConfigData()
{
	fileUtils.SaveFile(defaultFileData, configFileLocation);
}

// Returns the matching key in the config file for the passed in bool setting enum
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

// Returns the matching key in the config file for the passed in int setting enum
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

// Returns the matching key in the config file for the passed in float setting enum
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

// Returns the matching key in the config file for the passed in string setting enum
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

// Returns the matching key in the config file for the passed in key binding enum
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