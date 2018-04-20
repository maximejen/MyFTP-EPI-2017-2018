/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** my_ftp.h
*/

#ifndef MY_FTP_MY_FTP_H
	#define MY_FTP_MY_FTP_H

	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1
	#define ERROR -1

typedef int t_socket;

typedef struct args_s {
	int port;
	char *path;
} args_t;

typedef struct connect_server_data {
	args_t args;
	t_socket csock;
	t_socket client_sock;
} csd_t;

/*
** main_server.c
*/
int wait_for_connections(csd_t *data);

/*
** socket.c
*/
int create_socket(int, const char *);


#endif //MY_FTP_MY_FTP_H
