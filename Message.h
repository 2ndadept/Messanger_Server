#pragma once

class Message
{
public:
	wchar_t srcUser [32];
	wchar_t dstUser [32];
	char timeStr [9];
	char dateStr [9];
	wchar_t text [200];

	bool send_message();
	Message(void);
	~Message(void);
};
