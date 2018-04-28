##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## my_ftp
##

CC	=	gcc

RM	=	rm -f

NAME	=	server

SRC	=	main.c							\
		main_server/main_server.c				\
		communication/socket.c					\
		client_server/client_server.c				\
		client_server/custom_split.c				\
		client_server/str_replace.c				\
		client_server/key_fct/cdup.c				\
                client_server/key_fct/port.c				\
                client_server/key_fct/dele.c				\
                client_server/key_fct/cwd.c				\
                client_server/key_fct/list.c				\
                client_server/key_fct/stor.c				\
                client_server/key_fct/pass.c				\
                client_server/key_fct/noop.c				\
                client_server/key_fct/user.c				\
                client_server/key_fct/help.c				\
                client_server/key_fct/pasv.c				\
                client_server/key_fct/retr.c				\
                client_server/key_fct/pwd.c				\
                client_server/key_fct/quit.c				\
                communication/communication.c				\
                client_server/read_and_interpret.c			\
                client_server/key_fct/unknown.c				\
                client_server/key_fct/transfer_thread_functions.c	\
                get_next_line.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-I include -W -Wall -Wextra -g

LDFLAGS	=	-lpthread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

tests_run:
	make -C ./tests/
	LD_LIBRARY_PATH=. ./tests/tester

clean_test:
	make clean -C ./tests/

fclean_test:
	make fclean -C ./tests/

.PHONY: all clean fclean re clean_test fclean_test tests_run
