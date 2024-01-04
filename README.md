# Cookie - V4
Cookie is a **GAME ENGINE** made in C++ on top of SFML graphics library
## Table of contents
1. [Prerequisites](#prerequisites)

   - [Linux](#linux)
   - [Windows](#windows)
   - [MacOS](#windows)

2. [Steps to test](#building-your-first-game)
3. [API](#api)

## Prerequisites

### Linux
```
sudo apt-get install libsfml-dev
```
### Windows
> Coming soon
### MacOS
```
brew install sfml
```

## Steps to test
**STEP 1:** Download/Clone the repository from the version branch you want to work with.  
**STEP 2:** Copy `/includes` folder to your working projects directory.  
**STEP 3:** Create a `main.cpp` file that will serve as the entry point for the program.  
**STEP 4:** Paste the following code in `main.cpp` and put correct path to includes folder
```cpp
#include "{path_to_includes}/CookieEngine.cpp";
#include "{path_to_includes}/Gameroom.cpp";

// Create a new class that inherits from Gameroom
class TemplateRoom : public Gameroom {
public:
    vector<GameObject*> GenerateObjects() override {} // Define gamerooms virtual method
};

int main(){
  // Add TemplateRoom to Global gameroom vector
  GameRoom::AddRoom("FirstRoom", new TemplateRoom());
  
  // Create engine object
  CookieCore* engine = new CookieCore();

  // Setup engine
  engine->CreateWindow(1280, 720);
  engine->ChangeRoom("FirstRoom");
  
  // Start the engine
  engine->Start();
  return 0;
}
```

## API
> Coming soon
