/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** dele.c
*/

#include <memory.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <zconf.h>
#include <stdio.h>
#include "../../include/my_ftp.h"

static const char *LOG_PLS = "Please login with USER and PASS.";

static const char *SUCCESS = "Delete operation successful.";

static const char *FAIL = "Delete operation failed.";

static int check_path(client_data_t *cdata, char **path)
{
	struct stat buf;

	if (stat(*path, &buf) != -1 && S_ISREG(buf.st_mode) &&
		strncmp(cdata->home, *path, strlen(cdata->home)) == 0) {
		printf("try to delete : %s\n", *path);
		if (unlink(*path) == -1)
			send_message(cdata->csock, 550, FAIL);
	} else {
		send_message(cdata->csock, 550, FAIL);
		return (1);
	}
	return (0);
}

int dele(struct client_data *cdata, char **cmd)
{
	char *path = strdup(cdata->home);

	if (is_auth(cdata)) {
		if (cmd[1] == NULL || cmd[2] != NULL) {
			free(path);
			send_message(cdata->csock, 550, FAIL);
			return (1);
		}
		path = str_push(path, cdata->pwd);
		path = str_push(path, cmd[1]);
		path = realpath(path, NULL);
		if (!path) {
			free(path);
			send_message(cdata->csock, 550, FAIL);
			return (1);
		}
		if (check_path(cdata, &path) == 0)
			send_message(cdata->csock, 250, SUCCESS);
		free(path);
	} else
		send_message(cdata->csock, 530, LOG_PLS);
	return (0);
}