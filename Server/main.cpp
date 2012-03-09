#include "SERVER.h"

using namespace std;

std::list<SOCKET> clients ;

int main()
{
    WORD  wVersionRequested = MAKEWORD( 2, 2 );
    WSADATA wsaData;
	sockaddr_in local_addr;
	SOCKET client_socket ;
	sockaddr_in client_addr;
	int client_addr_size = sizeof ( client_addr );
	HANDLE thread;

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
    
	CONNECT(&local_addr,s);
    
	cout<<"Server receive ready"<<endl;
    cout<<endl;
    
	
	while( ( client_socket = accept ( s, ( sockaddr * )&client_addr, &client_addr_size ) ) )
    {
	  
	  cout<<inet_ntoa(client_addr.sin_addr)<<" connected \n";
	 
	  thread = (HANDLE) _beginthreadex ( NULL , NULL , ThreadFunc , &client_socket , NULL , NULL );

	  CloseHandle ( thread );

	  clients.push_back(client_socket);
    
	}
	
	closesocket(s);
	WSACleanup();
	return 0;
}
 