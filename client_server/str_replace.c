/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** str_replace.cpp
*/

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <zconf.h>

char *str_push(char *str, const char *to_push)
{
	size_t size;

	if (to_push == NULL || strcmp(to_push, "") == 0)
		return (str);
	if (str == NULL) {
		str = strdup(to_push);
	} else {
		size = strlen(str) + strlen(to_push);
		str = realloc(str, (size + 1));
		if (str == NULL)
			return (NULL);
		str = strcat(str, to_push);
		str[size] = 0;
	}
	return (str);
}

char *str_replace(char *str, const char *to_replace, const char *replace_str)
{
	char *tmp = NULL;
	char *tmp1 = str;
	char *s = NULL;

	do {
		tmp = strsep(&tmp1, to_replace);
		if (tmp && (!(s = str_push(s, tmp))))
			return (NULL);
		if (tmp1 && !(s = str_push(s, replace_str)))
			return (NULL);
	} while (tmp);
	free(str);
	return s;
}

/*
** Description:
** This function find a random nbr under max using /dev/urandom file
*/
int rand_nbr(size_t max)
{
	int rand = 0;
	int fd = open("/dev/urandom", O_RDONLY);

	if (fd != -1) {
		read(fd, &rand, 4);
		rand %= max;
		close(fd);
	}
	return (rand);
}