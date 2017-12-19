/*
* Source: bogotobogo.com
* Modified: Nov. 10, 2017
*/

#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h> 

using namespace std;

class Client
{
 public:

	Client();
	~Client();
	void informServer(string& key);
	int keyStatus();
	char * getMessage();

 private:

		int sockfd;
		int portno;
		int n;
		struct sockaddr_in serv_addr;
		struct hostent *server;
        char buffer[256];

        void error(const char *msg);
};

#endif
