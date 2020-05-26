# SDL/OpenGL Game Framework
## Introduction
This is a game framework/template written in C++, and uses SDL and OpenGL for low-level I/O. This is a personal project where I hope to discover from the ground up just what it takes to make a good game, and if feasible, build a commercial game on top of in the future. I hope others could also use or at least learn from (aspects of) it, as I have.

Inspired by the complexity and freedom of games such as *Dwarf Fortress*, *RimWorld*, *Terraria*, *Minecraft*, *Factorio* etc. that let the player explore and exploit, as well as the simple graphical and mechanical fun of *Minecraft*, *Red Alert 2*, *Amorphous+* etc. that despite their ultimately limited components, provide endless hours of engagement due to how richly said components interact with each other, this template aspires to draw from the best aspects of these games, and is ultimately developed in the direction of open-world action-adventure RPGs and/or colonysims. Due to similar mechanics (world map, units, items/resources etc.), this template could also be modified reasonably easily to make a strategy or hack n' slash game.

On top of the cliché requirements of being fast and powerful, this game template is written with the following aspects in mind:
- **Control**. Specify and process exactly what you want. Clean and fast. 3rd party libraries are limited to the low level, the rest is up to you. (You're free to integrate higher level libraries for your own needs.)
- **Modular**. The code is organized and easy to adapt and maintain, while remaining powerful. OOP is heavily used to sort concerns into sensible places.
- **2D**. Not every game needs to be a 3D FPS. Simplicity makes creating content faster (compare making a 2D sprite sheet vs a 3D rigged model - which one is easier to do and to do *well*?). If executed well, 2D is crisp, runs fast, and can be just as awesome. I wish I could credit all the beautiful 2D games out there, big or small.
- **Portable**. Not as much of a top priority, but there is some beauty in a program that works on multiple systems. The more people who can use it, the better. 3rd party libraries are kept to a minimum, and where they are used, they are checked for portability before they are integrated. At the very least, this project should run on the main PC OSes: Windows, MacOS and Linux.
- **Quality before quantity**. A game isn't good simply because it can list "this" and "that" as a feature on its Store page. The best games are the ones with care poured into making every feature deep and well-integrated into the rest of the game, and that is something indescribable and can only be felt by playing the game.

For an explanation of how this template works and how to use it, read this project's guide [here](guide.md).



## Acknowledgements
I would like to express appreciation for the following tutorials for their technical guidance:
- [Lazy Foo's SDL Tutorial](http://lazyfoo.net/tutorials/SDL) for setting up SDL2.
- [LearnOpenGL](https://learnopengl.com/) for setting up modern OpenGL.

The following subsections list 3rd party resources used in this project. The license is mentioned in brackets.

### 3rd-party Libraries
- [Simple DirectMedia Layer (SDL2)](https://www.libsdl.org/download-2.0.php) (zlib): Hardware interfacing
- OpenGL 3.3: Modern graphics rendering API (should come native with your compiler)
	- [OpenGL Extension Wrangler (GLEW)](http://glew.sourceforge.net/) (Modified BSD/MIT): Support for OpenGL 3+
	- [Simple OpenGL Image Library (SOIL)](http://www.lonesock.net/soil.html) (public): Texture loading
- [FreeType](https://www.freetype.org/) ([FTL](https://git.savannah.gnu.org/cgit/freetype/freetype2.git/tree/docs/FTL.TXT) (BSD-like)): TrueType font support (get the Windows library [here](https://github.com/ubawurinna/freetype-windows-binaries))

### 3rd-party Textures
- LearnOpenGL: [crate.jpg](https://learnopengl.com/img/textures/container.jpg), [awesomeface.png](https://learnopengl.com/img/textures/awesomeface.png)

### Other Resources Used
- [Commissioner font](https://fontesk.com/commissioner-typeface/) (OFL)
- [PT Mono font](https://fontesk.com/pt-mono-typeface/) (OFL)
