#pragma once
#include <iostream>

using namespace std;

class Profiler {
private:
    static void Message(string text, string color) {
        if (MESSAGES_ENABLED)
            cout << color << " " << text << " " << "\033[0m" << endl;
    }

public:
    static bool MESSAGES_ENABLED;

    static string FG_BLUE;
    static string BG_RED;
    static string BG_YELLOW;
    static string BG_GREEN;

    static void Warning(string text) {
        Message(text, BG_YELLOW);
    }

    static void Error(string text) {
        Message(text, BG_RED);
        exit(69);
    }

    static void Success(string text) {
        Message(text, BG_GREEN);
    }

    static void Info(string text) {
        Message(text, FG_BLUE);
    }
};

bool Profiler::MESSAGES_ENABLED = true;
string Profiler::FG_BLUE = "\033[1;34m";
string Profiler::BG_RED = "\033[1;41m";
string Profiler::BG_YELLOW = "\033[1;43m";
string Profiler::BG_GREEN = "\033[1;42m";