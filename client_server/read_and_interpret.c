/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** read_and_interpret.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <zconf.h>
#include "../include/my_ftp.h"
#include "../include/get_next_line.h"

static const char *KEYS[15] = {
	"CDUP",
	"CWD",
	"DELE",
	"HELP",
	"LIST",
	"NOOP",
	"PASS",
	"PASV",
	"PORT",
	"PWD",
	"QUIT",
	"RETR",
	"STOR",
	"USER",
	NULL
};

static char *read_instruction(t_socket sock, int *size)
{
	char *str = NULL;
	FILE *fsock = fdopen(sock, "r");

	printf("read in socket\n");
	if (getline(&str, (size_t *)size, fsock) < 0)
		return (NULL);
	return (str);
}

//static char *read_instruction(t_socket sock, int *size)
//{
//	char *str;
//
//	UNUSED(size);
//	if ((str = get_next_line(sock)) == NULL)
//		return (NULL);
//	return (str);
//}

int get_instruction(client_data_t *cdata)
{
	int rd = 0;
	char *str = NULL;

	str = read_instruction(cdata->csock, &rd);
	if (str) {
		str = str_replace(str, CLRF, "\0");
		strncpy(cdata->buffer, str, strlen(str));
	} else
		return (-1);
	return (0);
}

int interpret_instruction(client_data_t *cdata)
{
	char **tab = custom_split(cdata->buffer, ' ');
	int i;

	tab[0] = strtoupper(tab[0]);
	for (i = 0 ; KEYS[i] && strcmp(KEYS[i], tab[0]) != 0 ; i++);
	cdata->fctptr[i](cdata, tab);
	free_wordtab(tab);
	return (0);
}