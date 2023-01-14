#include <SFML/Network.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main() {

    TcpSocket socket;

    Socket::Status status = socket.connect("127.0.0.1", 8000);
    if (status != Socket::Done) {
        cout << "Error connecting to server!" << endl;
    } else {
        cout << "Connected Successfuly!" << endl;
    }

    return 0;
}