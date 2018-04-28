/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** retr.c
*/

#include <memory.h>
#include <fcntl.h>
#include <zconf.h>
#include <sys/stat.h>
#include <stdio.h>
#include <pthread.h>
#include "../../include/my_ftp.h"

static const char *LOG_PLS = "Please login with USER and PASS.";

static const char *SUCCESS_CNCT = "ASCII data connection established.";

static const char *FAIL = "Access denied.";

static const char *SUCCESS = "Transfer complete.";

static int check_path(client_data_t *cdata, const char *path)
{
	struct stat buf;

	printf("path : %s\n", path);
	if (stat(path, &buf) != -1 && S_ISREG(buf.st_mode) &&
		!access(path, R_OK) &&
		strncmp(cdata->home, path, strlen(cdata->home)) == 0) {
		return (1);
	}
	return (0);
}

int exec_retr(client_data_t *cdata, char *path)
{
	int fd;
	char buf[1024];
	ssize_t rd = 0;

	path = realpath(path, NULL);
	memset(buf, 0, 1024);
	if (check_path(cdata, path)) {
		fd = open(path, O_RDONLY, 0644);
		while ((rd = read(fd, buf, 1023)))
			write(cdata->tsock, buf, (size_t)rd);
		close(fd);
		send_message(cdata->csock, 226, SUCCESS);
	}
	else {
		send_message(cdata->csock, 550, FAIL);
		return (1);
	}
	return (0);
}

int retr(struct client_data *cdata, char **cmd)
{
	if (is_auth(cdata)) {
		cdata->cmd = strdup("RETR");
		cdata->cmd = str_push(cdata->cmd, " ");
		if (cmd[1])
			cdata->cmd = str_push(cdata->cmd, cmd[1]);
		else
			cdata->cmd = str_push(cdata->cmd, ".");
		send_message(cdata->csock, 150, SUCCESS_CNCT);
		pthread_barrier_wait(&cdata->barrier);
	}
	else
		send_message(cdata->csock, 530, LOG_PLS);
	return (0);
}