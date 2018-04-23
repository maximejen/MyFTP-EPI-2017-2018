/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** main_server.c
*/

#include <sys/socket.h>
#include <zconf.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include "../include/my_ftp.h"

int CONTINUE = 1;

void sigint(int sig)
{
	(void)sig;
	CONTINUE = 0;
	exit(0);
}

static void close_sockets(csd_t *data)
{
	close(data->csock);
	close(data->client_sock);
}

/*
** This funtion will wait a client to connect and then will fork the program
** to handle the client requests
*/
int wait_for_connections(csd_t *data)
{
	struct sockaddr_in sinclient;
	socklen_t sinsize = sizeof(sinclient);
	pid_t pid = -1;

	if ((data->csock = create_socket(data->args.port, "TCP")) == -1)
		return (84);
	while (pid != 0 && CONTINUE) {
		if (listen(data->csock, data->args.port) == -1)
			return (84);
		data->client_sock = accept(data->csock,
			(struct sockaddr *)&sinclient, &sinsize);
		if ((pid = fork()) == -1 || data->client_sock == -1)
			return (84);
		if (pid != 0)
			close(data->client_sock);
	}
	if (pid == 0)
		return (handle_client(data));
	close_sockets(data);
	return (0);
}