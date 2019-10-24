#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define MAX 80 
#define MAXLINE 1024
#define PORT 5002
#define SA struct sockaddr 
	int sockfd, connfd, len; 
	struct sockaddr_in servaddr, cli; 

// Function designed for chat between client and server. 
void func(int sockfd) 
{ 
	char buffer[MAX]; 

	// infinite loop for chat 
	for (;;) { 
		bzero(buffer, MAX); 

		// read the message from client and copy it in buffer 
		int n,len; 
		n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cli, &len); 
		// print buffer which contains the client contents 
		printf("From client: %s\t To client : ", buffer); 
		bzero(buffer, MAX); 
		n = 0; 
		// copy server message in the buffer 
		while ((buffer[n++] = getchar()) != '\n') 
			; 

		// and send that buffer to client 
		buffer[n] = '\0'; 
	printf("Client : %s\n", buffer); 
	sendto(sockfd, (const char *)buffer, strlen(buffer), 
		MSG_CONFIRM, (const struct sockaddr *) &cli, 
			len); 
	printf("Yeahhhhhhhh!!!!!!!!!!!\nHello message sent to Client.\n"); 

		// if msg contains "Exit" then server exit and chat ended. 
		if (strncmp("exit", buffer, 4) == 0) { 
			printf("Server Exit...\n"); 
			break; 
		} 
	} 
} 

// Driver function 
int main() 
{ 


	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0); 

	//Sets all buffer as  initially
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; //this is domain
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); //predefined

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n"); 

	// Function for chatting between client and server 
	func(connfd); 

	// After chatting close the socket 
	close(sockfd); 
} 

