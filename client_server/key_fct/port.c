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

static const char *FAIL = "Invalid PORT command.";

int asprintf(char **strp, const char *fmt, ...);

static int connect_to(client_data_t *cd, char **t)
{
	struct protoent *pe;
	struct sockaddr_in s;
	char *ip;
	int port[3];

	asprintf(&ip, "%s.%s.%s.%s", t[0], t[1], t[2], t[3]);
	port[0] = atoi(t[4]);
	port[1] = atoi(t[5]);
	port[2] = port[0] * 256 + port[1];
	if (!(pe = getprotobyname("TCP")))
		return (1);
	cd->tsock = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (cd->tsock == INVALID_SOCKET)
		return (-1 + 0 * close(cd->tsock));
	s.sin_family = AF_INET;
	s.sin_port = htons((uint16_t)port[2]);
	s.sin_addr.s_addr = inet_addr(ip);
	if (connect(cd->tsock, (const struct sockaddr *)&s, sizeof(s)) == -1)
		return (1);
	dprintf(cd->csock, "200 Connection to %s:%d%s", ip, port[2], CLRF);
	return (0);
}

static void *finish_socket_usage(client_data_t *cdata, char **tab)
{
	free(cdata->cmd);
	cdata->cmd = NULL;
	close(cdata->tsock);
	cdata->tsock = 0;
	free_wordtab(tab);
	return ("OK");
}

static void *start_port_thread(void *arg)
{
	client_data_t *cd = arg;
	char **tab = custom_split(cd->cmd, ',');
	int size = 0;

	cd->cmd = NULL;
	if (cd->tsock != 0) {
		close(cd->tsock);
		cd->tsock = 0;
	}
	for (size = 0 ; tab[size] ; size++);
	if (size < 6 || connect_to(cd, tab) == 1) {
		free_wordtab(tab);
		send_message(cd->csock, 550, FAIL);
		return ("KO");
	}
	pthread_barrier_wait(&cd->barrier);
	return (parse_cmd(cd) != 1 ? finish_socket_usage(cd, tab) : "KO");
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