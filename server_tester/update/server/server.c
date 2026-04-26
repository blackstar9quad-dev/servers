#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <../dbase.h>
#include <../socket_custom>
#include <../parser.h>

char PORT[10];
char *server_addr = "127.0.0.1";

int socket_connection(int fd ,int *client , struct sockaddr_in *client_info, struct adddrinfo *pol , fd_set *masterfds, int *piper){
	int bind_fd ;
	printf("binding the socket \n");

	bind_fd = bind(fd,pol->addr , pol->addrlen);
	if(bind_fd<0){
		perror("BINDING ERROR \n");
		return -1;
	};
	if(listen(fd,5) < 0){
		perror("LISTENING ERROR \n");
		return -1; 
	};

	printf("server is listening for connection \n");

	int res;

	if(global_server_config.fork_connection == 1){
		res = fork_route();
		if(res <0){
			printf("OPERATION FAILED : SERVER DOWN \n");
			return -1;
		};
	}else{
		res = select_route();
		if(res<0){
			printf("OPERATION FAILED : SERVER DOWN \n");
			return -1;
		};
	};

	/*res = forker(fd ,client ,client_info , pol , masterfds, piper);
	if(res<0){
		printf("OPERATION FAILED : FOKER \n");
		return -1;
	};*/

	printf("OPERATION CLOSED \n");
	return 0;
};

int socket_creator(int *fd , struct addrinfo *server , struct addrinfo *pol){
	printf("CREATING THE SOCKET \n");

	memset(server,0,sizeof(*server));
	server->ai_family = AF_INET ;
	server->ai_flags = AF_PASSIVE ;
	server->ai_addrlen = sizeof(*server);
	server->ai_socktype = SOCK_STREAM ;

	PORT =  global_server_config.PORT ;

	if(getaddrinfo(server_addr,PORT,server,&pol) !=0){
		perror("ADDRINFO ERROR \n");
		return -1;
	};
	
	*fd = socket(pol->ai_family, pol->ai_socktype , pol->ai_protocol);
	if(*fd<0){
		perror("SOCKET CREATION ERROR \n");
		return -1;
	};

	printf("SOCKET  CREATED \n");
	return 0;
};

int main(int argc , char *args[]){
	int server_fd , client_fd , piper[2];
	fd_set readfds , masterfds ;
	int res;
	sockaddr_in client_info ;
	struct addrinfo server,pol;
	int checker;
	char choice[10];

	FD_ZERO(masterfds);
	FD_ZERO(readfds);

	int pipe_d ;
	pipe_d = pipe(piper);
	if(pipe_d<0){
		perror("PIPE CREATION ERROR \n");
		return -1;
	};
	printf("pipe created \n");
	FD_SET(piper[0] , masterfds);

//-------------------------------------------------------------------------------------------------//
                                //USER CONFORMATION 

	printf("DO U WANT TO RUN THE SERVER WITH THE CURRENT CONFIGS \n");
	for(int i = 1 ; i <=argc ; i++){
		printf("%s \n",args[i]);
	};
	if(!fgets(choice,sizeof(choice),stdin) ){
		perror("INPU ERROR \n");
		return -1;
	};
	if(strcmp(choice,"no") == 0){
		printf("exiting the process \n");
		return -1;
	}else if(strcmp(choice,"yes") == 0){
		printf("Starting the server ......... \n");
	}else{
		printf("WRONG OPTION ENTERED \n");
		printf("EXITING \n");
		return -1;
	};
//--------------------------------------------------------------------------------------------------//

	if(command_parser(int argc , char *args[]) < 0){
		printf("OPERATION FAILED \n");
		return -1;
	};
	printf("command parsed and socket option taken in consideration \m");

	if(socket_creator(&fd ,&server, &pol) <0){
		perror("OPERATION FAILED : SOCKET CREATION  \n");
		return -1;
	};  //has to add the port parser option in the commnad_parser file ;
	printf("socket creation for the server completed \n");

	checker = 1 ;
	if(socket_optimizer(fd,checker) <0){
		printf("OPERATION FAILED : SOCKET OPTIMIZATION \n");
		return -1; 
	};
	printf("the server socket has been optimized by users passed flags \n");
	FD_SET(fd,masterfds);

	if(socket_connection(fd,&client,client_info,pol,&masterfds,&piper) <0){
		printf("OPERATION FAILED : BINDING CONNECTION \n");
		return -1;
	};
	printf("socket connection has been established \n");

};

