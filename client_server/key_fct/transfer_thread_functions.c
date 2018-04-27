/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** transfer_thread_functions.c
*/

#include <zconf.h>
#include <netinet/in.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "../../include/my_ftp.h"

static const char *SCS = "227 Entering Passive Mode";

static const char *KEYS[4] = {
	"LIST",
	"RETR",
	"STOR",
	NULL
};

int parse_cmd(client_data_t *cdata)
{
	char **tab = custom_split(cdata->cmd, ' ');
	int i;
	char *path = strdup(cdata->home);
	int (*ptr[3])(client_data_t *, char *) =
		{exec_list, exec_retr, exec_stor};
	int ret = 0;

	if (!tab)
		return (1);
	tab[0] = strtoupper(tab[0]);
	for (i = 0 ; KEYS[i] && strcmp(KEYS[i], tab[0]) != 0 ; i++);
	if (path[strlen(path) - 1] != '/')
		path = str_push(path, "/");
	path = str_push(path, strcmp(tab[1], ".") != 0 ? tab[1] : cdata->pwd);
	ret = ptr[i](cdata, path);
	free(path);
	free_wordtab(tab);
	return (ret);
}

static void define_ip_and_port(char **ip, int *port, int sock)
{
	port[0] = rand_nbr(256);
	port[1] = rand_nbr(256);
	port[2] = port[0] * 256 + port[1];
	*ip = get_socket_ip(sock);
	printf("port : %d\n", port[2]);
	*ip = str_replace(*ip, ".", ",");
}

static char *finish_socket_usage(client_data_t *cdata)
{
	free(cdata->cmd);
	cdata->cmd = NULL;
	close(cdata->tsock);
	cdata->tsock = 0;
	return ("OK");
}

void *start_pasv_thread(void *arg)
{
	int p[3];
	struct sockaddr_in sc;
	socklen_t ss = sizeof(sc);
	client_data_t *cdata = arg;
	char *ip;

	if (cdata->tsock != 0) {
		close(cdata->tsock);
		cdata->tsock = 0;
	}
	define_ip_and_port(&ip, p, cdata->csock);
	cdata->tsock = create_socket(p[2], "TCP");
	dprintf(cdata->csock, "%s (%s,%d,%d).%s", SCS, ip, p[0], p[1], CLRF);
	if (listen(cdata->tsock, p[2]) == -1)
		return ("KO");
	cdata->tsock = accept(cdata->tsock, (struct sockaddr *)&sc, &ss);
	while (cdata->cmd == NULL);
	return (parse_cmd(cdata) != 1 ? finish_socket_usage(cdata) : "KO");
}