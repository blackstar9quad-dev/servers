#ifndef MY_NETWORK_H
#define MY_NETWORK_H

#include <netdb.h>
#include <sys.types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/tcp.h>



struct client_connection{
	char *connectionid ;
	int client_sock;
	char *server_ip;
	char *client_ip;
	struct addrinfo *client_addrinfo;
	struct addrinfo *server_addinfo;
	struct sock_info *client_sock_info;
	char *customs[] ;
	char *optval_client[];
	struct db *db_next;
};

struct server_sock_info{ //socket level 
	struct tcp_infos *tcp_info ;
	struct ip_info   *ip_info ;
	unsigned int mode            : 1;
	unsigned int non_blocking    : 1; // --non-blcking fcntl logic 
        unsigned int reuseaddr       : 1; // Allow binding to a port in before the TIME_WAIT:1m to 4m
	unsigned int recv_buff       : 1; // SO_RCVBUF
	size_t reciver_buffer;
	unsigned int send_buff       : 1; // SO_SNDBUF
	size_t sender_buffer;
	unsigned int keepalive       : 1;   // SO_KEEPALIVE 
	unsigned int linger          : 1;   // struct linger  SO_LINGER
	int time_linger ;
	unsigned int recvtime        : 1;   // SO_RCVTIMEO bit
	struct timeval reader_timeout;            // struct timeval SO_RCVTIMEO
	unsigned int writetime       : 1;   // SO_SNDTIMEO
	struct timeval writer_timeout;            // struct timeval SO_SNDTIMEO
	unsigned int metrics         : 1;
	unsigned int log_socket      : 1;   // SO_ERROR 
	unsigned int listen_socket   : 1;   // check if the socket is listen or not SO_ACCEPTCONN
	unsigned int used_port       : 1;   //multiple socket can bin to the same port SO_REUSEPORT
	int recivers;                       // SO_REUSEPORT 
};

struct sock_info{ //socket level 
	struct tcp_infos *tcp_info ;
	struct ip_info   *ip_info  ;
	unsigned int mode            : 1;
	unsigned int non_blocking    : 1; // --non-blcking fcntl logic 
        unsigned int reuseaddr       : 1; // Allow binding to a port in before the TIME_WAIT:1m to 4m
	unsigned int recv_buff       : 1; // SO_RCVBUF
	size_t reciver_buffer;
	unsigned int send_buff       : 1; // SO_SNDBUF
	size_t sender_buffer;
	unsigned int keepalive       : 1;   // SO_KEEPALIVE 
	unsigned int linger          : 1;   // struct linger  SO_LINGER
	int time_linger ;
	unsigned int recvtime        : 1;   // SO_RCVTIMEO bit
	struct timeval reader_timeout;            // struct timeval SO_RCVTIMEO
	unsigned int writetime       : 1;   // SO_SNDTIMEO
	struct timeval writer_timeout;            // struct timeval SO_SNDTIMEO
	unsigned int metrics         : 1;
	unsigned int log_socket      : 1;   // SO_ERROR 
	unsigned int listen_socket   : 1;   // check if the socket is listen or not SO_ACCEPTCONN
	unsigned int used_port       : 1;   //multiple socket can bin to the same port SO_REUSEPORT
	int recivers;                       // SO_REUSEPORT 
};

struct tcp_infos{  //tcp level 
	unsigned int nodelay         : 1; // TCP_NODELAY disbale/enable nagle algo

	unsigned int info            : 1; // TCP_INFO 
	struct tcp_info tcp_info;         // TCP_INFO info container 


//--------------------------------------------------------------------------------------------------//
                            //SO_KEEPALIVE subsection 	
	unsigned int keepidle        : 1;  // TCP_KEEPIDLE  bit
	int idle;     // TCP_KEEPIDLE time to start the check after silence 
	unsigned int keepintvl       : 1;  // TCP_KEEPINTVL bit 
	int interval; // TCP_KEEPINTVL interval per cheack
	unsigned int keepcnt         : 1;  // TCP_kEEPCNT bit 
	int count;    // TCP_KEEPCNT how many checks before shutting down 
//--------------------------------------------------------------------------------------------------//
  
//--------------------------------------------------------------------------------------------------//
                           //SO_REUSEADDR subsection 
	unsigned int fastopen	     : 1; // TCP_FASTOPEN
	int queue_length;                 // upto 4 , establish the number of connection that use this
//--------------------------------------------------------------------------------------------------//
};

struct ip_info{

	unsigned int ttl             : 1; //IP_TTL 
	int tt_hop;                       //amount of hop  the packet data from this socket can make

	unsigned int tos             ; 1; //IP_TOS 
	int tos_value;
};

struct client_connection global_client_table[20];
struct server_sock_info  global_server_config ;
#endif
