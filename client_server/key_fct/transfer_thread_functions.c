/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** transfer_thread_functions.c
*/

#include <zconf.h>
#include <netinet/in.h>
#include <stdio.h>
#include "../../include/my_ftp.h"

static const char *SUCCESS = "227 Entering Passive Mode";

static const char *KEYS[5] = {
	"LIST",
	"RETR",
	"STOR",
	NULL
};


void *start_thread(void *arg)
{
	int o;
	int t;
	int port;
	struct sockaddr_in sc;
	socklen_t ss = sizeof(sc);
	client_data_t *cdata = arg;
	char *ip;

	if (cdata->tsock != 0) {
		close(cdata->tsock);
		cdata->tsock = 0;
	}
	o = rand_nbr(256);
	t = rand_nbr(256);
	port = o * 256 + t;
	cdata->tsock = create_socket(port, "TCP");
	ip = get_socket_ip(cdata->csock);
	printf("port : %d\n", port);
	ip = str_replace(ip, ".", ",");
	dprintf(cdata->csock, "%s (%s,%d,%d).%s", SUCCESS, ip, o, t, CLRF);
	if (listen(cdata->tsock, port) == -1)
		return ("KO");
	cdata->tsock = accept(cdata->tsock, (struct sockaddr *)&sc, &ss);
	while (cdata->cmd == NULL);
	// Todo : Parse the command, and get the path given in arg, for all the cases. for LIST, just use the pwd.
	// Todo : Exec the command in the cdata struct.
	return ("OK");
}