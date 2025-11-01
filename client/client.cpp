#include <iostream>
#include <string>
#include <cstring>
#include <cstdint>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

const char* SERVER_IP = "127.0.0.1";
const int SERVER_PORT = 8080;
const int BUFFER_SIZE = 1024;

int main(){
    cout << "ping - pong" <<endl;

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        cerr << "Ошибка создания сокета" << endl;
        return 1;
    }
    cout<<"создано"<<endl;

    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);

    cout<<"подключ к серверу"<<endl;
    if(connect(clientSocket, (sockaddr*) &serverAddr, sizeof(serverAddr))<0){
        cerr<<"ошибка 2"<<endl;
        return 2;
    }
    cout<<"подкл"<<endl;

    for(int i=0; i<3; i++){
        string message = "ping";
        cout<<"отправкa "<< message<<endl;
        send(clientSocket, message.c_str(), message.length(), 0);
        char buffer[BUFFER_SIZE];
        memset(buffer, 0, BUFFER_SIZE);
        int byferRessived = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
        if (byferRessived>0){
            cout<<"получен: "<<buffer<<endl;
        }
        cout<<"Готово"<<endl;
        cout << "---"<<endl;
    }
    cout<<"exit"<<endl;
    send(clientSocket, "exit", 4, 0);
    close(clientSocket);
    cout<<"завершён"<<endl;
    return 0;

}