#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

const int PORT = 8080;
const int BUFFER_SIZE = 1024;

int main(){
    cout << "сервер" << endl;
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0){
        cerr << "ошибка создания сокета!" << endl;
        return 1;
    }
    cout << "сокет создан!" << endl;

    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);


    //bind(сокт, адрес, размер адреса)

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cerr << "ошибка bind!" << endl;
        close(serverSocket);
        return 2;
    }
    cout << "Сокет привязан!!!" << endl;

    //listen (сокет размер);

    if(listen(serverSocket, 4) < 0){
        cerr << "ошибка listen!" << endl;
        close(serverSocket);
        return 3;
    }
    cout << "listen на порту " << PORT << endl;

    sockaddr_in clientAddr;
    socklen_t clientAddrsize = sizeof(clientAddr);
    int clientSocket = accept(serverSocket, (sockaddr*)& clientAddr, &clientAddrsize);
    if (clientSocket < 0){
        cerr << "Ошибка accept" << endl;
        close(serverSocket);
        return 4;
    }
    cout << "accept good" << endl;
    //inet_ntop(семейство, адрес, буфер, размер буфера)

    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
    cout << "Клиент подключён: " << clientIP << endl;
    
    char buffer[BUFFER_SIZE];
    while(true){
        memset(buffer, 0, BUFFER_SIZE);
        int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
        if(bytesReceived <= 0){
            cout << "Клиент отключился" << endl;
            break;
        }
        
        string message(buffer);
        cout << "Получено: " << message << endl;
   
        if (message == "exit"){
            cout << "Клиент запросил выход" << endl;
            break;
        }
        
        string response;
        if (message == "ping"){
            response = "pong";
        }
        else{
            response = "DA";
        }

        cout << "Отправка response: " << response << endl;
        send(clientSocket, response.c_str(), response.length(), 0);
    }

    close(clientSocket);
    close(serverSocket);
    cout << "Завершено" << endl;
    return 0;
}