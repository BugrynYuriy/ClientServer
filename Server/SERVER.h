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

bool initWinsockDll ( WORD wVersionRequested , LPWSADATA lpWSAData );
bool CONNECT (LPSOCKADDR_IN local_addr , SOCKET & mysocket );
unsigned int _stdcall ThreadFunc(void *client);
void sendAll (char *buff);

extern std::list<SOCKET> clients ;


#endif  /* _INC_SERVER */