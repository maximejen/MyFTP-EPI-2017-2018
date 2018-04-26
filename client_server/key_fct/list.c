/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** list.c
*/

#include <memory.h>
#include <zconf.h>
#include <sys/stat.h>
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

int exec_list(client_data_t *cdata, const char *path)
{
	send_message(cdata->csock, 220, path);
	if (check_path(cdata, path) == 1) {
		send_message(cdata->tsock, 220, SUCCESS);
		// TODO : write in the cdata->tsock the result of the ls in the path.
	}
	else
		send_message(cdata->csock, 550, FAIL);
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
		if (cmd[1])
			cdata->cmd = str_push(cdata->cmd, cmd[1]);
		else
			cdata->cmd = str_push(cdata->cmd, ".");
		send_message(cdata->csock, 150, WAIT_LIST);
		// Todo : UNLOCK the mutex for the thread. IF I DO MUTEX
	}
	else
		send_message(cdata->csock, 530, LOG_PLS);
	return (0);
}