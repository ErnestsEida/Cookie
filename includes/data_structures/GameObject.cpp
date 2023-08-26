#pragma once
#include <iostream>
#include "../helpers/generator.cpp"

using namespace std;

class GameObject {
public:
  string name, id;

  GameObject(string name) {
    this->id = Generator::GenerateID();
    this->name = name;
  }
};