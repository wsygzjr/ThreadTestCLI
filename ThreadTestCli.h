#pragma once
#include <iostream>
#include <thread>
#include <winsock2.h>
#include <WS2tcpip.h>

bool init_Socket();
bool close_Socket();
SOCKET CreateClientSocket();
void rec(SOCKET con);
void sen(SOCKET con);