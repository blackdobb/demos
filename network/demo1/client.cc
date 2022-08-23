#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

#define BUFFSIZE 2048
#define SERVER_IP "0.0.0.0"    // server ip
#define SERVER_PORT 16555            // server port

int main() {
    struct sockaddr_in serv_addr;
    int sockfd;
    char buff[BUFFSIZE];

    sockfd = socket(AF_INET, SOCK_STREAM,0);
    if(1 == sockfd) {
        std::cout << "Create socket error:" << errno << strerror(errno) << std::endl;
        return -1;
    }

    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET,SERVER_IP,&serv_addr.sin_addr);
    serv_addr.sin_port = htons(SERVER_PORT);
    if(-1 == connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))) {
        std::cout << "Connect error:" << errno << strerror(errno) << std::endl;
        return -1;
    }
    std::cout << "please enter the message:" << std::endl;
    std::cin >> buff;
    send(sockfd, buff, strlen(buff),0);
    bzero(buff, sizeof(buff));
    recv(sockfd,buff,BUFFSIZE-1,0);
    std::cout << "Received message from server:" << buff <<std::endl;
    close(sockfd);
    return 0;
}
