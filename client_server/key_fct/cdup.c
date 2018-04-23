/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** cdup.c
*/

#include <stddef.h>
#include "../../include/my_ftp.h"

static const char *CWD[3] = {
	"CWD",
	"..",
	NULL
};

int cdup(struct client_data *cdata, char **cmd)
{
	UNUSED(cmd);
	cwd(cdata, (char **)CWD);
	return (0);
}