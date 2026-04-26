#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <../dbase.h>

int command_parser(int argc , char *args[]){
	int fd_log ;

	global_server_config.tcp_info = (struct tcp_infos*)malloc(sizeof(struct tcp_infos));
	global_server_config.ip_info = (struct ip_info *)malloc(sizeof(struct ip_info));

	fd_log = open("log_file.txt" , O_CREAT | O_WRONLY | O_APPEND , 0777);
	if(fd_log<0){
		printf("error in opening the file \n");
		return -1;
	};

	if(dup2(fd_log , STDOUT_FILENO) < 0){
		printf("ERROR IN CHANGING THE OUTPUT LOCATION \n");
		return -1;
	};

	printf("extracting the command modules \n");

	for(int i= 0 ; i<=argc ; i++){
		char *arg = args[i];
		char *eq_pt = strchr(arg,"=");

		if(ep_pt){
			*eq_pt = '\0';
			char *key = args[i];
			char *value = eq_pt + 1;

			if(strcmp("--reuseaddr",key) == 0){  //reuseaddr
				if(strcmp("1",value) == 0){
					global_server_config.reuseaddr = 1;
					printf("reuseaddr set open \n");
				}else if(strcmp("0",value) == 0){
					global_server_config.reuseaddr = 0;
					printf("reuseaddr set off \n");
				}else{
					printf("RESUEADDR WRONG OPTION (DEFAULT MODE :off) \n");
				};
			};


			if(strcmp("--mode",key) == 0){
				if(strcmp(value,"select") == 0){
					global_server_config.select_polling = 1;
					printf("select  mode selceted \n");
				}else if(strcmp(value,"fork") == 0){
					global_server_confog.fork_connection = 1;
					printf("fork mode selected \n");
				}else{
					global_server_config.select_polling = 1;
					printf("NO OPTION / WRONG OPTION (DEFAULT : select mode) \n");
				};
			};



			if(strcmp("--sender-buffer",key) == 0){ //send_buff | sender_buffer
				size_t buffer_size;
				buffer_size = (size_t)strtol(value,NULL,10);

				global_server_config.send_buff = 1 ;
				global_server_config.sender_buffer = buffer_size;
				printf("size of the writer buffer file set to : %d " , buffer_size);
			};

         	       	if(strcmp("--reciver-buffer",key) == 0){ //recv_buff | reciver_buffer
				size_t buffer_size;
				buffer_size = (size_t)strtol(value,NULL,10);
				
				global_server_config.recv_buff = 1;
				global_server_config.reciver_buffer = buffer_size ;
				printf("size of the sender buffer set to : %d " , buffer_size);
         		};

         		if(strcmp("--keepalive",key) == 0){  //keepalive
				if(strcmp("1",value) == ){
					global_server_config.keepalive = 1; 
					printf(" keepalive activated \n");
				}else if(strcmp("0",value) == 0){
					global_server_config.keepalive = 0;
					printf(" keepalive deactivated \n");
				}else{
					printf("wrong option keepalive (default : off) \n");
				};
	         	};

         		if(strcmp("--linger",key) == 0){  //linger |  time_linger
				int time_linger ;
				time_linger = (int)strtol(value,NULL,10);

				global_server_config.linger = 1;
				global_server_config.time_linger = time_linger ;
				printf("linger enabled time period: %ld ",time_linger);
         		};

        		if(strcmp("--reader_timeout",key) == 0){ //recvtime | struct timeval reader_timeout
				time_t recvtime ;
				recvtime = (time_t)strtol(value,NULL,10);

				global_server_config.recvtime  = 1 ;
				global_server_config.reader_timeout.tv_sec = recvtime ;
				global_server_config.reader_timeout.tv_usec = 0;
				printf("timeout of reader set to : %ld sec " , recvtime);
        		};

        		if(strcmp("--sender_timeout",key) == 0){ //writetime | struct timeval writer_timeout
				time_t writetime;
				writetime = (time_t) strtol(value,NULL,10);

				global_server_config.writetime = 1;
				global_server_config.writer_timeout.tv_usec = 0;
				global_server_config.writer_timeout.tv_sec = writetime ;
        		};

        		if(strcmp("--non-blocking",key) == 0){ //non-blocking
				if(strcmp("1",value) == 0){
					global_server_config.non_blocking = 1;
					printf("non-blocking set onn \n");
				}else if(strcmp("0",value) == 0){
					global_server_config.non_blocking = 0;
					printf("non-blocking disabled \n");
				}else{
					printf("wrong option set on non-blocking (DEFAULT: OFF) \n");
				};
        		};

        		if(strcmp("--log-socket",key) == 0){ //log-socket
				if(strcmp("1",value) == 0){
					global_server_config.log_socket = 1;
					printf("so error set onn \n");
				}else if(strcmp("0",value)  == 0){
					global_server_config.log_socket = 0;
					printf("so error set off \n");
				}else{
					printf("worng option set on log-socket \n");
				};

        		};

        		/*if(strcmp("--listener",key) == 0){ //listen_socket
				if(strcmp("1",value) == 0){
					global_server_config.listen_socket = 1 ;
					printf("listen socket set to onn \n");
				}else if(strcmp("0",value) == 0){
					global_server_config.listen_socket = 0;
					printf("listen socket set to off \n");
				}else{
					printf("wrong option on listener \n");
				};
        		};*/

        		if(strcmp("--reuseport",key) == 0){ // used_port | recivers
				int reciver ; 
				reciver = (int)strtol(value,NULL,10);

				global_server_config.used_port = 1 ;
				printf("reuseport set to onn \n");
				if(reciver >0 || reciver <5){
					global_server_config.recivers = reciver;
					printf("number of connetion with SO_RESUSEPORT set to %d \n" , reciver);
				}else{
					global_server_config.reciver = 1;
					printf("wrong option on reuseport set to (default_value : 1) \n");
				};
        		};

        		if(strcmp("--idle",key) == 0){ //keepidle | idle 
				int idle_time ;
				idle_time  = (int)strtol(value,NULL,10);

				global_server_config.tcp_info->keepidle = 1;
				global_server_config.tcp_info->idle = idle_time;

				printf("time to check after silence : %d \n",idle_time);
        		};

        		if(strcmp("--interval",key) == 0){ // keepintvl | interval 
				int interval_time ;
				interval_time = (int) strtol(value,NULL,10);

				global_server_config.tcp_info->keepintvl = 1;
				global_server_config.tcp_info->interval = interval_time ;
				printf("interval between check %d",interval_time);
        		};

        		if(strcmp("--count",key) == 0){ // keepcnt | count 
				int count ;
				count = (int) strtol(value,NULL,10);

				global_server_config.tcp_info->keepcnt = 1;
				global_server_config.tcp_info->count = count ;
				printf("total check to happen %d \n",count);
        		};

        		if(strcmp("--nodelay",key) == 0){ //nodelay
				if(strcmp("1",value) == 0){
					global_server_config.tcp_info->nodelay = 1 ;
					printf("nodelay set to onn \n");
				}else if(strcmp("0",value) == 0){
					global_server_config.tcp_info->nodelay = 0;
					printf("nodelay set to off \n");
				}else {
					printf("worng option set on nodelay (default : 0) \n");
				};
        		};

        		if(strcmp("--info", key) == 0){ //info | tcp_info 
				if(strcmp("1",value) == 0){
					global_server_config.tcp_info->info = 1;
					printf("info retrival set to onn \n");
				}else if(strcmp("0",value) == 0){
					gloabl_server_config.tcp_info->info = 0;
					printf("info retrival set to off \n");
				}else {
					global_server_config.tcp_info->info = 1 ;
					printf("wrong option on info (default : 1) \n");
				};
        		};

        		if(strcmp("--fastopen",key) == 0){ //fastopen | queue_length 
				int queue;
				queue = (int) strtol(value,NULL,10);

				global_server_config.tcp_info->fastopen = 1;
				printf("fastopen set to onn \n");
				if(queue >0 || queue <5){
					global_server_config.tcp_info->queue_length = queue;
					printf("queue length set to %d \n",queue);
				}else{
					global_server_config.tcp_info->queue_length = queue;
					printf("wrong option set to default : 1 \n");
				};
				
        		};

        		if(strcmp("--ttl",key) == 0){ // ttl | tt_hop 
				int hop;
				hop = (int) strtol(value,NULL,10);

				global_server_config.ip_info->ttl = 1;
				global_server_config.ip_info->tt_hop = hop;
				printf("ttl set to onn with hop death at : %d",hop);
			};

        		if(strcmp("--tos",key) == 0){ // tos | tos_value 
				int tos ;
				tos = (int) strtol(value,NULL,10);

				global_server_config.ip_info->tos = 1;
				globale_server_config.ip_info->tos_value = tos;
				printf("tos set to onn at tos value :%d \n",tos_value);
			};


		}else {

			char *value = args[i] + 2

			if(strcmp("--reuseaddr",args[i]) == 0){  //reuseaddr
				if(strcmp("1",value) == 0){
					global_server_config.reuseaddr = 1;
					printf("reuseaddr set open \n");
				}else if(strcmp("0",value) == 0){
					global_server_config.reuseaddr = 0;
					printf("reuseaddr set off \n");
				}else{
					printf("RESUEADDR WRONG OPTION (DEFAULT MODE :off) \n");
				};
			};


			if(strcmp("--mode",args[i]) == 0){
				if(strcmp(value,"select") == 0){
					global_server_config.select_polling = 1;
					printf("select  mode selceted \n");
				}else if(strcmp(value,"fork") == 0){
					global_server_confog.fork_connection = 1;
					printf("fork mode selected \n");
				}else{
					global_server_config.select_polling = 1;
					printf("NO OPTION / WRONG OPTION (DEFAULT : select mode) \n");
				};
			};


			if(strcmp("--sender-buffer",args[i]) == 0){ //send_buff | sender_buffer
				size_t buffer_size;
				buffer_size = (size_t)strtol(value,NULL,10);

				global_server_config.send_buff = 1 ;
				global_server_config.sender_buffer = buffer_size;
				printf("size of the writer buffer file set to : %d " , buffer_size);
			};

         	       	if(strcmp("--reciver-buffer",args[i]) == 0){ //recv_buff | reciver_buffer
				size_t buffer_size;
				buffer_size = (size_t)strtol(value,NULL,10);
				
				global_server_config.recv_buff = 1;
				global_server_config.reciver_buffer = buffer_size ;
				printf("size of the sender buffer set to : %d " , buffer_size);
         		};

         		if(strcmp("--keepalive",args[i]) == 0){  //keepalive
				if(strcmp("1",value) == ){
					global_server_config.keepalive = 1; 
					printf(" keepalive activated \n");
				}else if(strcmp("0",value) == 0){
					global_server_config.keepalive = 0;
					printf(" keepalive deactivated \n");
				}else{
					printf("wrong option keepalive (default : off) \n");
				};
	         	};


         		if(strcmp("--linger",args[i]) == 0){  //linger |  time_linger
				int time_linger ;
				time_linger = (int)strtol(value,NULL,10);

				global_server_config.linger = 1;
				global_server_config.time_linger = time_linger ;
				printf("linger enabled time period: %ld ",time_linger);
         		};

        		if(strcmp("--reader_timeout",args[i]) == 0){ //recvtime | struct timeval reader_timeout
				time_t recvtime ;
				recvtime = (time_t)strtol(value,NULL,10);

				global_server_config.recvtime  = 1 ;
				global_server_config.reader_timeout.tv_sec = recvtime ;
				global_server_config.reader_timeout.tv_usec = 0;
				printf("timeout of reader set to : %ld sec " , recvtime);
        		};

        		if(strcmp("--sender_timeout",args[i]) == 0){ //writetime | struct timeval writer_timeout
				time_t writetime;
				writetime = (time_t) strtol(value,NULL,10);

				global_server_config.writetime = 1;
				global_server_config.writer_timeout.tv_usec = 0;
				global_server_config.writer_timeout.tv_sec = writetime ;
        		};

        		if(strcmp("--non-blocking",args[i]) == 0){ //non-blocking
				if(strcmp("1",value) == 0){
					global_server_config.non_blocking = 1;
					printf("non-blocking set onn \n");
				}else if(strcmp("0",value) == 0){
					global_server_config.non_blocking = 0;
					printf("non-blocking disabled \n");
				}else{
					printf("wrong option set on non-blocking (DEFAULT: OFF) \n");
				};
        		};

        		if(strcmp("--log-socket",args[i]) == 0){ //log-socket
				if(strcmp("1",value) == 0){
					global_server_config.log_socket = 1;
					printf("so error set onn \n");
				}else if(strcmp("0",value)  == 0){
					global_server_config.log_socket = 0;
					printf("so error set off \n");
				}else{
					printf("worng option set on log-socket \n");
				};

        		};

        		/*if(strcmp("--listener",args[i]) == 0){ //listen_socket
				if(strcmp("1",value) == 0){
					global_server_config.listen_socket = 1 ;
					printf("listen socket set to onn \n");
				}else if(strcmp("0",value) == 0){
					global_server_config.listen_socket = 0;
					printf("listen socket set to off \n");
				}else{
					printf("wrong option on listener \n");
				};
        		};*/

        		if(strcmp("--reuseport",args[i]) == 0){ // used_port | recivers
				int reciver ; 
				reciver = (int)strtol(value,NULL,10);

				global_server_config.used_port = 1 ;
				printf("reuseport set to onn \n");
				if(reciver >0 || reciver <5){
					global_server_config.recivers = reciver;
					printf("number of connetion with SO_RESUSEPORT set to %d \n" , reciver);
				}else{
					global_server_config.reciver = 1;
					printf("wrong option on reuseport set to (default_value : 1) \n");
				};
        		};

        		if(strcmp("--idle",args[i]) == 0){ //keepidle | idle 
				int idle_time ;
				idle_time  = (int)strtol(value,NULL,10);

				global_server_config.tcp_info->keepidle = 1;
				global_server_config.tcp_info->idle = idle_time;

				printf("time to check after silence : %d \n",idle_time);
        		};

        		if(strcmp("--interval",args[i]) == 0){ // keepintvl | interval 
				int interval_time ;
				interval_time = (int) strtol(value,NULL,10);

				global_server_config.tcp_info->keepintvl = 1;
				global_server_config.tcp_info->interval = interval_time ;
				printf("interval between check %d",interval_time);
        		};

        		if(strcmp("--count",args[i]) == 0){ // keepcnt | count 
				int count ;
				count = (int) strtol(value,NULL,10);

				global_server_config.tcp_info ->keepcnt = 1;
				global_server_config.tcp_info ->count = count ;
				printf("total check to happen %d \n",count);
        		};

        		if(strcmp("--nodelay",args[i]) == 0){ //nodelay
				if(strcmp("1",value) == 0){
					global_server_config.tcp_info ->nodelay = 1 ;
					printf("nodelay set to onn \n");
				}else if(strcmp("0",value) == 0){
					global_server_config.tcp_info ->nodelay = 0;
					printf("nodelay set to off \n");
				}else {
					printf("worng option set on nodelay (default : 0) \n");
				};
        		};

        		if(strcmp("--info", args[i]) == 0){ //info | tcp_info 
				if(strcmp("1",value) == 0){
					global_server_config.tcp_info ->info = 1;
					printf("info retrival set to onn \n");
				}else if(strcmp("0",value) == 0){
					gloabl_server_config.tcp_info ->info = 0;
					printf("info retrival set to off \n");
				}else {
					global_server_config.tcp_info ->info = 1 ;
					printf("wrong option on info (default : 1) \n");
				};
        		};

        		if(strcmp("--fastopen",args[i]) == 0){ //fastopen | queue_length 
				int queue;
				queue = (int) strtol(value,NULL,10);

				global_server_config.tcp_info ->fastopen = 1;
				printf("fastopen set to onn \n");
				if(queue >0 || queue <5){
					global_server_config.tcp_info ->queue_length = queue;
					printf("queue length set to %d \n",queue);
				}else{
					global_server_config.tcp_info ->queue_length = queue;
					printf("wrong option set to default : 1 \n");
				};
				
        		};

        		if(strcmp("--ttl",args[i]) == 0){ // ttl | tt_hop 
				int hop;
				hop = (int) strtol(value,NULL,10);

				global_server_config.ip_info->ttl = 1;
				global_server_config.ip_info->tt_hop = hop;
				printf("ttl set to onn with hop death at : %d",hop);
			};

        		if(strcmp("--tos",args[i]) == 0){ // tos | tos_value 
				int tos ;
				tos = (int) strtol(value,NULL,10);

				global_server_config.ip_info->tos = 1;
				globale_server_config.ip_info->tos_value = tos;
				printf("tos set to onn at tos value :%d \n",tos_value);
			};


		};
	};
	if(dup2(STDOUT_FILENO , fd_log) <0){
		perror("dup2 changing error \n");
		return -1;
	};

	return 0;
};
