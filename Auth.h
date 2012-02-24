#pragma once

class Auth
{
public:
	Login user;
	bool reg;
	Auth(void);
	~Auth(void);
	bool is_registrated();
	bool exist();
	bool registration();
};


