#include "includes/CookieEngine.cpp"

// Create a new class that inherits from Gameroom
class TemplateRoom : public GameRoom {
public:
  // Define gamerooms virtual method
  vector<GameObject *> GenerateObjects() override {
    return vector<GameObject *>();
  }
};

int main() {
  // Add TemplateRoom to Global gameroom vector
  GameRoom::AddRoom("FirstRoom", new TemplateRoom());

  // Create engine object
  CookieCore *engine = new CookieCore();

  // Setup engine
  engine->CreateWindow(1280, 720);
  engine->ChangeRoom("FirstRoom");

  // Start the engine
  engine->Start();
  return 0;
}
