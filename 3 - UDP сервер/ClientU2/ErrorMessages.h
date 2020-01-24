#pragma once
#include "pch.h"
#include <string>
#pragma comment (lib,"WS2_32.LIB")
#include <winsock.h>
using namespace std;
string GetErrorMsgText(int code);
string SetErrorMsgText(string msgText, int code);