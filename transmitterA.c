#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define MAX 80 
#define PORT 4021
#define SA struct sockaddr 

// Function designed for chat between client and server. 
void func(int sockfd) 
{ 
	char buff[MAX]; 
	int n; 
	int i;
	// infinite loop for chat 
	for (i=0;i<5;i++) { 
		bzero(buff, MAX); 

		// read the message from client and copy it in buffer 
		read(sockfd, buff, sizeof(buff)); 

		// print buffer which contains the client contents 
		printf("acknowledgement From client: %s\t : ", buff); 
		int flag=0;
		if(buff=='0')
			flag=0;
		else
			flag=1;
		printf("the flag is %d\n",flag);		
				
		bzero(buff, MAX); 
		n = 0;
 
		// copy server message in the buffer 
		char s[]="ACK 1";
		char t[]="BCK 0";
		//while ((buff[n++] = getchar()) != '\n') 
			//'; 

			// printf("the curretn buffer is : %s\t ", buff); 
		//int i;
		//for(i=0;i<5;i++)
		//	buff[i]=s[i];
		
		if(flag==1)
		{
			write(sockfd, t, sizeof(6));\
			flag=0;
		}
			
		else if(flag==0)
		{
			write(sockfd, t, sizeof(6));
			flag=1;
		}
			
		
		// and send that buffer to client 
		 

		// if msg contains "Exit" then server exit and chat ended. 
		if (strncmp("exit", buff, 4) == 0) { 
			printf("Server Exit...\n"); 
			break; 
		} 
	} 
} 

// Driver function 
int main() 
{ 
	int sockfd, connfd, len; 
	struct sockaddr_in servaddr, cli; 

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
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

	// Now server is ready to listen and verification 
	if ((listen(sockfd, 5)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n"); 
	len = sizeof(cli); 

	// Accept the data packet from client and verification 
	connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	} 
	else
		printf("server acccept the client...\n"); 

	// Function for chatting between client and server 
	func(connfd); 

	// After chatting close the socket 
	close(sockfd); 
} 

