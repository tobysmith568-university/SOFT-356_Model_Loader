# SOFT-356_Model_Loader

> .obj and .dae model loader and renderer with basic controls 

## Software and Libraries
- Visual Studio 2019 v16.3.9
- GLM v0.9.9.600
- nupenGL v0.1.0.1

## Usage

#### Compilation

The only setup for compiling this solution is to restore the NuGet packages. This software has only been written with Windows in mind.

#### Execution

The `.exe` can be run by double-clicking it, but should any errors occur and the program shut down then you will not be able to see the error message. As such, it is recommended that you open a command prompt, navigate to the directory of the `.exe` and run it from within that prompt. This will keep the window open when the program closes and any error messages can be read. 

### Config

All the functionality of this software is configurable via the [config.dat file](ModelLoader/media/config.dat) located in the `/media` folder next to the `.exe`. Should the folder or file not exist then the program will attempt to create them on startup. If the program has to create the `config.dat` file then it will also create the default shaders alongside it.  
Config within that file is a list of key/value pairs and sits in the following categories:
- Window options
- Background colour
- Render options
- Shaders
- Keybindings
	- Model Rotation
	- Model Translation
	- Model Scale
	- Model Options
	- Window Options
	- Current Model Swapping
	- Exporting

Boolean options evaluate to `true` if they are equal to `1`, else they are `false`.

All of the key bindings within the config file begin with the prefix `KeyBinding_`. In this README, key bindings are shown without the prefix and then give the default key in brackets, eg, `MoveForward (W)` or `FirstModel (1)`. In the config file, the bound key is represented by a number, the relationships between the keys on a keyboard and these numbers can be found [here on the GLFW website](https://www.glfw.org/docs/latest/group__keys.html).

### Functionality

When the program opens you should see an empty window showing only the configured background colour, by default, this is a pale blue. To add a model you need to press the `NewModel (N)` key. This will take the context away from the OpenGL window and back to the console window where it will prompt you for a file path to a model; the path can be absolute or relative to the `.exe`. On pressing enter, the context will then return to the OpenGL window. If the model is large then the program will lock up while it loads in the new model. On a modern machine, files like [creeper.obj](ModelLoader/Obj/Creeper.obj) should instantly, files like [low_poly_boat.obj](ModelLoader/Obj/low_poly_boat.obj) should take around 10 seconds, and files like [low_poly_boat.dae](ModelLoader/Dae/low_poly_boat.dae) should take just over 2 minutes.

Any model which is loaded into the scene can be manipulated while it is the currently active model. The `FirstModel (1)`, `SecondModel (2)` etc., keybindings can be used to swap the active model. Those 9 key bindings represent the first 9 models which are loaded into the scene, should there be more than 9 models loaded into the scene at a single time then any additional models past the 9th cannot be manipulated.

The `DeleteModel (Delete)` key binding can be used to remove models from the scene. It will always remove the model which was most recently added, not the currently active model.

The `Reset (R)` key binding can be used to reset the position, rotation, and scale of the currently active model.

The `SaveModelAsBasic (F1)` key binding can be used to export the currently active model into a file format I have developed called a `.basic`. Pressing this key binding will switch the context to the console window where it will ask you to enter a file location for where the model should be saved to; this path can be absolute or relative to the `.exe`. Please note that exporting will overwrite any existing file with the same name without warning. The file location you supply needs to contain the `.basic` file extension. Once a file has been exported it can be re-imported like any other `.obj` or `.dae`. It should be noted that the exported `.basic` requires the same texture images as the `.obj` or `.dae` it was created from - the export process will not duplicate the texture image file. If you export to a different folder, or do not copy the image file yourself, the new `.basic` will not be able to load in.

## Code Structure

### Utilities

Large amounts of functionality within the program is broken down and encapsulated within stateless utility classes:
- `ConfigUtil` - used to read from the config.dat file
- `ConsoleUtil` - used to read from and write to the console window
- `FileUtils` - many different actions for interacting with files, folder, and file paths
- `GLEWUtil` - used to interact with the GLEW library
- `GLFWUtil` - used to interact with the GLFW library
- `InputManager` - used to register keyboard interactions and execute callback functions when those actions occur. (Note that this class is not stateless like the others as it stores the keyboard interactions to be executed)
- `ModelLoaderFactory` - used to return a model loader based on the file path it is given

These utility classes are all instantiated once within the main method are they then passed around wherever they are needed via constructor injection. Many of these classes rely on others.

### Model Loading

Each model loader class within the program extends the abstract class `IModelLoader`. When the `ModelLoaderFactory` is handed a file path, it returns an instance of the `IModelLoader` which is designed to handle the file in that path. Currently, there are three implementations:

- .obj (and .mtl and .png)
- .dae (and .png)
- .basic (and .png)

### Core

The core program is broken down into the following structure:

- Scene
	- Shader Program
	- Models[]
		- Materials[]
		- MVP
		- Objects[]
			- Meshes[]
				- VAO
				- Vertices VBO
				- Indices EBO
				- Material&
				- Shader Program&

Details:

- There is a single `Scene` within the program, this represents what the user sees
- The `Shader Program` sits at the `Scene` level and remains constant after init
- The different `Model`s all sit within the `Scene`. Once per game tick, when the `Scene` is updated it must also call an update method on all of the `Model`s
- A `Model` holds all the different `Material`s that any of its child objects might use
- A `Model` has an MVP and it sets this as the current one each game tick before it then calls an update method on all of it's `Objects`
- `Objects` only act as a container for `Mesh`es. They exist to mirror the structure found within different model file types. When an `Object` is updated it must update all of it's `Mesh`es
- A `Mesh` contains the data required for OpenGL to render something. It also has references to a single `Material` and the `Shader program`
