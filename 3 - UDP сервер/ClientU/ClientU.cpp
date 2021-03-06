#include "pch.h"
#include <iostream>
#pragma comment (lib,"WS2_32.LIB")
#include <winsock.h>
#include <string>
#include "ErrorMessages.h"
#include <sstream>
#include <string.h>
#include <time.h>
#include <math.h>
using namespace std;
int main() {
	setlocale(LC_CTYPE, "Russian");

	string IP = "127.0.0.1";
	

	try
	{
		SOCKET cS;
		WSADATA wsaData;

		SOCKADDR_IN serv;
		serv.sin_family = AF_INET;// ipv 4
		serv.sin_port = htons(3000);
		serv.sin_addr.s_addr = inet_addr(IP.c_str());
		int sizeofaddrserv = sizeof(serv);
		char ans[12];

		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("Startup: ", WSAGetLastError());

		if ((cS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("Socket: ", WSAGetLastError());

		
			char msg[5];
			//char msg[256] = "Hello from Client ";
			cout << "Введите сообщение: ";
			cin >> msg;


			sendto(				//отпр сообщ без устан соединения
				cS,				///сокет
				msg,			///пересылаемые д-е
				sizeof(msg),	///размер
				0,				///индикатор режима маршрутизации
				(sockaddr*)&serv, 
				sizeof(serv)	///длина структуры to (сокета получателя)
			);


			recvfrom(			//получ сообщ без устан соед
				cS,					///сокет
				ans,				///получаемые д-е
				sizeof(ans),
				NULL,				///индикатор режима маршрутизации
				(sockaddr*)&serv,
				&sizeofaddrserv	///ук-ль на р-р to (структ сокета отправителя)
			);
			cout << "Ответ сервера: " << ans;



		if (closesocket(cS) == SOCKET_ERROR)
			throw SetErrorMsgText("Closesocket: ", WSAGetLastError());

		if (WSACleanup() == SOCKET_ERROR)     
			throw SetErrorMsgText("Cleanup: ", WSAGetLastError());
	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText << endl;
	}

	cout << endl;
	system("pause");
	return 0;
}