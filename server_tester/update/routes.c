#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <./dbase.h>



int fork_route(){
};

//maxfds logic left ;

int select_route(int fd , int *client_fd , struct sockaddr_in *client_info , struct addrinfo *pol , fd_set *masterfds, int *piper , fd_set *readfds){
	printf("INSIDE THE SELECT ROUTE \n");
	while(1){
		FD_ZERO(readfds);
		*masterfds = *readfds ;

		if(pselect(maxfds+1,readfds,NULL,NULL,NULL,NULL) <0){
			perror("PSELECT ERROR \n");
			return -1;
		};

		if(FD_ISSET(piper[0],readfds)){
			int pipe_runner = handle_piper(piper);
			if(pipe_runner <0){
				printf("OPERATION FAILED \n");
				return -1
			};
			printf("entry/updated complete \n");
		}

		if(FD_ISSET(fd,readfds)){
			int forker_runner;
			forker_runner = forker(fd,client_fd ,client_info,masterfds,piper);
			if(forker_runner <0){
				printf("OPERATION FAILED \n");
				return -1;
			};
			printf("New clinet in server \n");
		};

		for(int i = 0 ; i<=maxfds ; i++){
			if(FD_ISSET(i,readfds)){
				int client_runner;
				client_runner = handle_client(i);
				if(client_runner <0){
					perror("OPERATION FAILED \n");
					return -1;
				}
			};
			printf("DONE \n");
		};
	};

};
