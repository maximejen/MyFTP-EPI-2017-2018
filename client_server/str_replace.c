/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** str_replace.cpp
*/

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

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
	char *tmp;
	char *tmp1 = str;
	char *s = NULL;

	while ((tmp = strsep(&tmp1, to_replace)) != NULL && tmp1 != NULL) {
		if (!(s = str_push(s, tmp)) || !(s = str_push(s, replace_str)))
			return NULL;
		tmp1 = tmp;
	}
	free(str);
	return s;
}