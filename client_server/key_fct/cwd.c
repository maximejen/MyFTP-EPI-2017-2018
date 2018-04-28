/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** cwd.c
*/

#include <stddef.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "../../include/my_ftp.h"

static const char *LOG_PLS = "Please login with USER and PASS.";

static const char *SUCCESS = "Directory successfully changed.";

static const char *FAIL = "Failed to change directory.";

static int check_path(client_data_t *cdata, char **path)
{
	struct stat buf;
	size_t size = strlen(*path);

	if (stat(*path, &buf) != -1 && S_ISDIR(buf.st_mode) &&
		strncmp(cdata->home, *path, strlen(cdata->home)) == 0) {
		free(cdata->pwd);
		if ((*path)[size - 1] != '/')
			str_push(*path, "/");
		cdata->pwd = strdup(*path + strlen(cdata->home));
		if (strcmp(cdata->pwd, "") == 0)
			str_push(cdata->pwd, "/");
	} else {
		send_message(cdata->csock, 550, FAIL);
		return (1);
	}
	return (0);
}

int cwd(struct client_data *cdata, char **cmd)
{
	char *path = strdup(cdata->home);

	if (is_auth(cdata)) {
		if (cmd[1] == NULL || cmd[2] != NULL) {
			free(path);
			return (1 + send_message(cdata->csock, 550, FAIL));
		}
		path = str_push(path, cdata->pwd);
		path = str_push(path, cmd[1]);
		path = realpath(path, NULL);
		if (!path) {
			free(path);
			return (1 + send_message(cdata->csock, 550, FAIL));
		} else if (check_path(cdata, &path) == 0)
			send_message(cdata->csock, 250, SUCCESS);
		free(path);
	} else
		send_message(cdata->csock, 530, LOG_PLS);
	return (0);
}