#include <./dbase.h>
#include <./connection_parser>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int select_server(fd_set masterfds , fd_set readfds){
	for(int i = 0 ; i<=max_fds ; i++ ){
		fd_map[i] = NULL;
	};
	while(1){
		FD_ZERO(readfds);
		readfds = masterfds ;

		if(select(

		if(FD_ISSET
	};
};

int for_connect(){
};

