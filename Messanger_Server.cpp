#include "stdafx.h"

int main()
{
  _beginthread( console_control, 0, NULL );

	InitializeCriticalSection( &critical_section1 );
	SOCKET sock, listener;
	char buffver [ 1024 ] ;
	struct sockaddr_in addr;

	library_preparing( buffver );
	socket_initialization( listener );
	adress_initialization( addr );
	socket_connection( listener, addr );
	databaze_open();
	listen(listener, 10); //listen to a socket

	while(true)
		{
			accept_socket( sock, listener );

				cout<<"SOCK "<<sock<<"\n";

			_beginthread( handlesock, 0, (void*)sock );   // start a new tread 
														  // to handle accepted socket
    	}

	databaze_close();
	return 0;
}

