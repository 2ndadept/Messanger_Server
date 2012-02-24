#include "stdafx.h"
#include "Auth.h"

Auth::Auth( void )
{
	memset( &this->user, 0, sizeof( struct Login ) );
	this->reg = false;
}

Auth::~Auth( void )
{
}

bool Auth::is_registrated()
{
	Login temp_login;

	rewind( databaze );

	while( !feof( databaze ) )
	{
		fread( &temp_login, sizeof( struct Login ), 1, databaze );
		if( memcmp( &temp_login, &this->user, sizeof( struct Login ) ) == 0 )
		return true;	
	}
	return false;
}

bool Auth::exist()
{
	Login temp_login;

	rewind( databaze );

	while( !feof( databaze ) )
		{
			fread( &temp_login, sizeof( struct Login ), 1, databaze );
			if( memcmp( &temp_login, &this->user.login, sizeof( struct Login ) ) == 0)
			return true;	
		}
	return false;
}

bool Auth::registration()
{
	EnterCriticalSection( &critical_section1 ); //Enter critical_section2
	fwrite( &this->user, sizeof( struct Login ), 1, databaze );
	LeaveCriticalSection( &critical_section1 );
	return true;
}
