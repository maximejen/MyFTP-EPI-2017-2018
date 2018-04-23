/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** noop.c
*/

#include "../../include/my_ftp.h"

static const char *LOG_PLS = "Please login with USER and PASS.";

int noop(struct client_data *cdata, char **cmd)
{
	UNUSED(cmd);
	if (is_auth(cdata)) {
		send_message(cdata->csock, 200, "NOOP OK.");
	}
	else
		send_message(cdata->csock, 530, LOG_PLS);
	return (0);
}