#include "SERVER.h"

bool initWinsockDll ( WORD wVersionRequested , LPWSADATA lpWSAData )
{
	
	int err;
	
	// initiates use of the Winsock DLL by a process
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
    local_addr->sin_addr.s_addr = inet_addr("192.168.1.2");

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
unsigned int _stdcall clientThread(void *client)
{

	SOCKET s2 = ((CLIENT *)client)->client;
	char name [20];
	char buf[100];
	char message [100];
	
	strcpy_s(name,((CLIENT *)client)->name);
	
	while(recv(s2,buf,sizeof(buf),0))
    {
        
		if( send ( s2 ,"connect", 100 , 0) == SOCKET_ERROR )
		{
			clients.remove(s2);
			break;
		}
		else
		{
			concatString(message,name,buf);
			sendAll(message);
		}
    }
    
	closesocket(s2);
	printf("\nClient disconnected ");
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
void clientsRequests (SOCKET & mysocket)
{
	
	HANDLE thread;
	SOCKET client_socket ;
	sockaddr_in client_addr;
	int client_addr_size = sizeof ( client_addr );
	
	char name[20];

	while( ( client_socket = accept ( mysocket, ( sockaddr * )&client_addr, &client_addr_size ) ) != INVALID_SOCKET )
    {
	  
	  CLIENT client;
	  
	  recv(client_socket,name,sizeof(name),0);
	  
	  printf("\n%s connected",inet_ntoa(client_addr.sin_addr));
	  
	  client.client = client_socket;
	  strcpy_s(client.name,name);
	 
	  thread = (HANDLE) _beginthreadex ( NULL , NULL , clientThread , &client , NULL , NULL );

	  CloseHandle ( thread );

	  clients.push_back(client_socket);
    
	}

}
void concatString (char *concat , char * str1 , char *str2)
{

	strcpy(concat,str1); // Copies the str1 to buf
	strcpy(&concat[strlen(concat)],str2); // Copies the str2 to buf , in the position of the end of str1

}