/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** stor.c
*/

#include <memory.h>
#include <sys/stat.h>
#include <zconf.h>
#include <fcntl.h>
#include <stdio.h>
#include <pthread.h>
#include "../../include/my_ftp.h"

static const char *LOG_PLS = "Please login with USER and PASS.";

static const char *NO_SOCK = "Use PORT or PASV first.";

static const char *FAIL = "Access denied.";

static const char *SUCCESS = "Transfer complete.";

static const char *SUCCESS_CNCT = "ASCII data connection established.";

static int check_path(client_data_t *cdata, const char *path)
{
	if (strncmp(cdata->home, path, strlen(cdata->home)) == 0)
		return (1);
	return (0);
}

int exec_stor(client_data_t *cdata, char *path)
{
	int fd;
	char buf[1024];
	ssize_t rd = 0;

	memset(buf, 0, 1024);
	if (check_path(cdata, path)) {
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		while ((rd = read(cdata->tsock, buf, 1023)))
			write(fd, buf, (size_t)rd);
		close(fd);
		send_message(cdata->csock, 226, SUCCESS);
	}
	else {
		send_message(cdata->csock, 550, FAIL);
		return (1);
	}
	return (0);
}

int stor(struct client_data *cdata, char **cmd)
{
	if (is_auth(cdata)) {
		if (cdata->tsock == 0) {
			send_message(cdata->csock, 425, NO_SOCK);
			return (1);
		}
		cdata->cmd = strdup("STOR");
		cdata->cmd = str_push(cdata->cmd, " ");
		if (cmd[1])
			cdata->cmd = str_push(cdata->cmd, cmd[1]);
		else
			cdata->cmd = str_push(cdata->cmd, ".");
		send_message(cdata->csock, 150, SUCCESS_CNCT);
		pthread_barrier_wait(&cdata->barrier);
	} else
		send_message(cdata->csock, 530, LOG_PLS);
	return (0);
}