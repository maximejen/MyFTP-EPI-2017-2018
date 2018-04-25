/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** retr.c
*/

#include <memory.h>
#include "../../include/my_ftp.h"

static const char *LOG_PLS = "Please login with USER and PASS.";

int exec_retr(client_data_t *cdata, const char *path)
{
	UNUSED(path);
	send_message(cdata->tsock, 220, "RETR OK.");
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
		// Todo : UNLOCK the mutex for the thread.
	}
	else
		send_message(cdata->csock, 530, LOG_PLS);
}