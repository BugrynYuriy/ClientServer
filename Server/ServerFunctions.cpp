#include "SERVER.h"

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
bool CONNECT (LPSOCKADDR_IN local_addr , SOCKET & mysocket )
{
	local_addr->sin_family = AF_INET;
    local_addr->sin_port = htons ( 1280 );
    local_addr->sin_addr.s_addr = 0;

	// associates a local address with a socket
	if( bind ( mysocket , ( sockaddr * ) local_addr , sizeof( *local_addr ) ) != 0 )
	{
		printf("\nCan't associates a local address with a socket");
		return false;
	}

	// places a socket in a state in which it is listening for an incoming connection.
	if( listen ( mysocket , 20 ) != 0 )
	{
		printf("\nCan't places a socket in a listening state");
		return false;
	}

	return true;
}
unsigned int _stdcall ThreadFunc(void *client)
{

	SOCKET s2 = *((SOCKET *)client);
	char buf[100];


	while(recv(s2,buf,sizeof(buf),0))
    {
        
		if( send ( s2 ,"connect", 100 , 0) == SOCKET_ERROR )
		{
			clients.remove(s2);
			break;
		}
		else
		{
			printf("Client write : %s",buf);
			
			sendAll(buf);
		}
    }
    
	closesocket(s2);
	printf("Client disconnected ");
	return 0;
}
void sendAll (char *buff)
{
	std::list<SOCKET>::iterator it;

	for ( it = clients.begin() ; it != clients.end(); it++ )
	{
		send (*it ,buff, 100 , 0);
	}
	
}