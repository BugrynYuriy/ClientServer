#pragma once

#ifndef _INC_SERVER
#define _INC_SERVER

#include<stdio.h>
#include<iostream>
#include <winsock2.h>
#include <string.h>
#include <conio.h>
#include <process.h>
#include <list>

struct CLIENT
{
	SOCKET client;
	char name [20];
};

bool initWinsockDll ( WORD wVersionRequested , LPWSADATA lpWSAData );
bool CONNECT (LPSOCKADDR_IN local_addr , SOCKET & mysocket );
unsigned int _stdcall clientThread (void *client);
void clientsRequests (SOCKET & mysocket);
void sendAll (char *buff);
void concatString (char *concat , char * str1 , char *str2);

extern std::list<SOCKET> clients ;


#endif  /* _INC_SERVER */