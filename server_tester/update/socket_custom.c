#include <./dbase.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void non_blocking_fn(int fd ,struct sock_info *pointer){
};

void reuseaddr_fn(int fd ,struct sock_info *pointer){
	if(!*pointer->reuseaddr){
		return 0;
	};

	if(setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,pointer->reuseaddr,sizeof(*pointer->reuseaddr)) != 0){
		printf("ERROR IN SETTING THE SOCKET OPTION ON REUSEADDR \n");
		return 0;
	};

	printf("REUSEADDR SET \n");

	return 0;
};

void recv_buffer_fn(int fd ,  struct sock_info *pointer){

	if(!*pointer->recv_buff){
		return 0;
	};

	if(setsockopt(fd,SOL_SOCKET,SO_RCVBUF,pointer->reciver_buffer,sizeof(*pointer->reciver_buffer) ) < 0){
		perror("ERROR IN SETTING THE RECIVE BUFFER \n");
		return 0;
	};

	printf("RECIVER BUFFER SET TO : %ld \n" , *pointer->reciver_buffer);

	return 0;

};

void sender_buffer_fn(int fd , struct sock_info *pointer){

	if(!*pointer->send_buff){
		return 0;
	};

	if(setsockopt(fd,SOL_SOCKET,SO_RCVBUF,pointer->sender_buffer,sizeof(*pointer->sender_buffer) ) < 0){
		perror("ERROR IN SETTING THE RECIVE BUFFER \n");
		return 0;
	};

	printf("RECIVER BUFFER SET TO : %ld \n" , *pointer->sender_buffer);

	return 0;

};

void keepalive_fn(int fd ,  struct sock_info *pointer){

	if(!*pointer->keepalive){
		return 0;
	};

	if(setsockopt(fd,SOL_SOCKET,SO_RCVBUF,pointer->keepalive,sizeof(*keepalive) ) < 0){
		perror("ERROR IN SETTING THE KEEPALIVE \n");
		return 0;
	};

	printf("KEEPALIVE SET \n");
	return 0;

};

void linger_fn(int fd , struct sock_info *pointer){
	if(!*pointer->linger){
		return 0;
	};

	struct linger linger_value ;
	linger_value.l_onoff = *pointer->linger;
	linger_value.l_linger = *pointer->time_linger;

	if(setsockopt(fd,SOL_SOCKET,SO_LINGER,&linger_value,sizeof(linger_value)) <0){
		perror("ERROR IN SETTING THE LINGER TIME \n");
		return 0;
	};

	printf("LINGER TIME SET \n");

	return 0;
};

void recvtime_fn(int fd ,struct sock_info *pointer){
	
	if(*pointer->recvtime){
		return 0;
	};

	if(setsockopt(fd,SOL_SOCKET,pointer->reader_timeout,size(*pointer->reader_timeout)) != 0 ){
		perror("ERROR IN SET THE RECIVER TIMEOUT \n");
		return 0 ;
	};

	printf("RECIVER TIMEOUT SET \n");

	return 0;

};

void writetime_fn(int fd ,struct sock_info *pointer){
	
	if(*pointer->writetime){
		return 0;
	};

	if(setsockopt(fd,SOL_SOCKET,pointer->writer_timeout,size(*pointer->writer_timeout)) != 0 ){
		perror("ERROR IN SET THE WRITER TIMEOUT \n");
		return 0 ;
	};

	printf("WRITER TIMEOUT SET \n");

	return 0;

};

void log_socket_fn(int fd ,struct sock_info *pointer){
	if(!*pointer->log_socket){
		return 0 ; 
	};

	if(setsockopt(fd,SOL_SOCKET,SO_ERROR,pointer->log_socket, sizeof(*pointer->log_socket)) !=0){
		perror("ERROR IN SETTING THE SO_ERROR \n");
		return 0;
	};

	printf("use of so_error set \n");
	return 0;
};

void used_ports_fn(int fd ,struct sock_info *pointer){
	if(*pointer->used_port){
		return 0;
	};

	if(setsockopt(fd,SOL_SOCKET,SO_REUSEPORT,pointer->recivers,sizeof(*pointer->recivers)) != 0){
		perror("ERROR IN SETTING THE REUSEPORT \n");
		return 0;
	};

	printf("REUSEPORT SET \n");
	return 0;
};

void nodelayer_fn(int fd ,struct sock_info *pointer){
	if(!*pointer->tcp_info->nodelay){
		return 0;
	};

	if(setsockopt(fd,IPPROTO_TCP,TCP_NODELAY,pointer->tcp_info->nodelay,sizeof(*pointer->tcp_info->nodelay)) != 0){
		perror("ERROR IN SETTING THE NODELAYER \n");
		return 0;
	};
	
	printf("NODELAY SET \n");
	return 0;

};

