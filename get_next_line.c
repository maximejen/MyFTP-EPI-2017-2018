/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** get_next_line.c
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <memory.h>
#include "include/get_next_line.h"

static int my_find_line(char *str, int o)
{
	int i;

	i = 0;
	if (o == 0) {
		while (str[i] != '\n' && str[i] != '\0')
			i++;
		if (str[i] == '\n')
			return (i);
		return (-1);
	} else if (o == 1) {
		while (str != NULL && str[i] != '\0')
			i++;
		return (i);
	}
	return (-1);
}

static char *my_strcat_g(char *dest, char *src)
{
	int i;
	int m;
	char *string;

	i = 0 + 0 * (m = 0);
	if ((string = malloc(
		my_find_line(dest, 1) + my_find_line(src, 1) + 1)) == NULL)
		return (NULL);
	while (dest != NULL && dest[i] != '\0') {
		string[i] = dest[i];
		i++;
	}
	while (src != NULL && src[m] != '\0') {
		string[i] = src[m];
		i = i + 1;
		m = m + 1;
	}
	string[i] = '\0';
	free(dest);
	return (string);
}

static char *seperate(char **str, int z)
{
	int i;
	char *buffer;
	int a;

	if ((buffer = malloc(z + 1)) == NULL)
		return (NULL);
	i = -1;
	while (++i < z)
		buffer[i] = (*str)[i];
	buffer[i] = '\0';
	if ((*str)[i] == '\n')
		i++;
	a = 0;
	while ((*str)[i] != '\0')
		(*str)[a++] = (*str)[i++];
	(*str)[a] = '\0';
	return (buffer);
}

static int no_line(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (1);
	while (str[i] != '\0') {
		if (str[i] == '\n')
			return (0);
		i++;
	}
	return (0);
}

char *get_next_line(const int fd)
{
	static char *s = NULL;
	static int g = 0;
	char buf[READ_SIZE + 1] = {0};
	int i;

	while (1) {
		i = -2;
		if (g == 1)
			return (NULL);
		if (no_line(s) == 1)
			if ((i = read(fd, buf, READ_SIZE)) == -1)
				return (NULL);
		if (i == 0 && (g == 0) && (g = 1) == 1)
			return ((s != NULL && s[0] == '\0') ? (NULL) : (s));
		if ((s = my_strcat_g(s, (i == -2) ? (NULL) : (buf))) == NULL)
			return (NULL);
		if ((i = my_find_line(s, 0)) != -1)
			return (seperate(&s, i));
	}
}
