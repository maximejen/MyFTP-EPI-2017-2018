/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** list.c
*/

#include <memory.h>
#include <zconf.h>
#include <sys/stat.h>
#include <stdio.h>
#include <pthread.h>
#include "../../include/my_ftp.h"

static const char *LOG_PLS = "Please login with USER and PASS.";

static const char *NO_SOCK = "Use PORT or PASV first.";

static const char *FAIL = "You cannot list a file.";

static const char *WAIT_LIST = "Here comes the directory listing.";

static const char *SUCCESS = "Directory send OK.";

static int check_path(client_data_t *cdata, const char *path)
{
	struct stat buf;

	if (stat(path, &buf) != -1 && S_ISDIR(buf.st_mode) &&
		strncmp(cdata->home, path, strlen(cdata->home)) == 0) {
		return (1);
	}
	return (0);
}

int exec_list(client_data_t *cdata, char *path)
{
	FILE *f;
	char *cmd = strdup("ls -l");
	char c;

	path = realpath(path, NULL);
	if (check_path(cdata, path) == 1) {
		cmd = str_push(cmd, " ");
		cmd = str_push(cmd, path);
		f = popen(cmd, "r");
		while ((c = (char)getc(f)) > 0)
			write(cdata->tsock, &c, 1);
		pclose(f);
		send_message(cdata->csock, 226, SUCCESS);
	}
	else {
		send_message(cdata->csock, 550, FAIL);
		return (1);
	}
	return (0);
}

int list(struct client_data *cdata, char **cmd)
{
	if (is_auth(cdata)) {
		if (cdata->tsock == 0) {
			send_message(cdata->csock, 425, NO_SOCK);
			return (1);
		}
		cdata->cmd = strdup("LIST");
		cdata->cmd = str_push(cdata->cmd, " ");
		cdata->cmd = str_push(cdata->cmd, cmd[1] ? cmd[1] : ".");
		send_message(cdata->csock, 150, WAIT_LIST);
		pthread_barrier_wait(&cdata->barrier);
	}
	else
		send_message(cdata->csock, 530, LOG_PLS);
	return (0);
}