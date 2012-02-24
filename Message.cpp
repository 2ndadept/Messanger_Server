#include "stdafx.h"
#include "Message.h"

Message::Message( void )
{
}

Message::~Message( void )
{
}

bool Message::send_message()
{
	typedef list<Online_table_member>::iterator LI; //list iterator

	int bytes_send;

	char sbuf[1024];

	memset( sbuf, 0, sizeof( sbuf ) );

	memcpy( &sbuf, this, sizeof( Message ) );

	for(LI i = users_online.begin(); i != users_online.end(); i++ )//send to user info about users online
		{							
			Online_table_member &e = *i;

			if( memcmp( &e.username, this->dstUser, SIZE_OF_USERNAME ) == 0 )
			{
				while( true )
				{
					if( e.rdy_rcv == true )
					{
						EnterCriticalSection( &critical_section1 );
		
						e.rdy_rcv = false;

						LeaveCriticalSection( &critical_section1 );

						bytes_send = send( e.sock, sbuf, sizeof( Message ), 0 );
						
						if( bytes_send <= 0 )
							return false;
						
						break;
					}
				}

			}
		}

	return true;
}
