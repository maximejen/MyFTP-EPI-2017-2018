##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## my_ftp
##

CC	=	gcc

RM	=	rm -f

NAME	=	server

SRC	=	main.c					\
		main_server.c				\
		socket.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-I include -W -Wall -Wextra

LDFLAGS	=

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
