#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <../dbase.h>

int handle_client(int fd){
	struct client_info *info_pointer = fd_map[fd];
	char choice[10];
	if(info_pointer->client_sock_two == 0){
		printf("NO RECIVER IS PRESENT\n");
		printf("DO U WANNA WRITE TO THE STRUCTURE BUFFER \n");
		if(!fgets(choice,sizeof(choice),stdin)){
			perror("INPUT ERROIR \n");
			return -1;
		};

		if(strcmp(choice,"yes") ==0 ){
			int copy;
			char buffer_fd[4028];
			printf("ENTER THE MESSAGE U WANNA ENTER \n");
			if(!fgets(buffer_fd , sizeof(buffer_fd),stdin)){
				perror("INPUT ERROR \n");
				return -1;
			};
			strcpy(info_pointer->buffer,buffer_fd);

			printf("copyied to the struct buffer \n");
		}else{
			printf("NOTHING TO READ \n");
			return 0;
		};
		
	}else{
		int master , minor;
		printf("ANOTHER CLINET PRESENT CONNECTING .... \n");
		if(fd == info_pointer->client_sock_one){
			master = fd ;
			minor = info_pointer->client_sock_two;
		}else{
			master = fd ;
			minor = info_pointer->client_sock_one;
		};

		if(info_pointer->readcount == 0){
			printf("DATA PRESENT IN THE STRUCTURE BUFFER \n");
			char buffer[4028];
			strcpy(buffer,info_pointer->buffer);

			printf("BUFFER DATA : \n");
			printf("%s",buffer);
			info_pointer->readcount = 1;
		};

		char buffer[1024];
        	printf("CLIENT MESSAGE \n");
		int flag =1
		while(flag){
			char buffer[1024];
			int res ;
			res = read(master,buffer,sizeof(buffer));
			if(res <0){
				perror("READ ERROR \n");
				return -1;
			};

			if(res == 0 ){
				printf("------------------");
				break ;
			};

			printf("%s",buffer);
		};

		char choice[10];
		printf("DO U WANT TO WRITE TO THE CONNECTED CLIENT \n");
		if(!fgets(choice,sizeof(choice),stdin)){
			perror("INPUT ERROR \n");
			return -1;
		};

		if(strcmp(choice,"yes") == 0){
			char buffer_writer[];
			if(!fgets(buffer_writer,sizeof(buffer_writer),stdin)){
				perror("INPUT ERROR \n");
				return -1;
			};
			int wrt ;
			wrt =  write(minor,buffer_writer,sizeof(buffer_writer));
			if(wrt <0){
				perror("WRITING ERROR \n");
				return -1;
			};
			printf("message sent \n");
			return 0;
		};else{
			printf("exiting\n");
			return 0;
		};
	};
};
