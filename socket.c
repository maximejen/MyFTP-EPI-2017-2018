/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** socket.c
*/

#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <zconf.h>
#include "include/my_ftp.h"

int create_socket(int port, const char *protocol)
{
	struct protoent *pe;
	t_socket sock;
	struct sockaddr_in s_in;

	if (!(pe = getprotobyname(protocol)))
		return (1);
	sock = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (sock == INVALID_SOCKET) {
		close(sock);
		fprintf(stderr, "An error occured with create_socket.\n");
		return (-1);
	}
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons((uint16_t)port);
	s_in.sin_addr.s_addr = INADDR_ANY;
	if (bind(sock, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1) {
		close(sock);
		return (-1);
	}
	return (sock);
}