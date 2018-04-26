/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** stor.c
*/

#include <memory.h>
#include "../../include/my_ftp.h"

static const char *LOG_PLS = "Please login with USER and PASS.";

static const char *NO_SOCK = "Use PORT or PASV first.";

int exec_stor(client_data_t *cdata, const char *path)
{
	send_message(cdata->csock, 220, path);
	send_message(cdata->tsock, 220, "STOR OK.");
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
		// Todo : UNLOCK the mutex for the thread.
	}
	else
		send_message(cdata->csock, 530, LOG_PLS);
	return (0);
}