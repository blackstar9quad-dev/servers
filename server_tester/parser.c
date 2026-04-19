#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <../dbase.h>

int command_parser(int argc , char *args[]){
	printf("extracting the command modules \n");

	for(int i= 0 ; i<=argc ; i++){
		char *arg = args[i];
		char *eq_pt = strchr(arg,"=");

		if(!ep_pt){
			*eq_pt = '\0';
			char *key = args[i];
			char *value = eq_pt + 1;

			if(strcmp("--reuseaddr",key) == 0){  //reuseaddr
				if(strcmp("1",value) == 0){
				}else if(strcmp("0",value) == 0){
				}else{
				};
			};

			if(strcmp("--sender-buffer",key) == 0){ //send_buff | sender_buffer
				size_t buffer_size;
				buffer_size = (size_t)strtol(value,NULL,10);


			};

         	       	if(strcmp("--reciver-buffer",key) == 0){ //recv_buff | reciver_buffer
				size_t buffer_size;
				buffer_size = (size_t)strtol(value,NULL,10);


         		};

         		if(strcmp("--keepalive",key) == 0){  //keepalive
				if(strcmp("1",value) == ){
				}else if(strcmp("0",value) == 0){
				}else{
				};
	         	};

         		if(strcmp("--linger",key) == 0){  //linger |  time_linger
				int time_linger ;
				time_linger = (int)strtol(value,NULL,10);


         		};

        		if(strcmp("--reader_timeout",key) == 0){ //recvtime | struct timeval reader_timeout
				time_t recvtime ;
				recvtime = (time_t)strtol(value,NULL,10);


        		};

        		if(strcmp("--sender_timeout",key) == 0){ //writetime | struct timeval writer_timeout
				time_t writetime;
				writetime = (time_t) strtol(value,NULL,10);

        		};

        		if(strcmp("--non-blocking",key) == 0){ //non-blocking
				if(strcmp("1",value) == 0){
				}else if(strcmp("0",value) == 0){
				}else{
				};
        		};

        		if(strcmp("--log-socket",key) == 0){ //log-socket
				if(strcmp("1",value) == 0){
				}else if(strcmp("0",value)  == 0){
				}else{
				};
        		};

        		if(strcmp("--listener",key) == 0){ //listen_socket
				if(strcmp("1",value) == 0){
				}else if(strcmp("0",value) == 0){
				}else{
				};
        		};

        		if(strcmp("--reuseport",key) == 0){ // used_port | recivers
				int reciver ; 
				reciver = (int)strtol(value,NULL,10);


        		};

        		if(strcmp("--idle",key) == 0){ //keepidle | idle 
				int idle_time ;
				idle_time  = (int)strtol(value,NULL,10);

        		};

        		if(strcmp("--interval",key) == 0){ // kerrpintvl | interval 
				int interval_time ;
				interval_time = (int) strtol(value,NULL,10);

        		};

        		if(strcmp("--count",key) == 0){ // keepcnt | count 
				int count ;
				count = (int) strtol(value,NULL,10);

        		};

        		if(strcmp("--nodelay",key) == 0){ //nodelay
				if(strcmp("1",value) == 0){
				}else if(strcmp("0",value) == 0){
				}else {
				};
        		};

        		if(strcmp("--info", key) == 0){ //info | tcp_info 
				if(strcmp("1",value) == 0){
				}else if(strcmp("0",value) == 0){
				}else {
				};
        		};

        		if(strcmp("--fastopen",key) == 0){ //fastopen | queue_length 
				int queue;
				queue = (int) strtol(value,NULL,10);

        		} ;

        		if(strcmp("--ttl",key) == 0){ // ttl | tt_hop 
				int hop;
				hop = (int) strtol(value,NULL,10);

        		};

        		if(strcmp("--tos",key) == 0){ // tod | tos_value 
				int tos ;
				tos = (int) strtol(value,NULL,10);
			};


		}else {
			char *value ;
			value  = args[i]+2;

			if(strcmp("--reuseaddr",args[i]) == 0){  //reuseaddr
				if(strcmp("1",value) == 0){
				}else if(strcmp("0",value) == 0){
				}else{
				};
			};

			if(strcmp("--sender-buffer",args[i]) == 0){ //send_buff | sender_buffer
				size_t buffer_size;
				buffer_size = (size_t)strtol(value,NULL,10);


			};

         	       	if(strcmp("--reciver-buffer",args[i]) == 0){ //recv_buff | reciver_buffer
				size_t buffer_size;
				buffer_size = (size_t)strtol(value,NULL,10);


         		};

         		if(strcmp("--keepalive",args[i]) == 0){  //keepalive
				if(strcmp("1",value) == ){
				}else if(strcmp("0",value) == 0){
				}else{
				};
	         	};

         		if(strcmp("--linger",args[i]) == 0){  //linger |  time_linger
				int time_linger ;
				time_linger = (int)strtol(value,NULL,10);


         		};

        		if(strcmp("--reader_timeout",args[i]) == 0){ //recvtime | struct timeval reader_timeout
				time_t recvtime ;
				recvtime = (time_t)strtol(value,NULL,10);


        		};

        		if(strcmp("--sender_timeout",args[i]) == 0){ //writetime | struct timeval writer_timeout
				time_t writetime;
				writetime = (time_t) strtol(value,NULL,10);

        		};

        		if(strcmp("--non-blocking",args[i]) == 0){ //non-blocking
				if(strcmp("1",value) == 0){
				}else if(strcmp("0",value) == 0){
				}else{
				};
        		};

        		if(strcmp("--log-socket",args[i]) == 0){ //log-socket
				if(strcmp("1",value) == 0){
				}else if(strcmp("0",value)  == 0){
				}else{
				};
        		};

        		if(strcmp("--listener",args[i]) == 0){ //listen_socket
				if(strcmp("1",value) == 0){
				}else if(strcmp("0",value) == 0){
				}else{
				};
        		};

        		if(strcmp("--reuseport",args[i]) == 0){ // used_port | recivers
				int reciver ; 
				reciver = (int)strtol(value,NULL,10);


        		};

        		if(strcmp("--idle",args[i]) == 0){ //keepidle | idle 
				int idle_time ;
				idle_time  = (int)strtol(value,NULL,10);

        		};

        		if(strcmp("--interval",args[i]) == 0){ // kerrpintvl | interval 
				int interval_time ;
				interval_time = (int) strtol(value,NULL,10);

        		};

        		if(strcmp("--count",args[i]) == 0){ // keepcnt | count 
				int count ;
				count = (int) strtol(value,NULL,10);

        		};

        		if(strcmp("--nodelay",args[i]) == 0){ //nodelay
				if(strcmp("1",value) == 0){
				}else if(strcmp("0",value) == 0){
				}else {
				};
        		};

        		if(strcmp("--info", args[i]) == 0){ //info | tcp_info 
				if(strcmp("1",value) == 0){
				}else if(strcmp("0",value) == 0){
				}else {
				};
        		};

        		if(strcmp("--fastopen",args[i]) == 0){ //fastopen | queue_length 
				int queue;
				queue = (int) strtol(value,NULL,10);

        		} ;

        		if(strcmp("--ttl",args[i]) == 0){ // ttl | tt_hop 
				int hop;
				hop = (int) strtol(value,NULL,10);

        		};

        		if(strcmp("--tos",args[i]) == 0){ // tod | tos_value 
				int tos ;
				tos = (int) strtol(value,NULL,10);
			};


		};
	};
};
