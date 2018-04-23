/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** pwd.c
*/

#include <stdio.h>
#include "../../include/my_ftp.h"

static const char *LOG_PLS = "Please login with USER and PASS.";

int pwd(struct client_data *cdata, char **cmd)
{
	UNUSED(cmd);
	if (is_auth(cdata)) {
		dprintf(cdata->csock, "257 \"%s\"%s", cdata->pwd, CLRF);
	}
	else
		send_message(cdata->csock, 530, LOG_PLS);
	return (0);
}