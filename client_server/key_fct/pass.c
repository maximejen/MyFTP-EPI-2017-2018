/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** pass.c
*/

#include <memory.h>
#include <stdlib.h>
#include "../../include/my_ftp.h"

static const char *ALRD_LOGGED = "Already logged in.";

int pass(struct client_data *cdata, char **cmd)
{
	UNUSED(cmd);
	if (cdata->auth == 1) {
		send_message(cdata->csock, 230, ALRD_LOGGED);
		return (0);
	}
	if (cdata->user == NULL)
		send_message(cdata->csock, 503, "Login with USER first.");
	else if (cdata->user[0] != 'a'/*strcmp(cdata->user, "anonymous") != 0*/) {
		send_message(cdata->csock, 530, "Login incorrect.");
		free(cdata->user);
		cdata->user = NULL;
		cdata->auth = 0;
	}
	else {
		send_message(cdata->csock, 230, "Login successful.");
		cdata->auth = 1;
	}
	return (0);
}