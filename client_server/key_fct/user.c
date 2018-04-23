/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** user.c
*/

#include <memory.h>
#include <stdlib.h>
#include "../../include/my_ftp.h"

static const char *PASS_MSG = "Please specify the password.";
static const char *ALRD_LOGGED = "Can't change from guest user.";

int user(struct client_data *cdata, char **cmd)
{
	if (cdata->auth == 1) {
		send_message(cdata->csock, 530, ALRD_LOGGED);
		return (0);
	}
	if (cmd[1] == NULL)
		send_message(cdata->csock, 530, "Permission denied.");
	else {
		free(cdata->user);
		cdata->user = strdup(cmd[1]);
		send_message(cdata->csock, 331, PASS_MSG);
	}
	return (0);
}