#include<stdio.h>
#include<iostream>
#include<winsock2.h>
 
using namespace std;
void main()
{
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
    dest_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    connect(s,(sockaddr *)&dest_addr,sizeof(dest_addr));


	char buf[100];
 
    
 
while (true)
{
    cout<<"Enter the string:"<<endl;
    fgets(buf,sizeof(buf),stdin);
    send(s,buf,100,0);
	
	if (recv(s,buf,sizeof(buf),0)!=0)
    {
		if(strcmp(buf,"connect") != 0)
		{
			cout<<"Received string:"<<endl<<buf<<endl;
		}
    }
    
}
closesocket(s);
WSACleanup();
}