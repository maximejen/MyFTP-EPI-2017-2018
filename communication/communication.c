/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** communication.c
*/

#include <stdio.h>
#include "../include/my_ftp.h"

int send_message(t_socket sock, int code, const char *message)
{
	dprintf(sock, "%d %s%s", code, message, CLRF);
	return (0);
}