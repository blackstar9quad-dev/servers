#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <../dbase.h>


int PORT ;
char address[];

int comparor(){
};

int db(){
};

int signal_handler(){
};

int child_creation(){
};

int fd_studio(){
};

int director(){
};

int network_listener(){
};

int network_initlizor(){
};

int socket_listener(int fd, int clientfd , struct sockaddr_in *client , fd_set masterfd , int piper[2]){

	printf("Binding the socktet to the port and the ip \n");
	if(bind(fd,addr_pointer->ai_family,addr_pointer->addrlen) <0){
		perror("ERROR IN BINDING THE SOCKET \n");
		return -1;
	};
	printf("Binding complete \n");

	printf("Server Listening for connections \n");
	if(listen(fd,5)<0){
		perror("LISTENING ERROR \n");
		return -1;
	}else{
		int res =  connection_parter(fd ,clientfd, client , masterfd,piper);
	};
};

int socket_initlizor(struct addrinfo *server , struct addrinfo *pol , int *fd){
	char  port[10];
	int res;
	printf("CREATING THE SERVER SOCKET \n");
	printf("ENTER THE IP ADDRESS OF THE SERVER \n");
	if(!fgets(address,sizeof(address),stdin)){
		perror("input error \n");
		return -1;
	};

	printf("ENTER THE PORT NUMBER \n");
	if(!fgets(port,sizeof(port),stdin)){
		perror("INPUT ERROR \n");
		return -1;
	};

	PORT = (int) strtol(port,NULL,10);

	memset(server,0,sizeof(*server));
	server->ai_family = AF_INET;
	server->ai_flags = AI_PASSIVE;
	server->ai_socktype = SOCK_STREAM ;
	server->addrlen = sizeof(*server);

	res = getaddrinfo(address,PORT,server,pol);
	if(res !=0){
		printf("ADDRINFO ERROR \n");
		return -1;
	};

	*fd = socket(pol->ai_family , pol->ai_socktype , pol->ai_protocol);
	if(*fd <0){
		printf("socket creation error \n");
		return -1;
	};

	printf("server socket created \n");

	return 0;
	
};

int main(int argc , char *args[]){
	fd_set readfds , masterfds;
	struct addrinfo server , pol ;
	struct sockaddr_in client ;
	int res , fd ,  client_fd , piper[2] ;
	char choice[10];
	int checker = 1 ;  // 1 stands for the server and 0 is for the client to diffrentiate whose sockinfo to fill when in socket_optimizer

	
	printf("STARTING THE PROCESS ...... ]n");

	printf("do u wanna start the server \n");
	if(!fgets(choice,sizeof(choice),stdin)){
		perror("INPUT ERROR \n");
		return -1;
	};

	if(strcmp("yes",choice) == 0){
		memeset(&global_server_config,0,sizeof(global_server_config));
		printf("STARTING THE SERVER CREATION \n");
		if(res = socket_initlizor(&server , &pol , &fd)<0){
			printf("OPERATION FAILED \n");
			return -1;
		};
	}else{
		printf("EXITING THE PROCESS \n");
		return 0;
	};

	res = command_parser(argc , args);
	if(res <0){
		printf("OPERATION FAILED \n");
		return -1;
	};

	res = socket_optimizer(fd,pol,argc,args,checker);
	if(res<0){
		printf("operation failed \n");
		return -1;
	};

	if(socket_listener(fd,pol , &client , &client_fd) < 0){
		printf("OPERATION FAILED \n");
		return 0;
	};
};

