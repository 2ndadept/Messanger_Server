#include "StdAfx.h"
#include "User_state.h"

User_state::User_state(void)
{
}

User_state::~User_state(void)
{
}

void User_state::send_toall( SOCKET sock )
{
//	cout<<"start "<<__FUNCTION__<<"\n";

	typedef list<Online_table_member>::iterator LI; //list iterator

	int bytes_send = 0;

	char sbuf[ 1024 ];

	memset( sbuf, 0, sizeof(sbuf) );

	memcpy( &sbuf, this, sizeof( User_state ) );

	for(LI i = users_online.begin(); i != users_online.end(); i++ )
		{
			Online_table_member &e = *i;

			if( e.sock != sock )
			while( true )
			{
				if( e.rdy_rcv == true )
				{
					EnterCriticalSection( &critical_section1 );

					bytes_send = send( e.sock, sbuf, sizeof( User_state ), 0 );

					e.rdy_rcv = false;

//					cout<<"SOCKET "<<e.sock<<" got false, "<<__FUNCTION__<<"\n";

					LeaveCriticalSection( &critical_section1 );

					break;
				}
			}
 
		}
//	cout<<"end "<<__FUNCTION__<<"\n";
}
