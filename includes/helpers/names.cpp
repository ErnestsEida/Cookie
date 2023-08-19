#pragma once
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

string processName(string text) {
  replace(text.begin(), text.end(), ' ', '_');
  return text;
}