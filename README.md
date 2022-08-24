# Cookie - V1
Cookie is a **GAME ENGINE** made fully in C++ on top of SFML graphics library
## Table of contents
1. [Prerequisites](#prerequisites)

   - [Linux](#linux)
   - [Windows](#windows)
   - [MacOS](#windows)

2. [Building your first game](#building-your-first-game)
3. [Classes](#classes)

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
|Type | Accessability | Name | Description |
|:---|:-----:|:-------------|:------------|
| int | public | GetX | Return value of gameobjects x coordinate |
| int | public | GetY | Return value of gameobjects y coordinate |
| int | public | GetZ | Return value of gameobjects z index |
| string | public | GetObjectName | Return gameobjects name |
| string | public | GetTag | Return gameobjects tag |
| vector<Drawables*> | public | GetDrawables | Returns all drawable parts of gameobject |
| FloatRect* | public | Get_Collider | Returns gameobjects collider as Float rectangle |
