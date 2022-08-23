# Cookie - V1
Cookie is a **GAME ENGINE** made fully in C++ on top of SFML graphics library
## Table of contents
1. [Prerequisites](https://github.com/ErnestsEida/Cookie/edit/master/README.md#prerequisites)

   - [Linux](https://github.com/ErnestsEida/Cookie/edit/master/README.md#linux)
   - [Windows](https://github.com/ErnestsEida/Cookie/edit/master/README.md#windows)
   - [MacOS](https://github.com/ErnestsEida/Cookie/edit/master/README.md#windows)

2. [Building your first game](https://github.com/ErnestsEida/Cookie/edit/master/README.md#building-your-first-game)
3. [Classes](https://github.com/ErnestsEida/Cookie/edit/master/README.md#classes)

## Prerequisites

### Linux
```
sudo apt-get install libsfml-dev
```
### Windows
> Not available for this version
### MacOS
```
brew install sfml
```

## Building your first game
**STEP 1:** Create a main.cpp that will hold the game main loop  
**STEP 2:** include `CookieEngine.cpp` file into file created earlier  
**STEP 3:** Initialize Engines window ( without initialization you won't be able to run the game ):
```cpp
#include "{path_to_includes}/CookieEngine.cpp";
#include <iostream>

using namespace std;

int main(){
  // Create a new instance of engine
  CookieEngine engine;
  
  // Initialize window
  engine.InitWindow(1280, 720, "Game Window");
  
  // Run to show game window
  engine.Run();
  return 0;
}
```

Creating GameObjects on screen can be done anywhere before `engine.Run()` call

## Classes

### GameObject
#### Methods
|Type | Name | Accessability |
|:---:|:-----|:-------------:|
| --- | [Constructors](https://github.com/ErnestsEida/Cookie/edit/master/README.md#constructors) | Public |
| int | [GetX]() | Public |
| int | [GetY]() | Public |
| int | [GetZ]() | Public |
| string | [GetObjectName]() | Public |

#### Constructors
