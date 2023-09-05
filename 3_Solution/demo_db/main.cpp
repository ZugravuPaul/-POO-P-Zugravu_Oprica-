#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include "DAL.h"
#include "Serialisation.h"

#pragma comment(lib, "ws2_32.lib")  // Link with the Winsock library

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "8080"

using namespace std;


int main() {

	DAL& db = DAL::getInstance();
	//User user("andra", "andra", "andra", "parola", "mail");
	//db.createUser(user);

	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo* result = NULL;
	struct addrinfo hints;

	int iSendResult;

	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for the server to listen for client connections.
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = ::bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	printf("Server started. Waiting for connections...\n");

	char recvbuf[DEFAULT_BUFLEN];
	Serialisation js;

	while (true) {
		// Accept a client socket
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}

		// Receive until the peer shuts down the connection
		while(true) {
			memset(recvbuf, 0, recvbuflen);
			iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
			if (iResult > 0) {
				printf("Bytes received: %d\n", iResult);
				recvbuf[iResult] = '\0';
				printf("%s\n", recvbuf);

				string data_received = recvbuf;
				memset(recvbuf, 0, recvbuflen);
				//recvbuf va contine raspunsul la query
				strcpy(recvbuf, js.find_request(data_received).c_str());
				

				iSendResult = send(ClientSocket, recvbuf, iResult, 0);
				if (iSendResult == SOCKET_ERROR) {
					printf("send failed with error: %d\n", WSAGetLastError());
					break;
				}
				printf("Bytes sent: %d\n", iSendResult);
			}
			else if (iResult == 0) {
				printf("Connection closed by the client.\n");
				break;
			}
			else {
				printf("recv failed with error: %d\n", WSAGetLastError());
				break;
			}
		}
		closesocket(ClientSocket);
		printf("Client disconnected.\n");
	}
	closesocket(ListenSocket);
	WSACleanup();


	return 0;
}


