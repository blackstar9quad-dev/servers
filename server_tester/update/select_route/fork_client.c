#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


struct client_instruction *instruction_parser(int client_fd ,char buffer[2048]){
	char *pointer ;
	struct client_instruction *instruction;
	pointer = strchr(buffer,"@");
	if(!pointer){
		perror("WRONG INSTRUCTION OR STRCHR ERROR \n");
		return -1;
	};

	*pointer = '\0';
	instruction = (struct client_instruction *)malloc(sizeof(struct client_instruction));

	instruction->type = pointer - 1;
	instruction->connection_id =  pointer + 1;
	instruction->client_fd = client_fd ;

	return instruction;
};

int fork_worker(int *piper , int client_fd){
	char buffer[2048];
	char message[] = "ENTER THE INSTRUCTION \n";
	int wrt , rds ;

	wrt =  write(client_fd,message,strlen(message));
	if(wrt<0){
		perror("WRITE ERROR \n");
		return -1;
	};

	rds = read(client_fd,buffer,sizeof(buffer));
	if(rds<0){
		perror("READ ERROR \n");
		return -1;
	};
	
	int par;

	struct client_instruction *par = instruction_parser(client_fd ,buffer);

	wrt = write(piper[0],par,sizeof(*par));
	if(wrt<0){
		perror("WRITE ERROR \n");
		return -1;
	};

	printf("SENT TO THE PIPE READ END \n");
	
	return 0;
};

int forker(int fd , int *client_fd , struct sockaddr_in *client_info , fd_set *masterfds, int *piper){
	int choice;
	printf("into the forker funtion \n ");
	*client_fd = accept(fd,(struct sockaddr *)client_info,sizeof(struct sockaddr));

	if(global_server_config.select_polling == 1 ){
		FD_SET(*client_fd,masterfds);
	};
		
	if(*client_fd <0){
		perror("ACCEPT ERROR \n");
		return -1;
	}else{
		printf("ACCPETING THE CLINET CONNECTION \n");
		int forker_fd ;
		forker_fd = fork();
		if(forker_fd <0){
			perror("FORKING ERROR \n");
			return -1;
		}else if(forker_fd == 0 ){
			printf("FORK INITLISED \n");
			int worker;
			worker=fork_worker(piper,*client_fd);
			if(worker<0){
				printf("OPERTION FAILED : FORK WORKER \n");
				return -1;
			};

			printf("instruction send \n");
			printf("allocating connection .... \n");
			return 0;
		}else{
			printf("CONNECTION STREAM HAS BEEN TRIGGERED \n");
			return 0;
		};

};
