#pragma once
#include <iostream>
#include <map>
#include <cstring>

#include <SFML/Window/Keyboard.hpp>

using namespace sf;
using namespace std;

class KeyInput
{
public:
    static map<Keyboard::Key, bool> current_key_states;
    static map<Keyboard::Key, bool> previous_key_states;

    static map<Keyboard::Key, bool> SetDefaultKeyStates()
    {
        map<Keyboard::Key, bool> keys;

        for (int i = 0; i < Keyboard::KeyCount; i++)
        {
            keys.insert(pair<Keyboard::Key, bool>((Keyboard::Key)i, false));
        }

        return keys;
    }

    static void UpdateKeyStates()
    {
        for (int i = 0; i < Keyboard::KeyCount; i++)
        {
            KeyInput::previous_key_states[(Keyboard::Key)i] = KeyInput::current_key_states[(Keyboard::Key)i];
            KeyInput::current_key_states[(Keyboard::Key)i] = Keyboard::isKeyPressed((Keyboard::Key)i);
        }
    }

    static bool OnKey(Keyboard::Key key)
    {
        return KeyInput::current_key_states[key];
    }

    static bool OnKeyDown(Keyboard::Key key)
    {
        return (KeyInput::current_key_states[key] && !KeyInput::previous_key_states[key]);
    }

    static bool OnKeyUp(Keyboard::Key key)
    {
        return (!KeyInput::current_key_states[key] && KeyInput::previous_key_states[key]);
    }
};

map<Keyboard::Key, bool> KeyInput::current_key_states = KeyInput::SetDefaultKeyStates();
map<Keyboard::Key, bool> KeyInput::previous_key_states = KeyInput::SetDefaultKeyStates();