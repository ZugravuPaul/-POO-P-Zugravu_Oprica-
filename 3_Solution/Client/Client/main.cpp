#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

#include "User.h"
#include "SHA256.h"


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "8080"

int __cdecl main(int argc, char** argv)
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
   
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

    // Validate the parameters
    if (argc != 2) {
        printf("usage: %s server-name\n", argv[0]);
        return 1;
    }

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }
    char sendbuf[DEFAULT_BUFLEN];
    char recvbuf[DEFAULT_BUFLEN];
    string data_string;

    while (true) {
        // Get user input
        printf("Enter r to register (or 'q' to quit): ");
        fgets(sendbuf, DEFAULT_BUFLEN, stdin);

        // Check if user wants to quit
        if (strcmp(sendbuf, "q\n") == 0)
            break;
        if (strcmp(sendbuf, "r\n") == 0) {
            std::string name, pass, email;
            //cin>>name>>pass>>email;
            cin >> data_string;
            /* string hashed_pass = sha256(pass);
             User* newuser=new User(name, hashed_pass, email);    //criptarea
             data_string=newuser->SerializeUser();
             delete newuser;*/
            strcpy(sendbuf, data_string.c_str());
            sendbuf[data_string.length()] = '\0';

            if (strcmp(sendbuf, "\n") != 0) {
                iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
                if (iResult == SOCKET_ERROR) {
                    printf("send failed with error: %d\n", WSAGetLastError());
                    closesocket(ConnectSocket);
                    WSACleanup();
                    return 1;
                }
                // Receive the response
                iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
                if (iResult > 0) {
                    recvbuf[iResult] = '\0'; // Null-terminate the received data
                    printf("Received data: %s\n", recvbuf);
                }
                else if (iResult == 0) {
                    printf("Connection closed\n");
                    break;
                }
                else {
                    printf("recv failed with error: %d\n", WSAGetLastError());
                    closesocket(ConnectSocket);
                    WSACleanup();
                    return 1;
                }
                // Send the message

            }
        }
    }

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}