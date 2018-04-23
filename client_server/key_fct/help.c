/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** help.c
*/

#include "../../include/my_ftp.h"

static const char *HELP_MESSAGE = "- The following commands are recognized.\n"
	"CDUP CWD DELE HELP LIST NOOP PASS PASV PORT PWD QUIT RETR STOR USER";

static const char *LOG_PLS = "Please login with USER and PASS.";

int help(struct client_data *cdata, char **cmd)
{
	UNUSED(cmd);
	if (is_auth(cdata)) {
		send_message(cdata->csock, 214, HELP_MESSAGE);
		send_message(cdata->csock, 214, "Help OK.");
	}
	else
		send_message(cdata->csock, 530, LOG_PLS);
	return (0);
}