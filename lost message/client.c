#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

short SocketCreate(void)
{
	short hsocket;
	printf("Create the socket\n");
	hsocket = socket(AF_INET,SOCK_DGRAM,0);
	return hsocket;
}
  
int SocketConnect(int hsocket)
{
	int iRetval=-1;
	int ServerPort = 90190;
	struct sockaddr_in remote={0};
	
	remote.sin_addr.s_addr = inet_addr("127.0.0.1");
	remote.sin_family = AF_INET;
	remote.sin_port = htons(ServerPort);
	
	iRetval=connect(hsocket,(struct sockaddr *)&remote,sizeof(struct sockaddr_in));
	return iRetval;
}
int SocketSend(int hSocket,char* Rqst,short lenRqst)
{
	int shortRetval = -1;
	struct timeval tv;
	tv.tv_sec = 20;
	tv.tv_usec = 0;
	
	if(setsockopt(hSocket,SOL_SOCKET,SO_SNDTIMEO,(char *)&tv,sizeof(tv))<0)
	{
		printf("Time Out\n");
		return -1;
	}
	shortRetval = send(hSocket , Rqst , lenRqst , 0);
	return shortRetval;
}

int SocketReceive(int hSocket,char* Rsp,short RvcSize)
{
	int shortRetval = -1;
	struct timeval tv;
	tv.tv_sec = 20; /* 20 secs Timeout */
	tv.tv_usec=0;
	
	if(setsockopt(hSocket,SOL_SOCKET,SO_RCVTIMEO,(char *)&tv,sizeof(tv))<0)
	{
		printf("time Out\n");
		return -1;
	}
	shortRetval = recv(hSocket , Rsp , RvcSize , 0);
	printf("Response %s\n",Rsp);
	return shortRetval;
}

int main(int argc , char *argv[])
{
	int hSocket, read_size;
	struct sockaddr_in server;
	char SendToServer[100] = {0};
	char server_reply[200] = {0};
	
	hSocket = SocketCreate();
	if(hSocket == -1)
	{
		printf("Could not create socket\n");
		return 1;
	}
	printf("socket is created");
	
	if(SocketConnect(hSocket)<0)
	{
		perror("connect failed.\n");
		return 1;
	}
	printf("Successfully connected with server\n");
	printf("enetr the message");
	gets(SendToServer);
	
	SocketSend(hSocket,SendToServer,strlen(SendToServer));
	
	read_size = SocketReceive(hSocket , server_reply , 200);
	printf("Server Response: %s\n\n",server_reply);
	
	close(hSocket);
	shutdown(hSocket,0);
	shutdown(hSocket,1);
	shutdown(hSocket,2);
	return 0;
}