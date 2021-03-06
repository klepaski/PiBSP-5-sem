#include "pch.h"
#include <iostream>
#pragma comment (lib,"WS2_32.LIB")
#include <winsock.h>
#include <string>
#include <math.h>
#include "ErrorMessages.h"
using namespace std;



int main() {
	setlocale(LC_ALL, "Russian");
	try
	{
		SOCKET sS;
		WSAData wsaData;
		SOCKADDR_IN client;
		SOCKADDR_IN serv;
		int sizeofaddrserv = sizeof(serv);
		int sizeofaddrclient = sizeof(client);
		serv.sin_addr.s_addr = inet_addr("127.0.0.1");
		serv.sin_port = htons(3000);
		serv.sin_family = AF_INET;
		char msg[20];


		if (WSAStartup(MAKEWORD(2, 1), &wsaData) != 0) {
			throw SetErrorMsgText("Startup", WSAGetLastError());
		}

		if ((sS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET) {
			throw SetErrorMsgText("Socket", WSAGetLastError());
		}

		if (bind(sS, (SOCKADDR*)&serv, sizeof(serv)) == SOCKET_ERROR) {
			throw SetErrorMsgText("Bind", WSAGetLastError());
		}


		while (true) {

			recvfrom(sS, msg, sizeof(msg), NULL, (sockaddr*)&client, &sizeofaddrclient);
			cout << "Client (" << inet_ntoa(client.sin_addr) << ":" << client.sin_port << "): " << msg << endl;

			char ans[20] = "ECHO-";
			strcat(ans, msg);
			cout << "Ответ клиенту: " << ans;

			sendto(sS, ans, sizeof(ans), 0, (sockaddr*)&client, sizeof(client));

		}
		if (closesocket(sS) == SOCKET_ERROR) throw SetErrorMsgText("Closesocket", WSAGetLastError());
		if (WSACleanup() == SOCKET_ERROR) throw SetErrorMsgText("Cleanup", WSAGetLastError());

		system("pause");

	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText << "\n";
	}
	system("pause");
	return 0;
}
