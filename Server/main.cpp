#include "SERVER.h"



std::list<SOCKET> clients ;

int main()
{

	WORD  wVersionRequested = MAKEWORD( 2, 2 );
    WSADATA wsaData;
	sockaddr_in local_addr;
	
	// Initiates use of the Winsock DLL by a process
	if( !initWinsockDll( wVersionRequested,&wsaData ) )
	{
		_getch();
		return 0;
	}
 
    SOCKET s= socket( AF_INET , SOCK_STREAM , 0 ); // create IPv4 server socket 
	if( s < 0 )
	{
		printf (" Socket ( ) error    %d \n ", WSAGetLastError ( ) );
	}
    
	/* 
	   Associates a local address with a socket and  places them 
	   in a state in which it is listening for an incoming connection.
	*/
	CONNECT(&local_addr,s);
    
	// processing clients' requests
	clientsRequests(s);
	
	closesocket(s);
	WSACleanup();
	return 0;
}
 