void keepidle_fn(int fd ,struct sock_info *pointer){
	if(!*pointer->tcp_info->keepidle){
		return 0;
	};

	if(setsockopt(fd,IPPROTO_TCP,TCP_KEEPIDLE,pointer->tcp_info->idle,sizeof(*pointer->tcp_info->idle)) != 0){
		perror("ERROR IN SETTING THE IDLE TIME \n");
		return 0 ;
	};

	printf("IDLE TIME SET \n");
	return 0;
};

void keepinterval_fn(int fd ,struct sock_info *pointer){
	if(!*pointer->tcp_info->keepintvl){
		return 0;
	};

	if(setsockopt(fd,IPPROTO_TCP,TCP_KEEPINTVL,pointer->tcp_info->interval,sizeof(*pointer->tcp_info->interval)) != 0){
		perror("ERROR IN SETTING THE INTERVAL TIME \n");
		return 0 ;
	};

	printf("INTERVAL TIME SET \n");
	return 0;
};

void keepcnt_fn(int fd ,struct sock_info *pointer){
	if(!*pointer->tcp_info->keepcnt){
		return 0;
	};

	if(setsockopt(fd,IPPROTO_TCP,TCP_KEEPCNT,pointer->tcp_info->count,sizeof(*pointer->tcp_info->count)) != 0){
		perror("ERROR IN SETTING THE COUNT TIME \n");
		return 0 ;
	};

	printf("COUNT TIME SET \n");
	return 0;
};

void fastopen_fn(int fd ,struct sock_info *pointer){
	if(!*pointer->tcp_info->fastopen){
		return 0;
	};

	if(setsockopt(fd,IPPROTO_TCP,TCP_FASTOPEN,pointer->tcp_info->queue,sizeof(*pointer->tcp_info->queue)) != 0){
		perror("ERROR IN SETTING THE FAST OPEN \n");
		return 0 ;
	};

	printf("FASTOPEN SET \n");
	return 0;
};

void ttl_layer(int fd ,struct sock_info *pointer ){
	if(!*pointer->ip_info->ttl){
		return 0;
	}

	if(setsockopt(fd,IPPROTO_IP,IP_TTL,pointer->ip_info->tt_hop,sizeof(*pointer->ip_info->ttl)) != 0){
		perror("ERROR IN SETTING THE TTL HOPS \n");
		return 0;
	};

	printf("TTL SET \n");
	return 0;
};

void tos_layer(int fd ,struct sock_info *pointer){
	if(!*pointer->ip_info->tos){
		return 0;
	}

	if(setsockopt(fd,IPPROTO_IP,IP_TOS,pointer->ip_info->tos_value,sizeof(*pointer->ip_info->tos_value)) != 0){
		perror("ERROR IN SETTING THE TOS \n");
		return 0;
	};

	printf("TOS SET \n");
	return 0;
};

typedef void (*optimizer)(int fd ,struct sock_info *pointer);

typedef struct{
	char option_name[30]; ; 
	optimizer fn;
}option_entry;

option_entry opt_table[] = {
	{"NON_BLOCKING" , non_blocking_fn},
	{"SO_REUSEADDR" , reuseaddr_fn},
	{"SO_RCVBUF" , recv_buff_fn},
	{"SO_SNDBUF" , send_buff_fn},
	{"SO_KEEPALIVE" , keepalive_fn},
	{"SO_LINGER" , linger_fn},
	{"SO_RECVTIMEO" , recvtime_fn},
	{"SO_SNDTIMEO" , wrtietime_fn},
	{"SO_ERROR" , log_socket_fn},
	{"SO_REUSEPORT", used_ports_fn},
	{"TCP_NODELAY" , nodelayer_fn},
	{"TCP_KEEPIDLE" , keepidle_fn},
	{"TCP_KEEPINTVL", keepinterval_fn},
	{"TCP_KEEPCNT" , keepcnt_fn},
	{"TCP_FASTOPEN" , fastopen_fn},
	{"IP_TTL" , ttl_layer},
	{"IP_TOS" , tos_layer},
};

int socket_optimizer(int fd ,int checker ){
	printf("optimizing the socket according the commands passed \n");
	int count;
	count  =  sizeof(opt_table) / sizeof(opt_table[0]) ;

	if(checker == 1){
		printf("server cofig \n");
		struct sock_info *pointer = &global_server_config
	}else{
		printf("client config \n");
		struct sock_info *pointer;
		pointer = connection_getter(checker);
		if(!res){
			printf("ERROR IN GETTING THE CONNECTION DETAIL\n");
			return -1;
		};
	};

	for(int i = 0 ;  i <= count ; i++){
		opt_table[i].fn(fd,pointer);
	};

	printf("OPERATION COMPLETED \n");

	return 0;
};
