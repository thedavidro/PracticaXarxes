/*#define WIN32_LEAN_AND_MEAN
#define DEFAULT_BUFLEN 512
#include <Windows.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")


void client() {

	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	struct addrinfo addrInit;
	struct addrinfo *addrDest;
	ZeroMemory(&addrInit, sizeof(addrInit));

	addrInit.ai_family = AF_INET;
	addrInit.ai_socktype = SOCK_STREAM;
	addrInit.ai_protocol = IPPROTO_TCP;

	getaddrinfo("192.168.123.76", "8155", &addrInit, &addrDest); //Ip servidor (a qui li enviem)


	SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	connect(Socket, addrDest->ai_addr, addrDest->ai_addrlen);
	const char *message = "Sloth";
	send(Socket, message, DEFAULT_BUFLEN, sizeof(message));
	shutdown(Socket, 1);
	closesocket(Socket);
	WSACleanup();
}

void server() {
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	struct addrinfo addrInit;
	struct addrinfo *addrDest;

	ZeroMemory(&addrInit, sizeof(addrInit));
	addrInit.ai_family = AF_INET;
	addrInit.ai_socktype = SOCK_STREAM;
	addrInit.ai_protocol = IPPROTO_TCP;
	addrInit.ai_protocol = AI_PASSIVE;

	getaddrinfo(NULL, "8155", &addrInit, &addrDest);

	char recvbuf[DEFAULT_BUFLEN];
	int recbuflen = DEFAULT_BUFLEN;

	SOCKET connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(connectSocket, addrDest->ai_addr, addrDest->ai_addrlen);
	listen(connectSocket, 1); //socket + # de conexiones permitidas
	SOCKET reciveSocket = accept(connectSocket, addrDest->ai_addr, NULL);
	int pos = recv(reciveSocket, recvbuf, recbuflen, 0);
	recvbuf[pos - 1] = '\0';
	std::cout << recvbuf << std::endl;
	shutdown(reciveSocket, SD_RECEIVE);
	closesocket(reciveSocket);
	WSACleanup();
}

void main() {
	for (;;) {
		server();
	}
	//client();
}
*/