//TCP CLIENT header file

//Must include "Ws2_32.lib"
#pragma once
#pragma comment(lib,"Ws2_32.lib")

//Standard HEADER files
#include <sdkddkver.h>
#include <WinSock2.h>
#include <iostream>
#include <string>
#include <Windows.h>

#define SCK_VERSION2 0x0202

using namespace std;

string runClient(string score, string achievements, bool* beated) {
	long SUCCESSFUL;
	WSAData WinSockData;
	WORD DLLVersion;
	DLLVersion = MAKEWORD(2, 1);
	SUCCESSFUL = WSAStartup(DLLVersion, &WinSockData);

	string RESPONSE;
	string CONVERTER;
	char MESSAGE[200];
	char scoreAnswer[10];
	char achivementAnswer[6];

	//INFO TO SEND
	string score_xml;
	string achievements_xml;
	string name;

	char namecopy[10];
	bool valido = false;

	SOCKADDR_IN ADDRESS;

	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, NULL);

	ADDRESS.sin_addr.s_addr = inet_addr("127.0.0.1");
	ADDRESS.sin_family = AF_INET;
	ADDRESS.sin_port = htons(444);

	connect(sock, (SOCKADDR*)&ADDRESS, sizeof(ADDRESS));	//Establishes connection.

	SUCCESSFUL = send(sock, score.c_str(), 46, NULL);	//Sends Score:
	cout << "Enter your name without spaces: ";
	cin >> name;
	strcpy(namecopy, name.c_str());
	while (!valido) {
		valido = true;
		for (int i = 0; namecopy[i] != '\0'; i++) {
			if (namecopy[i] == ' ') { valido = false; }
		} if (!valido) { cout << "Without spaces: "; cin >> name; strcpy(namecopy, name.c_str()); }
	}
	cout << "\n";
	SUCCESSFUL = send(sock, name.c_str(), 46, NULL);

	//Waits for response about score:
	SUCCESSFUL = recv(sock, scoreAnswer, sizeof(scoreAnswer), NULL);
	score_xml = scoreAnswer;
	//Verificas si ha batido/igualado/no batido su high score anterior.
		//Printeas highScore anterior en caso de igualarlo o no batirlo. HIGHSCORE/NOT HIGHSCORE
		//Printear score de esta partida en caso de batirlo. +  NEW HIGHSCORE!!




	// ACHIEVEMENTS
	cout << "Press ENTER ...";
	cin >> RESPONSE;
	//Mandar información de los achievements.
	SUCCESSFUL = send(sock, achievements.c_str(), 46, NULL);
	SUCCESSFUL = recv(sock, achivementAnswer, sizeof(achivementAnswer), NULL);
	achievements_xml = achivementAnswer;
	int i_tmp = 0;
	
	for (int i = 0; i != 5; i++) {
		//COMPROBACIONES DE LOS ACHIEVEMENTS: beated[i] = i_tmp;
		i_tmp = achivementAnswer[1] - '0';
		beated[i] = i_tmp;
	}
	return score_xml;
}
