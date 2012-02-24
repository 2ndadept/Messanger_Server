#pragma once

class User_state
{
public:
	wchar_t username [ 32 ];
	int a_d;						//0 - add user, 1 - delete user
	User_state(void);
	~User_state(void);

	void send_toall( SOCKET sock );
};
