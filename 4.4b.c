#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>


void func(int sockfd)
{
	char buff[100];
	int h;


	for(;;)
	{
		bzero(buff, 100);


		read(sockfd, buff, sizeof(buff));

		printf("Client:%sYou :", buff);
		bzero(buff, 100);
		h = 0;

		while((buff[h++] = getchar()!='\n'));
		
		if(strncmp("exit", buff, 4) == 0)
		{
			printf("\nEXIT SERVER...\n");
			printf("*****Hi! Welcome to Chat Channel*****\n\n");
			break;
		}
	}
}


int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;


	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		printf("FAILED to create the Socket!!!\n");
		exit(0);
	}
	else
	{
		printf("SUCCESS to create the Socket!!!\n");
	}
	bzero(&servaddr, sizeof(servaddr));


	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons( 8888 );


	if((bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)))!=0){

		printf("SOCKET FAILED TO BIND!!!\n");
		exit(0);
	}

	else
	
		printf("SOCKET SUCCESSFULLY BINDED!!!");



	if((listen(sockfd, 5))!=0)
	{
		printf("FAILED TO LISTEN!!!\n");
		exit(0);
	}
	else
	{
		printf("\nSERVER IS LISTENING FOR YOU\n");
	}
	len = sizeof(cli);


	connfd = accept(sockfd, (struct sockaddr*)&cli, &len);
	if(connfd < 0)
	{
		printf("ACCEPTANCE BY THE SERVER FAILED!!!\n");
		exit(0);
	}
	else
	{
		printf("CLIENT WAS ACCEPTED BY THE SERVER. TO START A CONVERSATION, SEND A RESPONSE MESSAGE!\n");
		printf("\nTYPE EXIT TO CLOSE THE SERVER AND CHAT CHANNEL\n\n");
	}


	func(connfd);

	close(sockfd);
}
