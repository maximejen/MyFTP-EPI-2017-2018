/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** quit.c
*/

#include "../../include/my_ftp.h"

int quit(struct client_data *cdata, char **cmd)
{
	UNUSED(cmd);
	send_message(cdata->csock, 221, "Goodbye.");
	cdata->ctn = 0;
	return (0);
}