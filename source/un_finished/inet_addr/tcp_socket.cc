#include "tcp_socket.h"
#include <assert.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include "end_point.h"

namespace net{
	int		tcp_socket_create()
	{
		return ::socket(AF_INET,SOCK_STREAM | SOCK_CLOEXEC ,0);
	}
	
	int		tcp_nbsocket_create()
	{
		return ::socket(AF_INET,SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC,0);
	}
	
	int		tcp_socket_bind(int fd,const EndPointV4& endpoint)
	{
		return ::bind(fd,(const struct sockaddr *)&endpoint.Address(),sizeof(struct sockaddr));
	}
	int		tcp_socket_accept(int listen_fd, EndPointV4& peer)
	{
		net::SockecAddressV4 add_buf;
		socklen_t  len=sizeof(net::SockecAddressV4);
		int ret= ::accept(listen_fd,(struct sockaddr*)&add_buf,&len);
		assert(sizeof(SockecAddressV4) >= len);
		if(ret != -1){
			peer = add_buf;
			//peer = net::EndPointV4( add_buf );
		}
		return ret;
	}
	
	void	set_nonblock(int fd)
	{
		int flags = ::fcntl(fd, F_GETFL, 0);
		flags |= O_NONBLOCK;
		int ret = ::fcntl(fd, F_SETFL, flags);
		// FIXME check
		(void)ret;
	}
	
	void	set_close_on_exec(int fd)
	{
		int flags = ::fcntl(fd, F_GETFD, 0);
		flags |= FD_CLOEXEC;
		int ret  = ::fcntl(fd, F_SETFD, flags);
		// FIXME check
		(void)ret;
	}

	int	shutdown_r(int fd)
	{
		return ::shutdown(fd,SHUT_RD);
	}
	int	shutdown_w(int fd)
	{
		return ::shutdown(fd,SHUT_WR);
	}
	int	shutdown_rw(int fd)
	{
		return ::shutdown(fd,SHUT_RDWR);
	}
	
};//net