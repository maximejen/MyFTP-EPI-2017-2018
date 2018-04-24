/*
** EPITECH PROJECT, 2018
** my_ftp
** File description:
** my_ftp.h
*/

#ifndef MY_FTP_MY_FTP_H
	#define MY_FTP_MY_FTP_H

	#define INVALID_SOCKET -1
	#define BUFFER_SIZE 1024
	#define CLRF "\n\r"
	#define UNUSED(x) ((void)(x))

typedef int t_socket;

typedef struct args_s {
	int port;
	char *path;
} args_t;

typedef struct connect_server_data {
	args_t args;
	t_socket csock;
	t_socket client_sock;
} csd_t;

typedef struct client_data {
	t_socket csock;
	char *user;
	int auth;
	char *pwd;
	char *home;
	int (*fctptr[14])(struct client_data *, char **cmd);
	char buffer[BUFFER_SIZE];
	int ctn;
} client_data_t;

/*
** main_server.c
*/
int wait_for_connections(csd_t *data);
void sigint(int sig);

/*
** socket.c
*/
int create_socket(int, const char *);

/*
** custom_split.c
*/
char **custom_split(const char *str, char c);
void free_wordtab(char **tab);
char *strtoupper(char *str);

/*
** client_server.c
*/
int handle_client(csd_t *data);
int is_auth(client_data_t *cdata);

/*
** str_replace.c
*/
char *str_replace(char *str, const char *to_replace, const char *replace_str);
char *str_push(char *str, const char *to_push);

/*
** read_and_interpret.c
*/
int interpret_instruction(client_data_t *cdata);
int get_instruction(client_data_t *cdata);

/*
** communication.c
*/
int send_message(t_socket sock, int code, const char *message);

/*
** key_fct
*/
int cdup(struct client_data *cdata, char **cmd);
int cwd(struct client_data *cdata, char **cmd);
int dele(struct client_data *cdata, char **cmd);
int help(struct client_data *cdata, char **cmd);
int list(struct client_data *cdata, char **cmd);
int noop(struct client_data *cdata, char **cmd);
int pass(struct client_data *cdata, char **cmd);
int pasv(struct client_data *cdata, char **cmd);
int port(struct client_data *cdata, char **cmd);
int pwd(struct client_data *cdata, char **cmd);
int quit(struct client_data *cdata, char **cmd);
int retr(struct client_data *cdata, char **cmd);
int stor(struct client_data *cdata, char **cmd);
int user(struct client_data *cdata, char **cmd);
int unknown(struct client_data *cdata, char **cmd);

#endif //MY_FTP_MY_FTP_H
