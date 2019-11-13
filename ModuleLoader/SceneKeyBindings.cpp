#include "Scene.h"

void Scene::BindMovements()
{
	inputManager.RegisterKeyRepeat(KeyBinding::RotateXPositive, [&]()
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddRotation(5.0f, 0.0f, 1.0f, 0.0f);
		}
	});
	inputManager.RegisterKeyRepeat(KeyBinding::RotateXNegative, [&]()
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddRotation(-5.0f, 0.0f, 1.0f, 0.0f);
		}
	});
	inputManager.RegisterKeyRepeat(KeyBinding::RotateYPositive, [&]()
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddRotation(5.0f, 1.0f, 0.0f, 0.0f);
		}
	});
	inputManager.RegisterKeyRepeat(KeyBinding::RotateYNegative, [&]()
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddRotation(-5.0f, 1.0f, 0.0f, 0.0f);
		}
	});
	inputManager.RegisterKeyRepeat(KeyBinding::MoveUp, [&]()
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddTranslation(0.0f, 0.1f, 0.0f);
		}
	});
	inputManager.RegisterKeyRepeat(KeyBinding::MoveDown, [&]()
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddTranslation(0.0f, -0.1f, 0.0f);
		}
	});
	inputManager.RegisterKeyRepeat(KeyBinding::MoveForward, [&]()
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddTranslation(0.0f, 0.0f, -0.1f);
		}
	});
	inputManager.RegisterKeyRepeat(KeyBinding::MoveBackward, [&]()
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddTranslation(0.0f, 0.0f, 0.1f);
		}
	});
	inputManager.RegisterKeyRepeat(KeyBinding::MoveLeft, [&]()
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddTranslation(-0.1f, 0.0f, 0.0f);
		}
	});
	inputManager.RegisterKeyRepeat(KeyBinding::MoveRight, [&]()
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddTranslation(0.1f, 0.0f, 0.0f);
		}
	});
	inputManager.RegisterKeyRepeat(KeyBinding::ScaleUp, [&]()
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddScale(1.01f, 1.01f, 1.01f);
		}
	});
	inputManager.RegisterKeyRepeat(KeyBinding::ScaleDown, [&]()
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder().AddScale(0.99f, 0.99f, 0.99f);
		}
	});
	inputManager.RegisterKeyPress(KeyBinding::NewModel, [&]()
	{
		AddModel();
	});
	inputManager.RegisterKeyPress(KeyBinding::Reset, [&]()
	{
		if (models.size() > activeModel)
		{
			models[activeModel].GetMVPBuilder() = MVPBuilder();
		}
	});
	inputManager.RegisterKeyPress(KeyBinding::FirstModel, [&]()
	{
		activeModel = 0;
	});
	inputManager.RegisterKeyPress(KeyBinding::SecondModel, [&]()
	{
		activeModel = 1;
	});
	inputManager.RegisterKeyPress(KeyBinding::ThirdModel, [&]()
	{
		activeModel = 2;
	});
	inputManager.RegisterKeyPress(KeyBinding::FourthModel, [&]()
	{
		activeModel = 3;
	});
	inputManager.RegisterKeyPress(KeyBinding::FifthModel, [&]()
	{
		activeModel = 4;
	});
	inputManager.RegisterKeyPress(KeyBinding::SixthModel, [&]()
	{
		activeModel = 5;
	});
	inputManager.RegisterKeyPress(KeyBinding::SeventhModel, [&]()
	{
		activeModel = 6;
	});
	inputManager.RegisterKeyPress(KeyBinding::EighthModel, [&]()
	{
		activeModel = 7;
	});
	inputManager.RegisterKeyPress(KeyBinding::NinthModel, [&]()
	{
		activeModel = 8;
	});
}