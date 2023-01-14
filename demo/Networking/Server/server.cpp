#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

int main() {

    bool isServer = true;
    TcpListener listener;
    vector<TcpSocket*> clients;

    if (listener.listen(8000) != Socket::Done) {
        cout << "Failed to open server!" << endl; 
    }

    TcpSocket client;
    if (listener.accept(client) != Socket::Done) {
        cout << "Client failed to connect!" << endl;
    } else {
        cout << "Client connected!" << endl; 
    }

    return 0;
}