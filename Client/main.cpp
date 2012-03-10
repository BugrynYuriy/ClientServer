#include<stdio.h>
#include<iostream>
#include<winsock2.h>
#include <process.h>
#include <conio.h>
 
using namespace std;

unsigned int _stdcall readMessage(void *server)
{

	SOCKET s = *((SOCKET *)server);
	char buf[100];
	int res;

	while(true)
	{
		if ((res=recv(s,buf,sizeof(buf),0))!=0 && res!=SOCKET_ERROR)
		{
			if(strcmp(buf,"connect") != 0)
			{
				cout<<endl<<buf;
			}
		}

		else
		{
			cout<<"Server disconnected";
			break;
		}
		
	}

	return 0;
}


void main()
{
    char clientname [20];
	WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD( 2, 2 );
    err=WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 ){return;}
	 SOCKET s=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in dest_addr;
    dest_addr.sin_family=AF_INET;
    dest_addr.sin_port=htons(1280);
    dest_addr.sin_addr.s_addr=inet_addr("192.168.1.2");
    
	cout<<"Enter name : ";
	cin>>clientname;
	
	strcpy(&clientname[strlen(clientname)]," : ");
	fflush(stdin);
	
	connect(s,(sockaddr *)&dest_addr,sizeof(dest_addr));

	send(s,clientname,20,0);

	char buf[100];
 
	_beginthreadex(NULL,NULL,readMessage,&s,NULL,NULL);
 
while (true)
{
    fgets(buf,sizeof(buf),stdin);
    if( send ( s , buf , 100 , 0 ) == SOCKET_ERROR )
	{
		break;
	}
}

closesocket(s);
WSACleanup();
_getch();
}