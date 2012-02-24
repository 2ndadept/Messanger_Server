#pragma once

class Online_table_member
{
public:
	wchar_t username [ 32 ];
	SOCKET sock;
	volatile bool rdy_rcv;

	bool is_online();
	void get_online_users();
	void Online_table_member::send_auth_rezult( int auth_rezult );
	void going_online();
	void put_into_db();
	Online_table_member::Online_table_member( SOCKET sock, wchar_t* login, int sizeoflogin );
	Online_table_member(void);
	~Online_table_member(void);
};
