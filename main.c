/*
** EPITECH PROJECT, 2018
** Project
** File description:
** main.c
*/

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <signal.h>
#include "include/my_ftp.h"

static const char FLAGS[2][7] = {
	"--help",
	"-h"
};

static const char *HELP_MESSAGE =
	"USAGE\t./server port path\n"
	"\n"
	"\tport\t"
	"is the port number on which the server socket listens\n"
	"\tpath\tis the path to the home directory for the Anonymous user";

static const char *ERROR_MESSAGE = "Error : The port should be greater"
	" than 0 and you should also precise a path.";

static void fill_string(char **str, const char *to_copy)
{
	free(*str);
	*str = strdup(to_copy);
}

/*
** Description:
**  This function parse the arguments sent by the user when exec the program
**  then it stores the datas in a struct args_t.
*/
static int parse_args(int argc, char **argv, args_t *args)
{
	struct stat buf;
	size_t size;
	char *str = NULL;

	for (int i = 1 ; i < argc ; i++) {
		if (argv[i][0] >= '0' && argv[i][0] <= '9')
			args->port = atoi(argv[i]);
		if (stat(argv[i], &buf) != -1)
			fill_string(&args->path, argv[i]);
	}
	if (args->port <= 0 || args->path == NULL)
		return (fprintf(stderr, "%s\n", ERROR_MESSAGE) * 0 + 84);
	size = strlen(args->path);
	if (args->path[size - 1] == '/')
		args->path[size - 1] = 0;
	str = realpath(args->path, str);
	free(args->path);
	args->path = str;
	return (0);
}

int main(int argc, char **argv)
{
	args_t args = {0, NULL};
	csd_t data;
	int ret = 84;

	if (argc >= 3) {
		signal(SIGINT, &sigint);
		ret = parse_args(argc, argv, &args);
		if (ret != 84) {
			data.args = args;
			ret = wait_for_connections(&data);
		}
		return (ret);
	}
	if (argc >= 2 && (strcmp(argv[1], FLAGS[0]) == 0 ||
		strcmp(argv[1], FLAGS[1]) == 0)) {
		printf("%s\n", HELP_MESSAGE);
		return (0);
	}
	return (ret);
}