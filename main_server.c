/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** main_server.c
*/

#include <sys/socket.h>
#include <zconf.h>
#include <netinet/in.h>
#include "include/my_ftp.h"

int wait_for_connections(csd_t *data)
{
	struct sockaddr_in sinclient;
	socklen_t sinsize = sizeof(sinclient);
	pid_t pid;

	if ((data->csock = create_socket(data->args.port, "TCP")) == -1)
		return (84);
	while (1) {
		data->client_sock = accept(data->csock,
			(struct sockaddr *)&sinclient, &sinsize);
		if ((pid = fork()) == -1)
			return (84);
		if (pid == 0) {
			// FILS
			// Todo : Va s'occuper de récupérer les commandes du client.
		} else
			close(data->client_sock);
	}
	return (0);
}