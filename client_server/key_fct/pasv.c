/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** pasv.c
*/

#include <stddef.h>
#include <fcntl.h>
#include <zconf.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <pthread.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <memory.h>
#include "../../include/my_ftp.h"

static const char *LOG_PLS = "Please login with USER and PASS.";

int get_socket_info(int sock, struct sockaddr_in *s)
{
	socklen_t len = sizeof(*s);
	return (getsockname(sock, (struct sockaddr *)s, &len) + 1);
}

char *get_ip(struct sockaddr_in *sc)
{
	char str[INET_ADDRSTRLEN * 2];
	inet_ntop(AF_INET, (const void *)&sc->sin_addr, str,
		INET_ADDRSTRLEN * 2);
	return strdup(str);
}

char *get_socket_ip(int sock)
{
	struct ifaddrs *ifap;
	struct sockaddr_in addr;
	struct sockaddr_in *iface;
	char *res = NULL;

	if (getifaddrs(&ifap) == -1 || !get_socket_info(sock, &addr))
		return (0);
	for (struct ifaddrs *head = ifap ; head ; head = head->ifa_next)
		if (head->ifa_addr && head->ifa_addr->sa_family == AF_INET) {
			iface = (struct sockaddr_in *)head->ifa_addr;
			if (iface->sin_addr.s_addr == addr.sin_addr.s_addr) {
				res = get_ip(iface);
				freeifaddrs(ifap);
				return (res);
			}
		}
	freeifaddrs(ifap);
	return (res);
}

int pasv(struct client_data *cdata, char **cmd)
{
	pthread_t thread;

	UNUSED(cmd);
	if (is_auth(cdata)) {
		if (pthread_create(&thread, NULL, start_thread, cdata) != 0)
			return (1);
	} else
		send_message(cdata->csock, 530, LOG_PLS);
	return (0);
}