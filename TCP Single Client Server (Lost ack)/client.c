//client lost ack
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
void error(const char *msg)
{
perror(msg);
exit(0);
}

int SocketReceive(int hSocket,char* Rsp,short RcvSize)
{
int shortRetval=-1;
struct timeval tv;
tv.tv_sec=3;
tv.tv_usec=0;
if(setsockopt(hSocket,SOL_SOCKET,SO_RCVTIMEO,(char *) &tv,sizeof(tv))<0)
{
printf("time  out\n");
return -1;
}
shortRetval=recv(hSocket,Rsp,RcvSize,0);
printf("Response %s\n",Rsp);
return shortRetval;
}
int main(int argc,char *argv[])
{
    int sockfd,portno,n;
    char buffer[256];
    struct sockaddr_in serv_addr;
    struct hostent* server;
    if(argc < 3)
    {
     fprintf(stderr,"usage %s hostname port \n",argv[0]);
     exit(0);
    }

 
    // socket create and verification
    portno=atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd <0)
    {
     error("ERROR opening socket");
    }
    server = gethostbyname(argv[1]);
    if(server==NULL)
    {
    fprintf(stderr,"ERROR ,no such host\n");
    exit(0);
    }

    bzero((char*)&serv_addr, sizeof(serv_addr));
       // assign IP, PORT
     
    serv_addr.sin_family = AF_INET;
    bcopy((char*) server->h_addr,(char*)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);
 
   if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
   {
    error("ERROR connecting");
   }
    printf("please enter the message:");
    bzero(buffer,256);
    fgets(buffer,225,stdin);
    n=write(sockfd,buffer,strlen(buffer));
    if(n<0)
    {
    error("ERROR writing to socket");
    }
    bzero(buffer,256);
    n=SocketReceive(sockfd,buffer,255);
    if(n<0)
    {
    error("ERROR reading from socket");
    }

    printf("%s\n",buffer);
    close(sockfd);
    return 0;
    }