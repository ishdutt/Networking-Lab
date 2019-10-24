#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#define MAX 80 
#define PORT 5002
#define MAXLINE 1024
#define SA struct sockaddr 
	int sockfd, connfd; 
	struct sockaddr_in servaddr, cli; //for storing server and client address
void func(int sockfd) 
{ 
	char buffer[MAX]; 
	int n,len; 
	for (;;) { 
		bzero(buffer, sizeof(buffer)); 
		printf("Enter the string : "); 
		n = 0; 
		while ((buffer[n++] = getchar()) != '\n') 
			; 		
		sendto(sockfd, (const char *)buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 
		
		printf("Hello message sent.\n"); 
		bzero(buffer, sizeof(buffer)); 
		n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 
		buffer[n] = '\0'; 
		printf("Server : %s\n", buffer);


		if ((strncmp(buffer, "exit", 4)) == 0) { 
			printf("Client Exit...\n"); 
			break; 
		} 
	} 
} 

int main() 
{ 


	// socket create and varification 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0); 


	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 


	// function for chat 
	func(sockfd); 

	// close the socket 
	close(sockfd); 
} 

