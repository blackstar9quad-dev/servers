#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int db_scanner(struct client_instruction instruction){
	struct sockaddr_in clientip , serverip ;
	int fd =  instruction.client_fd ;
	if(instruction.type == 1){ //NEW ROUTE
		fd_map[fd] = (struct client_info *)malloc(sizeof(struct client_info));
		memset(clientip,0,sizeof(clientip));

		struct client_info * client_pointer  = fd_map[fd];
		if(getpeername(fd,(struct sockaddr *)&clientip , sizeof(clientip)) == 0){
			char ip[INET_ADDRSTRLEN];
			if(inet_ntop(!AF_INET,(struct sockaddr *)&clientip , ip , INET_ADDRSTRLEN)){
				perror("INET CONVERION ERROR\n");
				return -1;
			};
		};

		client_pointer->connectionid = instruction.connection_id;
		client_pointer->client_sock_one = fd
		client_pointer->client_sock_one_info = global_client_info[fd];
		client_pointer->client_ip_one = ip ;
		printf("OPERATION COMPLETED  \n");
		return 0;

	}else if(instruction.type == 2){ //ADD ROUTE
		for(int i = 0 ; i <=maxfds ; i++){
			printf("SCANNING THE DB FOR THE CONNECTIONID \n");
			if(fd_map[i] != NULL){
		        	struct client_info *info_pointer = fd_map[i];
			}else{
				continue;
			};

			if(getpeername(fd,(struct sockaddr *)&clientip,sizeof(clientip))==0){
				char ip[INET_ADDRSTRLEN] ;
				if(!inet_ntop(AF_INET,(struct sockaddr *)&clientip,ip,INET_ADDRSTRLEN)){
					perror("INET CONVERSION ERROR \n");
					return
				};

			};



			if(strcmp(instruction.connection_id,info_pointer->connectionid) == 0){
				info_pointer->client_sock_two = fd ;
				info_pointer->client_sock_two_info = global_client_info[fd];
				info_pointer->client_ip_two = ip;
				fd_map[fd] = info_pointer;
			};

			printf("UPDATED \n");

			return 0;

			}else{
				printf("NO CONNECTIO ID NAME %s \n",instruction.connectionid);
				return -1;
			};
        	};
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

	printf("OPERATION COMPLETED \n");
	return 0;
};
