# Dork 2
The 2D sequel to the text based combat game

In the late 70s and early 80s, Zork was a popular text-based adventure game. Dork was a first attempt at a text-based combat game. It lacked any kind of graphics and the mechanics needed work.

Now, Dork is back as a 2D game!

### Controls
On the main menu, use the arrow keys to move the selector or change a value. WASD will also work unless the "name" field is selected. Press ENTER to select buttons. In game, use WASD or the arrow keys to move around or select things. Press ESC to to access the pause menu.

### About

Dork 2 was created for [Maximum Monster Month](https://itch.io/jam/maximum-monster-month), a Game Jam hosted on [itch.io](https://itch.io). Although the game was not completed on time and ideas for the game existed before joining the jam, the jam was a necessary incentive to begin development, which continues long after the duration of the jam.

### Legal

Project available under GPLv3. The source code for the original Dork is currently proprietary because it's so bad it's not worth sharing. However, a lot of the original Dork's source code will be reused in Dork 2. In any case, if people are interested, the source code for the original game can be released as well.

Orx game engine available under Zlib license (see [the repository](https://github.com/orx/orx) for details).

Assets used in the game are mostly available under Creative Commons licenses. See CREDITS for more details.

### Contributing/Community

Contributions to the development of Dork 2 are more than welcome! If you would like to contribute assets (music, sprites) or want to improve the codebase, feel free to fork the repository and make a pull request!

If you have any suggestions as to how to improve the game, you can [open a new issue](
https://github.com/Arc676/Dork-2/issues/new).

We also have a [Discord server](https://discord.gg/ay3Td9W) if you want to chat about the game! If you don't have a GitHub account, you can also report bugs and make suggestions here.

### Compiling Dork 2 from Source

If you would like to compile Dork 2 from source so you can check out development progress or you wish to make modifications, use `git clone` or GitHub's interface to download the source code and the included resources for compilation. The repository includes simple methods for compilation on any platform.
- On Mac, use the associated Xcode project to compile the executable. Note that the output program is a simple executable file rather than an app package (.app) like normal applications. For releases, I package Dork 2 as an app manually.
- On Linux, use `make` and the included `Makefile` to compile Dork 2. The target is `dork2`. Defining the `DEBUG` macro allows debugging. Currently, no `install` target is implemented. The executable is compiled to `Build/Dork 2` relative to the root of the repository. Unless you move `lib/liborx.so` to a location for custom libraries, you will need to update your library path to include `lib/`, as the executable requires the dynamically linked Orx library. You can do this by running `export LD_LIBRARY_PATH=$(readlink -f lib)` when in the root of the repository (or using a relative path in place of `lib`). Once the library is in your library path, you will be able to run the executable file. Note that the game assets must be in the same directory as the executable file. This is done automatically by the `Makefile`, but if you wish to move the executable (or make it accessible from elsewhere) you will need to move all the assets as well or create an alias that includes an absolute path to the executable file. Object code is stored in the `obj/` directory relative to the root.
- On Windows, you can compile Dork 2 with Visual Studio using the included VS project. Note that the output EXE must be in the same directory as the game assets.
Please note that, during development, these compilation methods may diverge. Certain project files may become outdated if new assets are added while working on another platform (e.g. if I'm working on Linux and a new asset is added, neither the Xcode nor Visual Studio projects will include references to said asset until I'm on their respective platforms).

The repository includes files for the custom font, Manaspace. `Assets/Other` contains a file with all the required characters for the game. Using Orx's `orxfontgen` tool, it is possible to create assets for the font should this be necessary (e.g. make a new copy of the font with a different size). This tool is not tracked in this repository. Its source code can be found in the Orx repository and compiled with the included Makefile.
