/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** client_server.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <zconf.h>
#include <pthread.h>
#include "../include/my_ftp.h"

static void fill_function_ptr(client_data_t *cdata)
{
	cdata->fctptr[0] = cdup;
	cdata->fctptr[1] = cwd;
	cdata->fctptr[2] = dele;
	cdata->fctptr[3] = help;
	cdata->fctptr[4] = list;
	cdata->fctptr[5] = noop;
	cdata->fctptr[6] = pass;
	cdata->fctptr[7] = pasv;
	cdata->fctptr[8] = port;
	cdata->fctptr[9] = pwd;
	cdata->fctptr[10] = quit;
	cdata->fctptr[11] = retr;
	cdata->fctptr[12] = stor;
	cdata->fctptr[13] = user;
	cdata->fctptr[14] = unknown;
}

int is_auth(client_data_t *cdata)
{
	return cdata->auth;
}

/*
** This function will get the user commands and then exec them to answer.
*/
int handle_client(csd_t *data)
{
	client_data_t cdata = {data->client_sock, NULL, 0, strdup("/"),
		strdup(data->args.path), {NULL}, "", 1, 0, NULL, {{0}}};

	pthread_barrier_init(&cdata.barrier, NULL, 2);
	fill_function_ptr(&cdata);
	memset(cdata.buffer, 0, BUFFER_SIZE);
	send_message(cdata.csock, 220, "You are correctly connected");
	while (cdata.ctn) {
		if (get_instruction(&cdata) == -1)
			return (-1);
		interpret_instruction(&cdata);
		memset(cdata.buffer, 0, BUFFER_SIZE);
	}
	close(cdata.csock);
	free(cdata.pwd);
	pthread_barrier_destroy(&cdata.barrier);
	return (0);
}