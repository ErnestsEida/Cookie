#pragma once
#include <iostream>
#include "../helpers/generator.cpp"

using namespace std;

class ScriptModel {
private:
  string id;

public:
  string name, content;

  ScriptModel(string name, string content = "") {
    this->id = Generator::GenerateID();
    this->name = name;
    this->content = content;
  }
};