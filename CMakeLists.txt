project(my_ftp)

set(sources main.c include/my_ftp.h main_server.c socket.c)

add_executable(my_ftp ${sources})