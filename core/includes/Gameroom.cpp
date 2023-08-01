#pragma once
#include "Gameobject.cpp"
#include "Alerts.cpp"
#include <vector>

using namespace std;

class GameRoom {
public:
  static vector<pair<string, GameRoom*> > rooms;
  
  static void AddRoom(string title, GameRoom* room) {
    if (room == nullptr) Alerts::Error("Trying to append a GameRoom that is pointing to NULL");

    GameRoom::rooms.push_back(make_pair(title, room));
  }

  static GameRoom* GetRoom(string title) {
    GameRoom* room = nullptr;

    for(size_t i = 0; i < GameRoom::rooms.size(); i++) {
      if (GameRoom::rooms.at(i).first == title) {
        room = GameRoom::rooms.at(i).second;
        break;
      }
    }
    
    return room;
  }

  virtual vector<GameObject*> GenerateObjects() = 0;
};

vector<pair<string, GameRoom*> > GameRoom::rooms = vector<pair<string, GameRoom*> >();