#pragma once
#include "../interfaces/IDisplayWindow.cpp"
#include <vector>

using namespace std;

class WindowsManager {
public:
  static vector<IDisplayWindow*> all_windows;
};

vector<IDisplayWindow*> WindowsManager::all_windows = vector<IDisplayWindow*>();