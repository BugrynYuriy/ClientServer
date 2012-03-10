#pragma once

#ifndef _INC_CLIENT
#define _INC_CLIENT

#include<stdio.h>
#include<iostream>
#include <winsock2.h>
#include <string.h>
#include <conio.h>
#include <process.h>
#include <list>

bool initWinsockDll ( WORD wVersionRequested , LPWSADATA lpWSAData );
bool CONNECT (LPSOCKADDR_IN dest_addr , SOCKET & mysocket );



#endif  /* _INC_CLIENT */