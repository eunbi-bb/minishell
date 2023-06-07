# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ssemanco <ssemanco@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/06/07 10:16:07 by ssemanco      #+#    #+#                  #
#    Updated: 2023/06/07 15:54:39 by ssemanco      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror

SRC =   cmd_echo.c \
		cmd_pwd.c \
		env.c \
		exec.c \
		cmd_cd.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	cd libft/ && $(MAKE)
	gcc -o $(NAME) $(OBJ) libft/libft.a 

%.o:%.c
	gcc $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)
	cd libft/ && $(MAKE) clean

fclean: clean
	rm -f $(NAME)
	cd libft/ && rm -f libft.a

re: fclean all