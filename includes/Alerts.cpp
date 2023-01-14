#pragma once
#include <iostream>

using namespace std;

class Alerts {
private:
    static void Message(string text, string color) {
        cout << color << " " << text << " " << "\033[0m" << endl;
    }
public:
    static string BG_RED;
    static string BG_YELLOW;
    static string BG_GREEN;

    static void Warning(string text) {
        text = "[WARNING] " + text;
        Message(text, BG_YELLOW);
    }

    static void Error(string text) {
        text = "[ERROR] " + text;
        Message(text, BG_RED);
        exit(69);
    }

    static void Success(string text) {
        text = "[SUCCESS] " + text;
        Message(text, BG_GREEN);
    }
};

string Alerts::BG_RED = "\033[1;41m";
string Alerts::BG_YELLOW = "\033[1;43m";
string Alerts::BG_GREEN = "\033[1;42m";