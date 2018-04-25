/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** list.c
*/

#include <memory.h>
#include <zconf.h>
#include "../../include/my_ftp.h"

static const char *LOG_PLS = "Please login with USER and PASS.";

int exec_list(client_data_t *cdata, const char *path)
{
	UNUSED(path);
	send_message(cdata->tsock, 220, "LIST OK.");
	// TODO : write in the cdata->tsock the result of the ls in the path.
}

int list(struct client_data *cdata, char **cmd)
{
	if (is_auth(cdata)) {
		cdata->cmd = strdup("LIST");
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