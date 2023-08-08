#pragma once
#include "../index_windows.cpp"

class WindowsManager {
public:
  static GameObjectBuilder* gameobject_builder_window;
  static GameRoomBuilder* gameroom_builder_window;
  static ScriptEditor* script_editor_window;
  static AssetsManager* assets_manager_window;
};

GameObjectBuilder* WindowsManager::gameobject_builder_window = nullptr;
GameRoomBuilder* WindowsManager::gameroom_builder_window = nullptr;
ScriptEditor* WindowsManager::script_editor_window = nullptr;
AssetsManager* WindowsManager::assets_manager_window = nullptr;