#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <signal.h>
#define BUFFSIZE 2048
#define DEFAULT_PORT 16555    // specify the port 16555.
#define MAXLINK 2048
int sockfd, connfd;    // define the server and client socket.
void stopServerRunning(int p)
{
    close(sockfd);
    printf("Close Server\n");
    exit(0);
}

int main()
{
    struct sockaddr_in serv_addr; // struct for ip+port
    char buff[BUFFSIZE];
    
    // socket(domain, socket type, protocol), two processes can communicate each other only if their sockets are of the same type and in the same domain.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd) {
        std::cout << "Create socket error:" << errno << strerror(errno) << std::endl;
        return -1;
    }
    // clear network address, same as memset(&serv_addr,0,sizeof(serv_addr));
    bzero(&serv_addr, sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET; // the protocol should be same as the first arg of socket()
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // bind ip
    serv_addr.sin_port = htons(DEFAULT_PORT); // bind port

    if(-1 == bind(sockfd,(struct sockaddr*)& serv_addr,sizeof(serv_addr))) {
        std::cout << "Bind error:" << errno << strerror(errno) << std::endl;
        return -1;
    }

    if (-1 == listen(sockfd,MAXLINK)) {
        std::cout << "Listen error:" << errno << strerror(errno) << std::endl;
        return -1;
    }

    std::cout << "Start listening ..." << std::endl;

    while (true) {
        signal(SIGINT,stopServerRunning); // stop server when Ctrl+C

        connfd = accept(sockfd,NULL,NULL);
        if (-1 == connfd) {
            std::cout << "Connect error:" << errno << strerror(errno) << std::endl;
            return -1;
        }

        bzero(buff,BUFFSIZE);
        recv(connfd,buff,BUFFSIZE-1,0);

        std::cout << "Received data:" << buff << std::endl;

        send(connfd,buff,strlen(buff),0);
        close(connfd);

    }
    return 0;
}