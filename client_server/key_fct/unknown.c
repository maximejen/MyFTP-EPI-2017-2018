/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** unknown.c
*/

#include "../../include/my_ftp.h"

static const char *LOG_PLS = "Please login with USER and PASS.";

int unknown(struct client_data *cdata, char **cmd)
{
	UNUSED(cmd);
	if (is_auth(cdata)) {
		send_message(cdata->csock, 530, LOG_PLS);
	}
	else
		send_message(cdata->csock, 500, "Unknown command.");
	return (0);
}