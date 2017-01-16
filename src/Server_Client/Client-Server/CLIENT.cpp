//TCP CLIENT source file

/*#include "CLIENT.h"

using namespace std;

void ConvertToString(char* p_message, int p_size) {
	for (int i = 0; i != p_size; i++) {
		if (p_message[i] != '_') {
			p_message[i-1] = '\0';
		}
	}
}

void main()
{
	//Locals
	long SUCCESSFUL;
	WSAData WinSockData;
	WORD DLLVersion;
	DLLVersion = MAKEWORD(2, 1);
	SUCCESSFUL = WSAStartup(DLLVersion, &WinSockData);

	string RESPONSE;
	string CONVERTER;
	char MESSAGE[200];
	char scoreAnswer[100];

	//INFO TO SEND
	string name;
	string score;
	string achievements;

	SOCKADDR_IN ADDRESS;

	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, NULL);

	ADDRESS.sin_addr.s_addr = inet_addr("127.0.0.1");
	ADDRESS.sin_family = AF_INET;
	ADDRESS.sin_port = htons(444);

	cout << "\n\tCLIENT: Do you want to connect to this SERVER? (Y\N)";
	cin >> RESPONSE;

	if (RESPONSE == "n")
	{
		cout << "\n\tOK. Quitting instead.";
	}
	else if (RESPONSE == "y")
	{
		int sizeOfMessage = 0;
		connect(sock, (SOCKADDR*)&ADDRESS, sizeof(ADDRESS));	//Establishes connection.
		SUCCESSFUL = recv(sock, MESSAGE, sizeof(MESSAGE), NULL);	//Connection established message
		sizeOfMessage = sizeof(MESSAGE)*sizeof(char);
		//MESSAGE[6] = '\0';	//Esto funciona para el caso de los achievements --> NO ES NECESARIO SI EL MENSAJE ERA ORIGINALMENTE UN STRING.
		CONVERTER = MESSAGE;


		//Sends Score:
		SUCCESSFUL = send(sock, score.c_str(), 46, NULL);
		cout << "\tPleas enter your name: ";
		cin >> name;
		cout << "\n\n";
		SUCCESSFUL = send(sock, name.c_str(), 46, NULL);

		//Waits for response about score:
		SUCCESSFUL = recv(sock, scoreAnswer, sizeof(scoreAnswer), NULL);

		
		

		

		cout << "\n\tMessage from SERVER:\n\n\t" << CONVERTER << endl;
	}
	else
	{
		cout << "\n\tThat was an inappropiate RESPONSE!";
	}

	cout << "\n\n\t";
	system("PAUSE");
	exit(1);
}*/