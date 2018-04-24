/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** pasv.c
*/

#include "../../include/my_ftp.h"

// IN THREAD
// Todo : generate a valid port ((rand() % 256) * 256) + (rand() % 256)
// Todo : create a socket with this port.
// Todo : wait to be destroyed or some commands.

int pasv(struct client_data *cdata, char **cmd)
{
	UNUSED(cdata);
	UNUSED(cmd);
	cdata->ctn = 0;
	// Todo : Create a thread
	// Todo
	return (0);
}