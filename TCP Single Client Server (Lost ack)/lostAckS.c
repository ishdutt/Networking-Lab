//server lost ack
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
void error(const char *msg)
{
   perror(msg);
   exit(1);
}
int main(int argc,char *argv[])
{
    int sockfd,newsockfd,portno,clien;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if(argc < 2)
    {
       fprintf(stderr,"ERROR,no port provided\n");
       exit(1);
    }
 
 
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd <0)
    {
       error("ERROR opening socket");
    }
    bzero((char*)&serv_addr, sizeof(serv_addr));
    
    // assign IP, PORT
    portno=atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
 
    // Binding newly created socket to given IP and verification
    if (bind(sockfd,(struct sockaddr*) &serv_addr, sizeof(serv_addr)) <0 )
    {
        error("ERROR on binding");
    }
    listen(sockfd,5);
    clien=sizeof(cli_addr);
    newsockfd=accept(sockfd,(struct sockaddr*) &cli_addr,&clien);
    if(newsockfd<0)
    {
       error("ERROR on accept");
    }
    bzero(buffer,256);
    n=read(newsockfd,buffer,255);
    if(n<0)
    {
       error("ERROR reading from socket");
    }
    printf("Here is the message: %s \n",buffer);
    sleep(8);
    n=write(newsockfd,"I got your message",18);
    if(n<0)
    {
       error("ERROR writing to socket");
    }
    close(newsockfd);
    close(sockfd);
    return 0;

}
