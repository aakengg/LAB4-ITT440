#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<stdlib.h>

int main(int argc , char *argv[])
{

	int socket_desc , new_socket , c;
	struct sockaddr_in server , client;
	char *message;
	int optval;
	socklen_t optlen = sizeof(optval);


	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}


	if(getsockopt(socket_desc, SOL_SOCKET, SO_KEEPALIVE, &optval , &optlen) <0) {
	 perror("getsockopt()");
	 close(socket_desc);
	 exit(EXIT_FAILURE);
	 }
	 printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));


	 optval = 1;
	 optlen = sizeof(optval);
	 if(setsockopt(socket_desc, SOL_SOCKET , SO_KEEPALIVE , &optval , optlen) < 0) {
	  perror("setsockopt()");
	  close(socket_desc);
	  exit(EXIT_FAILURE);
	 }
	 printf("SO_KEEPALIVE set on socket\n");
	

	 if(getsockopt(socket_desc, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) <0) {
	 perror("getsockopt()");
	 close(socket_desc);
	 exit(EXIT_FAILURE);
	 }
	 printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));


	 server.sin_family = AF_INET;
	 server.sin_addr.s_addr = INADDR_ANY;
	 server.sin_port = htons( 8888 );


	 if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	 {
		puts("bind failed");
		return 1;
	 }
	 puts("bind done");


	 listen(socket_desc , 3);



	 puts("Waiting for incoming connections...");
	 c = sizeof(struct sockaddr_in);
	 while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
	 {
		puts("Connection accepted");

		message = "Hello Client , I have received your connection. But I have to go now, bye\n";
		write(new_socket , message , strlen(message));
	 }

	 if (new_socket<0)
	 {
		perror("accept failed");
		return 1;
	 }

	
	 return 1;

}
