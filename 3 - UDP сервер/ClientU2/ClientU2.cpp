#include "pch.h"
#include <iostream>
#pragma comment (lib,"WS2_32.LIB")
#include <winsock.h>
#include <string>
#include "ErrorMessages.h"
#include <sstream>
#include <string.h>
#include <time.h>
using namespace std;
int main() {
	setlocale(LC_CTYPE, "Russian");

	string IP = "127.0.0.1";
	int count;
	cout << "Введите количество сообщений для отправки: ";
	cin >> count;

	clock_t t1 = 0,
		t2 = 0;

	try
	{
		SOCKET cS;
		WSADATA wsaData;

		SOCKADDR_IN serv;
		serv.sin_family = AF_INET;// ipv 4
		serv.sin_port = htons(709);
		serv.sin_addr.s_addr = inet_addr(IP.c_str());

		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("Startup: ", WSAGetLastError());

		if ((cS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("Socket: ", WSAGetLastError());



		char obuf[256] = "HelloFromClient ";

		t1 = clock();

		for (int i = 0; i < count; i++)
		{
			char msg[256] = "Hello from Client ";
			stringstream strs;
			strs << i;
			string temp_str = strs.str();
			char* char_type = (char*)temp_str.c_str();
			strcat_s(msg, char_type);

			cout << msg << endl;
			sendto(cS, msg, sizeof(msg), 0, (sockaddr*)&serv, sizeof(serv));
		}

		t2 = clock();




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
	cout << "Время передачи: " << (double)(t2 - t1) / CLOCKS_PER_SEC << " сек." << endl;
	cout << endl;
	system("pause");
	return 0;
}