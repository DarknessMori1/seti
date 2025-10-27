#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

const int PORT = 8080;
const int BUFFER_SIZE = 1024;
int main(){
    cout << "сервер!" << endl;
    int serverSocket=socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0){
        cerr << "ошибка!";
        return 0;
    }
    cout << "Сокет создан!"<<endl;

    sockaddr serverAddr;
}