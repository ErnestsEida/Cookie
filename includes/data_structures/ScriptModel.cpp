#pragma once
#include <iostream>
#include "../helpers/generator.cpp"

using namespace std;

class ScriptModel {
public:
  string name, content, id;

  ScriptModel(string name, string content = "") {
    this->id = Generator::GenerateID();
    this->name = name;
    this->content = content;
  }
};