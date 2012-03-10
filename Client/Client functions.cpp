#include "CLIENT.h"


bool initWinsockDll ( WORD wVersionRequested , LPWSADATA lpWSAData )
{
	
	int err;
		
	err = WSAStartup( wVersionRequested,lpWSAData);
    if (err != 0) 
	{
        // Tell the user that we could not find a usable  WinSock DLL
        printf("WSAStartup failed with error: %d\n", err);
        return false;
    }

	if (LOBYTE(lpWSAData->wVersion) != 2 || HIBYTE(lpWSAData->wVersion) != 2) 
	{
        // Tell the user that we could not find a usable WinSock DLL
        printf("Could not find a usable version of Winsock.dll\n");
        WSACleanup();
        return false;
    }

	return true;
}

bool CONNECT (LPSOCKADDR_IN dest_addr , SOCKET & mysocket )
{
	dest_addr->sin_family=AF_INET;
    dest_addr->sin_port=htons(1280);
    dest_addr->sin_addr.s_addr=inet_addr("127.0.0.1");

	connect(mysocket,(sockaddr *)dest_addr,sizeof(dest_addr));
	
	return true;
}