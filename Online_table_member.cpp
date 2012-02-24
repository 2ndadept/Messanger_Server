#include "stdafx.h"
#include "Online_table_member.h"

Online_table_member::Online_table_member( SOCKET sock, wchar_t* login, int sizeoflogin )
{
	memset( this->username, 0, 64 );

	this->sock = sock;

	memcpy( this->username, login, SIZE_OF_USERNAME );

	this->rdy_rcv = false;
}

Online_table_member::Online_table_member(void)
{
}

Online_table_member::~Online_table_member(void)
{
}

bool Online_table_member::is_online()
{
	typedef list<Online_table_member>::const_iterator LI; //list iterator

	for(LI i = users_online.begin(); i != users_online.end(); i++ )//check for this user online
		{							
			const Online_table_member &e = *i;

			if( memcmp( &this->username, 
						&e, sizeof( SIZE_OF_USERNAME ) ) == 0)//if this user alreay is online
				{
					return true;
				}
		}
	return false;
}

void Online_table_member::get_online_users()	
{
//	cout<<"start "<<__FUNCTION__<<"\n";
	typedef list<Online_table_member>::iterator LI; //list iterator

	User_state user;

	int bytes_send;

	int bytes_read;

	char sbuf[ 1024 ];

	memset( sbuf, 0, sizeof( sbuf ) );

	char rbuf[ 1024 ];

	memset( rbuf, 0, sizeof( rbuf ) );


	for(LI i = users_online.begin(); i != users_online.end(); i++ )//send to user info about users online
		{					
			Online_table_member &e = *i;

			memcpy( &user, &e.username, SIZE_OF_USERNAME ); 

			user.a_d = 0;

			memcpy( sbuf, &user, sizeof( user ) );

			if( e.sock != this->sock )
			while( true )
			{
				if( e.rdy_rcv == true )
				{
					EnterCriticalSection( &critical_section1 );	

					this->rdy_rcv = false;

					LeaveCriticalSection( &critical_section1 );

					bytes_send = send( this->sock, sbuf, sizeof( user ), 0);

	//				cout<<"SOCKET "<<this->sock<<" got false, "<<__FUNCTION__<<"\n";

					bytes_read = bytes_recieving( this->sock, rbuf, sizeof( rbuf ) );

					if( bytes_read == 1 )
					{
						EnterCriticalSection( &critical_section1 );
	
						this->rdy_rcv = true;
	
						LeaveCriticalSection( &critical_section1 );
					
	//					cout<<"SOCKET "<<this->sock<<" got true, "<<__FUNCTION__<<"\n";

						break;
					}
					else
					{
						cout<<"recieve data error! "<<bytes_read<<"\n";
						break;
					}
				}
			}			//while
		}				//for
	}

void Online_table_member::send_auth_rezult( int auth_rezult )
{
	int bytes_send;

	char sbuf[1024];

	memset( sbuf, 0, sizeof(sbuf) );

	memcpy( sbuf, &auth_rezult, sizeof( auth_rezult ) );
	
	bytes_send = send( this->sock, sbuf, sizeof( auth_rezult ), 0 );

	if( bytes_send == -1)
	{
		cout<<"sending data error! \n";
		exit( -2 );
	}
}

void Online_table_member::put_into_db()
{
	EnterCriticalSection( &critical_section1 );

	users_online.push_back( *this );

	LeaveCriticalSection( &critical_section1 );
}

void Online_table_member::going_online()
{
	User_state user;

	user.a_d = 0;

	memcpy( &user.username, &this->username, SIZE_OF_USERNAME );

	user.send_toall( this->sock );

}

