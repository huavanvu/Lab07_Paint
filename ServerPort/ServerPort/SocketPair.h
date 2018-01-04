#pragma once


#include <iostream>
#include "afxsock.h"
#include <sstream>
#include <fstream>
#include <string>
#include <thread>
#include <iostream>
#include <vector>

using namespace std;

class SocketPair
{
public:
	fstream blackList;
	CSocket Client;
	SOCKET Proxy;
	bool isAlive;
	SocketPair()
	{
	}
	~SocketPair() {
	}
};

#define HTTP "http://"
#define PORT 80
#define USERAGENT "HTTP 1.0"