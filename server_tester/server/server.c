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

int socket_optifier(){
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
	struct addrinfo server , pol ;
	int res , fd ;
	char choice[10];
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

	res = socket_optimizer(pol,fd);
	if(res<0){
		printf("operation failed \n");
		return -1;
	};



};

