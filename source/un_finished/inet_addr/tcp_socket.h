#ifndef MURADIN_NET_TCP_SOCKET_H_
#define MURADIN_NET_TCP_SOCKET_H_


namespace net{
	
	class EndPointV4;
	
	//创建一个非阻塞套接字并带有FD_CLOEXEC选项
	int		tcp_nbsocket_create();
	
	//创建一个阻塞套接字并带有FD_CLOEXEC选项
	int		tcp_socket_create();
	
	int		tcp_socket_bind(int fd,const EndPointV4& endpoint);
	
	int		tcp_socket_accept(int listen_fd, EndPointV4& peer);
		
	//设置非阻塞
	void	set_nonblock(int fd);
	//设置FD_CLOEXEC
	void	set_close_on_exec(int fd);
	
	// 关闭读端,所有套接字读缓冲区中残留的数据将被丢弃
	int		shutdown_r(int fd);
	// 关闭写端,所有套接字写缓冲区中残留的数据将被发送,并且附带一个FIN分节
	int		shutdown_w(int fd);
	// 等同于先调用shutdown_r,然后调用shutdown_w
	int		shutdown_rw(int fd);
	
};//net
#endif//MURADIN_NET_TCP_SOCKET_H_