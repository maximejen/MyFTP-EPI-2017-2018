/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** port.c
*/

#include <zconf.h>
#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <memory.h>
#include "../../include/my_ftp.h"

static const char *LOG_PLS = "Please login with USER and PASS.";

static int connect_to(client_data_t *cdata, char *ip, int port)
{
	struct protoent *pe;
	struct sockaddr_in s_in;

	if (!(pe = getprotobyname("TCP")))
		return (1);
	cdata->tsock = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (cdata->tsock == INVALID_SOCKET)
		return (-1 + 0 * close(cdata->tsock));
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons((uint16_t)port);
	s_in.sin_addr.s_addr = inet_addr(ip);
	connect(cdata->tsock, (const struct sockaddr *)&s_in, sizeof(s_in));
	return (0);
}

static void *start_port_thread(void *arg)
{
	client_data_t *cdata = arg;
	char **tab = custom_split(cdata->cmd, '-');

	cdata->cmd = NULL;
	if (cdata->tsock != 0) {
		close(cdata->tsock);
		cdata->tsock = 0;
	}
	printf("ip : %s\n", tab[0]);
	printf("port : %d\n", atoi(tab[1]));
	connect_to(cdata, tab[0], atoi(tab[1]));
	free_wordtab(tab);
	return ("OK");
}

int port(struct client_data *cdata, char **cmd)
{
	pthread_t thread;

	UNUSED(cmd);
	if (is_auth(cdata)) {
		cdata->cmd = strdup(cmd[1]);
		if (pthread_create(&thread, NULL, start_port_thread,
			cdata) != 0)
			return (1);
	} else
		send_message(cdata->csock, 530, LOG_PLS);
	return (0);
}