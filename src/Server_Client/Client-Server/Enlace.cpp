#include <Windows.h>
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>


#pragma comment(lib, "Ws2_32.lib")


int client(int argc, char *argv[]) {
	WSAData wsaData;
	struct addrinfo addrInit;
	struct addrinfo *addrDest;

	addrInit.ai_family = AF_INET;
	addrInit.ai_socktype = SOCK_STREAM;
	addrInit.ai_protocol = IPPROTO_TCP;


	getaddrinfo("192.168.123.9", "5260", &addrInit, &addrDest);

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET my_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	connect(my_socket, addrDest->ai_addr, addrDest->ai_addrlen);









	shutdown(my_socket, 1);
	closesocket(my_socket);
	WSACleanup();

	return 0;
}

int server() {
	struct addrinfo addrInit;
	struct addrinfo *addrDest;
	struct addrinfo *addrEmpty;

	addrInit.ai_family = AF_INET;
	addrInit.ai_socktype = SOCK_STREAM;
	addrInit.ai_protocol = IPPROTO_TCP;

	getaddrinfo("127.0.0.1", "5260", &addrInit, &addrDest);

	SOCKET my_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(my_socket, addrDest->ai_addr, addrDest->ai_addrlen);
	listen(my_socket, 1); //socket + # de conexiones permitidas
	accept(my_socket, addrEmpty->ai_addr, NULL);
	char *buf;
	recv(my_socket, buf, sizeof(*buf), 1);

	shutdown(my_socket, 1);
	closesocket(my_socket);
	WSACleanup();
}