#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int db_scanner(struct client_instruction instruction){
	int fd =  instruction.client_fd ;
	if(instruction.type == 1){ //NEW ROUTE
		fd_map[fd] = (struct client_info *)malloc(sizeof(struct client_info));
		struct client_info * client_pointer  = fd_map[fd];

		client_pointer->
		client_pointer->
		client_pointer->

	}else if(instruction.type == 2){ //ADD ROUTE 
	};
};

int handle_pipe(int *piper){
	struct client_instruction instruction_buffer;
	int rds,res;

	rds = read(piper[0],&instruction_buffer,sizeof(instrution_buffer));
	if(rds<0){
		perror("READ ERROR \n");
		return -1 ;
	};

	res = db_scanner(instruction_buffer);
	if(res<0){
		printf("OPERATION FAILED : DB_SCANNER \n");
		return -1;
	};
};
