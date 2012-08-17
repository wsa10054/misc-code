
#include "end_point.h"
#include "endian.h"
#include "tcp_socket.h"
#include "signal_act.h"
#include "timestamp.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h> //fork

#include <errno.h>
#include <string.h>
#include <iostream>
#include <string>




void	send_close(int conn_fd,const net::EndPointV4& peer);

void	sig_child(int signo);
int main(int argc, char **argv)
{
	std::string	ip_str="192.168.0.1";
	uint16_t	port=5001;
	net::EndPointV4 addr_srv(port);
	net::EndPointV4 peer;
	::printf("is_big_endianess ? %s\n",(net::is_big_endianess()?"true": "false"));
	
	::printf("listen port:%d\n",  addr_srv.GetPort());
	int client_fd=-1;
	int listen_fd= net::tcp_socket_create();
	if(-1 == listen_fd){
		::perror(NULL);
	}
	if(-1 == net::tcp_socket_bind(listen_fd,addr_srv)){
		::perror(NULL);
	}
	if(-1 == ::listen(listen_fd,5)){
		::perror(NULL);
	}
	//sig_callback old=NULL;
	base::set_sig_func(SIGCHLD,sig_child);
	while(true){
		client_fd = net::tcp_socket_accept(listen_fd,peer);
		if(-1 == client_fd){
			if(errno == EINTR ){
				::printf("accept interrupt\n");
			}else{
				//::printf("accept ERROR :[%d] %s ",errno,"");
				::perror("accept ERROR  ");
			}
		}else{
			pid_t id = fork();
			if(id == 0 ){
				send_close(client_fd,peer);
				return 0;
			}else{
				close(client_fd);
			}
		}
	}
	
	return 0;
}

void	send_close(int conn_fd,const net::EndPointV4& peer)
{
	std::string now= base::Timestamp::now().toFormattedString();
	::printf("[%s]client connect %s:%d\n",now.c_str(), peer.GetIP().c_str(), peer.GetPort());
	now+="\n";
	::write(conn_fd,now.c_str(),now.length());
	net::shutdown_w(conn_fd);
	do{
		char read_buff[512]={0};
		size_t read_len= ::read(conn_fd,read_buff,sizeof(read_buff)-1);
		if(read_len > 0){
			::printf("recv : %s\n",read_buff);
		}else if(read_len == 0){
			::printf("peer disconnected\n");
			break;
		}else{
			::perror("read ERROR  ");
			break;
		}
	}while(true );
	close(conn_fd);
}

void	sig_child(int signo)
{
	std::string now= base::Timestamp::now().toFormattedString();
	pid_t id;
	int stat;
	::printf("[%s]%s\n",now.c_str(),::strsignal(signo));
	if( (id = ::waitpid(-1,&stat,WNOHANG)) > 0 ){
		::printf("[%s]child process exit:%d\n",now.c_str(),(int)id);
	}
}

