# SDL/OpenGL Game Framework
![](teaser.png)

## Introduction
This is a game framework/template written in C++, and uses SDL and OpenGL for low-level I/O. It is developed towards 2D games with a top-down view, with a tile-based map but free-moving entities.

Disclaimer: The project is still under development and I do not recommend building on top of it in its current state, as the core structure does not support some major functionalities yet. Once ready, the project will be marked v1.0 and this disclaimer will be removed.

This is a personal project where I hope to discover from the ground up just what it takes to make a good game, and if feasible, build a commercial game on top of in the future. I hope others could also use or at least learn from (aspects of) it, as I have.

This project is inspired by:
- The content and freedom of strategy and outcome of open-world games such as [*Dwarf Fortress*](https://www.bay12games.com/dwarves/), [*RimWorld*](https://rimworldgame.com/), [*Terraria*](https://terraria.org/), [*Minecraft*](https://www.minecraft.net/), [*Factorio*](https://factorio.com/) etc. that let the player explore and exploit the world as a character or colony director.
- The mechanical interest of [*Minecraft*](https://www.minecraft.net/), *Red Alert 2*, [*Amorphous+*](https://armorgames.com/play/2044/amorphous-plus) etc. that despite their ultimately limited components, provide endless hours of engagement due to how richly said components interact with each other.
- The simple tactile experience of the above games as well as [*Decision 3*](https://armorgames.com/play/16123/decision-3) etc., where even doing the same thing over and over is smooth and satisfying without a need for extrinsic reward like gold or XP.

This template aspires to draw from the best aspects of these games, and is ultimately developed in the direction of open-world action-adventure RPGs and/or colonysims. Due to similar features and mechanics (world map, units, buildings, items/resources etc.), this template could also be modified reasonably easily to make a strategy or hack n' slash / shoot 'em up game.

On top of the cliché requirements of being fast and powerful, this game template is written with the following aspects in mind:
- **Control**. Specify and process exactly what you want. Clean and fast. 3rd party libraries are limited to the low level, the rest is up to you. (You're free to integrate higher level libraries for your own needs.)
- **Modular**. The code is organized and easy to adapt and maintain, and strives for a balance between programmer restriction to manipulate data in a controlled and safe way, and programmer freedom to implement new and novel features. OOP is heavily used to sort concerns into sensible places.
- **2D**. Not every game needs to be a cinematic 3D FPS. Simplicity makes creating content faster (compare making a 2D sprite sheet vs a 3D rigged model - which one is easier to do and to do *well*?). If executed well, 2D is crisp, runs fast, and can be just as awesome. I wish I could credit all the beautiful 2D games out there, big or small.
- **Portable**. Not as much of a top priority, but there is some beauty in a program that works on multiple systems. The more people who can use it, the better. 3rd party libraries are kept to a minimum, and where they are used, they are checked for portability before they are integrated. At the very least, this project should run on the main PC OSes: Windows, MacOS and Linux.
- **Quality before quantity**. A game isn't good simply because it can list "this" and "that" as a feature on its Store page. The best games are the ones with care poured into making every feature deep and well-integrated into the rest of the game, and that is something indescribable and can only be felt by playing the game.

For an explanation of how this template works and how to use it, read this project's [guide](guide.md).



## Roadmap
The [issue tracker](https://github.com/OrangeJuice7/SDL-OpenGL-Game-Framework/issues) serves as a general todo list, although it may not list all implemented or planned features as some features are added ad-hoc.

Desirable milestones:
- [ ] Alpha 1.0: Able to build a functional and reasonably featured shoot 'em up: Player, enemies, weapons, projectiles, levels, shop etc. (by end of 2020)
- [ ] Alpha 2.0: Able to build an RPG/dungeon crawler: Items, map/dungeon generation, friendly NPCs, dialog, questlines etc.
- [ ] Alpha 3.0: Able to build a RTS/colonysim: Buildings, player command system, AI task manager, fog of war etc.



## Acknowledgements
I would like to express appreciation for the following tutorials for their technical guidance:
- [Lazy Foo's SDL Tutorial](http://lazyfoo.net/tutorials/SDL) for setting up SDL2.
- [LearnOpenGL](https://learnopengl.com/) for setting up modern OpenGL.

### 3rd-party Resources
The following subsections list 3rd party resources used in this project. The license is mentioned in brackets.

#### Libraries
- [Simple DirectMedia Layer (SDL2)](https://www.libsdl.org/download-2.0.php) (zlib): Hardware interfacing
- OpenGL 3.3: Modern graphics rendering API (should come native with your compiler)
	- [OpenGL Extension Wrangler (GLEW)](http://glew.sourceforge.net/) (Modified BSD/MIT): Support for OpenGL 3+
- [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) and [stb_image_write](https://github.com/nothings/stb/blob/master/stb_image_write.h) (public): Texture loading and saving respectively
- [FreeType](https://www.freetype.org/) ([FTL](https://git.savannah.gnu.org/cgit/freetype/freetype2.git/tree/docs/FTL.TXT) (BSD-like)): TrueType font support (get the Windows library [here](https://github.com/ubawurinna/freetype-windows-binaries))

#### Textures
- LearnOpenGL: [crate.jpg](https://learnopengl.com/img/textures/container.jpg), [awesomeface.png](https://learnopengl.com/img/textures/awesomeface.png)
- [elf_f_idle R.png](https://0x72.itch.io/dungeontileset-ii) (CC-0)
- [explosion.png](https://opengameart.org/content/iron-plague-explode3bmp) (CC-0)

#### Other Resources
- [Commissioner font](https://fontesk.com/commissioner-typeface/) (OFL)
- [PT Mono font](https://fontesk.com/pt-mono-typeface/) (OFL)
