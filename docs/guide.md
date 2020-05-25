# Guide

NOTICE: Due to the project still being in rapid development and many APIs and functionalities subject to change, the detailed architecture is not documented, but should be evident from the code and comments. This guide instead focusses on big-picture descriptions and visions that would help to understand how the various parts cohere. Do contact the authors of this project if anything is unclear.



## Setting up
### Prerequisites
- Highly recommended: Latest version of [Code::Blocks](http://www.codeblocks.org)
- A C++ compiler (MinGW G++ already included with Code::Blocks)

### Setting up the project on your computer
Windows:

- Clone this repo to your computer.
- Grab the libraries that are stated in the readme and put the .dlls in the same location as where the executable will be.
	- DLLs you will need: `freetype`, `SDL2`, `zlib1`
	- If you are using Code::Blocks, you can leave the DLLs in the root directory.
- Make sure your C++ compiler knows where to find the libraries and headers.
- Compile the source code with these options: `-DGLEW_STATIC -lmingw32 -lSDL2main -lSDL2 -lglew32s -lSOIL -lopengl32 -lfreetype`
	- This is already set up for you if you have Code::Blocks on your computer: Just open the .cbp project file.
	- Note: The MinGW compiler will give a warning saying ".drectve \`/DEFAULTLIB:"LIBCMT" /DEFAULTLIB:"OLDNAMES" ' unrecognized". This warning is, from what I've read, due to an incompatibility with GLEW and MinGW, and is harmless. You just have to ignore it.
- Run the program and interact with it using the mouse and keyboard. Try out the features in the next subsection.

### Demo Features / Verifying the setup
- Currently, <kbd>Q</kbd> switches between the `MenuScene` and `GameScene`, as does clicking the Widget at the topleft of the screen.
- In the `GameScene`, there are three entities. The center entity is player-controlled.
	- <kbd>SPACE</kbd> pauses/unpauses the game.
	- <kbd>W</kbd><kbd>A</kbd><kbd>S</kbd><kbd>D</kbd> or <kbd>↑</kbd><kbd>↓</kbd><kbd>←</kbd><kbd>→</kbd> moves the player.
	- The player can bump the other two entities by moving into them.
	- The mouse can held down to make the player fire projectiles in the direction of the mouse. These projectiles can be fired at the other two entities to damage and eventually kill them. When killed, the entities explode into particles.
	- The mouse can also be used to hover over and click on the widgets on the left of the screen. Clicking them spawns particles.
	- The mouse may also be moved to the edges of the screen to pan the camera.
	- The camera can also be zoomed in and out by scrolling the mouse wheel.
	- The camera can be reset by clicking the mouse wheel.



## Design
This section describes how the code base is organized.

### Architecture
![](ArchitectureDiagram.png)

The `MainApp` hosts all the other components, and tracks application-wide data such as frames per second (FPS). It contains methods to initialize, run and de-initialize the whole program. It also contains methods that allow `Message`s to affect its underlying data.

Independent of `MainApp` and indeed the rest of the program is the `MessageHandler`. `MessageHandler` is a singleton class which collects `Message`s posted to it by any part of the main program, and lets a `MainApp` instance clear the `Message`s.

When the whole program starts, an instance of `MainApp` is created. `init()` is called, then `run()`. `run()` executes an endless loop:

- Poll for inputs
	- `MainApp` tells `UiManager` to pass `Scene` raw inputs.
	- `Scene` parses the inputs into internal actions that are effected immediately, and `Message`s that are posted to `MessageHandler`.
	- `MainApp` clears all `Message`s from `MessageHandler`.
- Update
	- `MainApp` tells `Scene` to update itself by 1 tick. `Scene` may post more `Message`s.
	- `MainApp` clears `Message`s.
- Draw
	- `MainApp` tells `Scene` to draw, passing it `UiManager`.
	- `Scene` tells `UiManager` what to draw based on its `Widget`s and `Model`.

When `run()` is exited, `deinit()` is called, then the program ends.

### UiManager
![](UiManagerClassDiagram.png)

The `UiManager` handles all low-level I/O, including setting up I/O functionality, maintaining I/O info, and providing an interface for the rest of the program to make I/O calls with. Specific duties include:

- Initializing and deinitializing I/O resources, such as the window, SDL, and OpenGL.
- Breaking down input - such as keyboard and mouse signals - to feed to `Scene`.
- Providing `Scene` an interface to make output calls to, such as display and audio.

The `UiManager` contains several subclasses to handle specialized areas:

- `MouseState`, `KeyboardState` are used to record the input state of the input devices.
- `ShaderProgram` defines and provides an interface for the shader program used by OpenGL. In particular, it helps to load and compile GLSL shader code, and defines an interface to load uniform values into them.
- `SpriteManager` handles `Sprite`s: all graphical elements are `Sprite`s. There are two main kinds of `Sprites`: `TexturedSprite`s which host and render a texture, and `GeometricSprite`s which render coloured geometric primitives.
	- `Texture`s handle individual image loading and handling with OpenGL.
	- `Sprite`s handle how to render things: VAOs and VBOs. They expose a `draw()` function, which would draw their data. It is up to the `UiManager` to specify parameters to the `ShaderProgram` to transform this output to the desired position and scale.
	- The `SpriteManager` lets the developer specify and load all the `Sprite`s to be used in the game. It is supported by a `SpriteId` enum.
- `TextManager` loads fonts and generates textures for each character of each typeface and font size, each managed by their own `GlyphSprite` class.
	- The `GlyphSprite`s are managed by `TextManager`, separately from the `SpriteManager`.
	- `TextManager`'s API only allows to print individual characters; an actual string of text is handled by `UiManager` since that requires UI position transformations from one character to the next, which is out of the scope of `TextManager`.

### Scene
![](SceneClassDiagram.png)

The `Scene` is the core of the game. It is conceptually split into two sections: The UI - handled by the `WidgetManager` - and the Model - handled by the `ModelManager`.

Furthermore, There are different derivatives of `Scene`, corresponding what what environments the player might encounter while navigating the app. In particular, there is currently a `MenuScene` - the environment of the main menu and game lobby, and a `GameScene` - the actual game environment. The `MainApp` tracks one `Scene`, which it can construct and destruct as needed.

The `Scene` has three external functionalities:
- Accept user input and interpret them into actions on itself, based on its current state. User input is in terms of keyboard and mouse events and state, and would typically be called from the `UiManager`, although they can technically be called from anywhere.
- Update its internal state (by one game tick).
- Tell a `UiManager` how to draw its state.

#### Widgets
The `WidgetManager` handles the GUI of the `Scene`. The GUI is defined in terms of `Widget`s. `Widget`s essentially define a region in screen space. They may have a defined action upon being clicked, and also have a defined draw function to visually indicate where they are when the app runs. They can be used to display information such as text, or provide a region for the player to click in order to activate a certain function. `Widget`s are fixed to the screen space; they move around with the in-game camera. `Widget`s are always drawn on top of any other object from the Model.

#### Model
![](ModelClassDiagram.png)

The Model contains the actual state of the game, as well as methods to interact with, update and draw them. The parent `Scene` may pass commands to the Model directly, or it may also pass user input to the `WidgetManager` which would then translate them into Model commands.

While the `GameScene` makes the heaviest use of the Model, other `Scene`s may also use the Model to display backdrops and animations.

The `ModelManager` is a base class that tracks camera and timing information about the game state, and defines methods on camera manipulation, conversion between game and screen coordinates, drawing to the screen, and updating its own state based on input or a game tick. Its derivatives would track actual game entities using `EntityManager`s, and define further methods to manipulate the game entities, such as spawning new entities.