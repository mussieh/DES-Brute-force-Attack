//Used portions of code from: http://www.bogotobogo.com/cplusplus/sockets_server_client.php
#include "client.h"


Client::Client() {
    portno = 30777;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname("18.216.21.129");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");
}

Client::~Client() {
    close(sockfd);
}

void Client::informServer(string& key) {
    bzero(buffer,256);
    // fgets(buffer,255,1); //stdin
    int key_length = key.length();
    for (int i = 0; i < key_length; ++i) {
        buffer[i] = key.at(i);
    }
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
         error("ERROR writing to socket");
}

char * Client::getMessage() {
    return buffer;
}

int Client::keyStatus() {
    bzero(buffer,256);

    // Non-blocking mode
    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

    n = read(sockfd, buffer, 255);
    // if (n < 0) {
    //     error("ERROR reading from socket");
    // }
    return n;
}

void Client::error(const char *msg)
{
    perror(msg);
    exit(0);
}
