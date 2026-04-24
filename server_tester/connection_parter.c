#include <./debase.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


int client_network_handler(int client_fd ,  int server_fd , struct addrinfo server , int piper[2]){
	int reader, writer ;
	char connection_info[1024];
	char message[] = "GIVE THE CONNECTION DETAIL \n";

	printf("ASKING THE CLIENT FOR THE CONNECTION INFO \n");
	writer =  write(client_fd,message,strlen(message));
	if(writer < 0){
		perror("WRITER ERROR \n");
		return -1;
	};

	printf("SENT \n");
	loff_t offset = 0;
	while(bytes_read > offset){
		byte_read = read(clientfd,connection_info+offset,sizeof(connection_info)-offset);
        	if(bytes_read <0){
	        	perror("READ  ERROR \n");
		        return -1;
        	}else if(reader == 0){
	        	printf("NOTHING TO READ \n");
	        	break;
        	};

		offset += bytes_read ;
	};

	printf("user detail recived \n");

	if(write(piper[1],connection_info,strlen(connection_info)) <0){
		perror("ERROR IN WRITING TO THE PIPE \n");
		return -1;
	};

	printf("WRITTEN TO THE PIPE \n");

	return 0;
};

int connection_parter(int fd ,int clientfd , struct sockaddr_in *client, fd_set masterfds , int piper[2] ){
	int creation, res ,  status , pip;
	pip = pipe(pipe(piper));
	clientfd =  accept(fd,(struct sockaddr *)client , sizeof(*client));

	if(global_server_config.select_polling == 1 ){
		FD_ZERO(masterfds);
		FD_SET(creation,masterfds);
        	FD_SET(piper[0],masterfds);
        	FD_SET(clientfd,masterfds);
        	FD_SET(fd,masterfds);
	};

	if(clientfd>max_fds){
		max_fds = clientfds ;
	}
	if(piper[0]>max_fds){
		max_fds = piper[0];
	}
	if(piper[1] > max_fds){
		max_fds = piper[1];
	}
	if(fd> max_fds){
		max_fds = fd ;
	};

	if(creation <0){
		perror("ERROR IN ACCEPTING THE CLINET CONNECTION \n");
		return -1;
	}else if(creation == 0){
		printf("client connected \n");
		int forker ;
		forker = fork();
		if(forker < 0){
			perror("ERROR IN FORKING THE PROCESS \n");
			return -1;
		}else if(forker == 0){
			res = client_network_handler(creation,fd,server,piper);
			if(res<0){
				perror("OPERATION FAILED  IN FORK \n"):
					return -1;
			}else{
				printf("OPERATION SUCCESSFUL \n");
				return 0;
			};
		};
	}else{
		printf("parentent is continuing \n");

		if(global_server_config.select_polling == 1){
			res = select_server();
			if(res < 0){
				printf("OPERATION FAILED \n");
				return -1;
			};
		}else if(global_server_config.fork_connection == 1){
			res = fork_connect();
			if(res<0){
				printf("OPERATION FAILED \n");
				return -1;
			};
		}else
	};
};
