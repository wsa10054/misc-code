project(socket_misc)

add_executable(socket_misc endian.cc main.cpp end_point.cc socket_addr.cc tcp_socket.cc)
add_executable(timesrv1 time_server1.cc endian.cc  end_point.cc socket_addr.cc tcp_socket.cc timestamp.cc signal_act.cc)