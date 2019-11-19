#include "Scene.h"

/*
	This method is in it's own file due to it's size and the fact that it doesn't relate to any of the other scene content directly
*/

// Creates lambda functions to be triggered on keypresses
void Scene::BindMovements()
{
	inputManager.RegisterKeyRepeat(KeyBinding::RotateXPositive, [&]()// Callback for rotating the current model positively in the X axis
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddRotation(5.0f, 0.0f, 1.0f, 0.0f);
		}
	});
	inputManager.RegisterKeyRepeat(KeyBinding::RotateXNegative, [&]()// Callback for rotating the current model negatively in the X axis
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddRotation(-5.0f, 0.0f, 1.0f, 0.0f);
		}
	});
	inputManager.RegisterKeyRepeat(KeyBinding::RotateYPositive, [&]()// Callback for rotating the current model positively in the Y axis
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddRotation(5.0f, 1.0f, 0.0f, 0.0f);
		}
	});
	inputManager.RegisterKeyRepeat(KeyBinding::RotateYNegative, [&]()// Callback for rotating the current model negatively in the Y axis
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddRotation(-5.0f, 1.0f, 0.0f, 0.0f);
		}
	});
	inputManager.RegisterKeyRepeat(KeyBinding::MoveUp, [&]()// Callback for translating the current model up in the Y axis
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddTranslation(0.0f, 0.1f, 0.0f);
		}
	});
	inputManager.RegisterKeyRepeat(KeyBinding::MoveDown, [&]()// Callback for translating the current model down in the Y axis
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddTranslation(0.0f, -0.1f, 0.0f);
		}
	});
	inputManager.RegisterKeyRepeat(KeyBinding::MoveForward, [&]()// Callback for translating the current model down in the Z axis
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddTranslation(0.0f, 0.0f, -0.1f);
		}
	});
	inputManager.RegisterKeyRepeat(KeyBinding::MoveBackward, [&]()// Callback for translating the current model up in the Z axis
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddTranslation(0.0f, 0.0f, 0.1f);
		}
	});
	inputManager.RegisterKeyRepeat(KeyBinding::MoveLeft, [&]()// Callback for translating the current model down in the X axis
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddTranslation(-0.1f, 0.0f, 0.0f);
		}
	});
	inputManager.RegisterKeyRepeat(KeyBinding::MoveRight, [&]()// Callback for translating the current model up in the X axis
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddTranslation(0.1f, 0.0f, 0.0f);
		}
	});
	inputManager.RegisterKeyRepeat(KeyBinding::ScaleUp, [&]()// Callback for increasing the scale of the current model
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddScale(1.01f, 1.01f, 1.01f);
		}
	});
	inputManager.RegisterKeyRepeat(KeyBinding::ScaleDown, [&]()// Callback for decreasing the scale of the current model
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddScale(0.99f, 0.99f, 0.99f);
		}
	});
	inputManager.RegisterKeyPress(KeyBinding::NewModel, [&]()// Callback for adding a new model into the scene
	{
		AddModel();
	});
	inputManager.RegisterKeyPress(KeyBinding::DeleteModel, [&]()// Callback for deleting the most recently added model from the scene
	{
		DeleteModel();
	});
	inputManager.RegisterKeyPress(KeyBinding::Reset, [&]()// Callback for resetting the MVPBuilder on the current model
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder() = MVPBuilder();
		}
	});
	inputManager.RegisterKeyPress(KeyBinding::FirstModel, [&]()// Callback for setting the 0th model as the current model
	{
		activeModel = 0;
	});
	inputManager.RegisterKeyPress(KeyBinding::SecondModel, [&]()// Callback for setting the 1st model as the current model
	{
		activeModel = 1;
	});
	inputManager.RegisterKeyPress(KeyBinding::ThirdModel, [&]()// Callback for setting the 2nd model as the current model
	{
		activeModel = 2;
	});
	inputManager.RegisterKeyPress(KeyBinding::FourthModel, [&]()// Callback for setting the 3rd model as the current model
	{
		activeModel = 3;
	});
	inputManager.RegisterKeyPress(KeyBinding::FifthModel, [&]()// Callback for setting the 4th model as the current model
	{
		activeModel = 4;
	});
	inputManager.RegisterKeyPress(KeyBinding::SixthModel, [&]()// Callback for setting the 5th model as the current model
	{
		activeModel = 5;
	});
	inputManager.RegisterKeyPress(KeyBinding::SeventhModel, [&]()// Callback for setting the 6th model as the current model
	{
		activeModel = 6;
	});
	inputManager.RegisterKeyPress(KeyBinding::EighthModel, [&]()// Callback for setting the 7th model as the current model
	{
		activeModel = 7;
	});
	inputManager.RegisterKeyPress(KeyBinding::NinthModel, [&]()// Callback for setting the 8th model as the current model
	{
		activeModel = 8;
	});
	inputManager.RegisterKeyPress(KeyBinding::SaveModelAsBasic, [&]()// Callback for exporting the current model as a .basic
	{
		if (models.size() > activeModel)
		{
			basicModelLoader.Export(models[activeModel]);
		}
	});
}