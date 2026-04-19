#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <../dbase.h>

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

int socket_initlizor(){
};

int main(int argc , char *args[]){
	int res ;
	printf("STARTING THE PROCESS ...... ]n");

	res = command_parser(argc , args);
	if(res <0){
		printf("OPERATION FAILED \n");
		return -1;
	};
};

