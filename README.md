# Pong

<!-- Reserve space of an image of the game -->
![First Working Game](resources/game_play.png)

![C](https://img.shields.io/badge/language-C-blue)
![C++](https://img.shields.io/badge/language-C++-blue)
![GLSL](https://img.shields.io/badge/language-GLSL-blue)
![Linux](https://img.shields.io/badge/OS-Linux-lightgrey)
![Make](https://img.shields.io/badge/build-Make-orange)
![KHR](https://img.shields.io/badge/library-KHR-green)
![GLM](https://img.shields.io/badge/library-GLM-green)
![GLAD](https://img.shields.io/badge/library-GLAD-green)
![GLFW](https://img.shields.io/badge/library-GLFW-green)
![SFML](https://img.shields.io/badge/library-SFML-green)
![MVC](https://img.shields.io/badge/architecture-MVC-red)

I've been steadily going through [this site](https://learnopengl.com/) to learn OpenGL. One day, the site was down (restored within a day), so I decided to test what I already knew and make Pong from scratch with OpenGL. This is the result.

"Art" and text were created using [GIMP](https://www.gimp.org/). Soudn effects were created using [jsfxr](https://sfxr.me/). The [game over tune](resources/audio/gameover.wav) was made with [FamiStudio](https://famistudio.org/).

## Compiling

### Linux

Before running `make`, you'll need to ensure you have SFML's audio component and GLFW installed. You can obtain both with the following commands or by following the links to their respective websites.

[SFML](https://www.sfml-dev.org/development.php)

	sudo apt-get install libsfml-dev

[GLFW](https://www.glfw.org/)

	sudo apt-get install libglfw3
	sudo apt-get install libglfw3-dev

Other dependencies that are already included in the repository can be found in the [include](include) directory.

To complete the compilation, simply run the makefile with

	make

Your executable will be found at `bin/pong`.

### Have Fun!