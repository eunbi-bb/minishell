NAME	= lexer.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
OBJ_DIR	= obj/
LIBFT		= libft
SRC_DIR		= src/

HEADER_DIR	= includes/
HEADER_SRC	= lexer.h
HEADERS		= $(addprefix $(HEADER_DIR), $(HEADER_SRC))

SRC_DIR		= src/
SRC_FILE	= lexer.c node_utils.c

OBJ			=	$(addprefix $(OBJ_DIR), $(SRC_FILE:.c=.o))

OBJF =	.cache_exists

CYAN_B		=	\033[1;96m
CYAN		=	\033[0;96m

all: $(NAME)

$(NAME):	$(OBJ) $(OBJF)
			@make -C $(LIBFT)
			@cp libft/libft.a .
			@mv libft.a $(NAME)
			@$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME)
			@echo "$(CYAN_B)- Lexer is compiled -"

$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(HEADER)| $(OBJF)
			@$(CC) $(CFLAGS) -c $< -o $@

$(OBJF):
		@mkdir -p $(OBJ_DIR)
		@mkdir -p $(OBJ_DIR)$(SRC_DIR)
		@touch $(OBJF)

clean:
		@rm -rf $(OBJ_DIR)
		@make clean -C $(LIBFT)
		@rm -f $(OBJF)
		@echo "$(CYAN)- Object files are cleaned -"

fclean: clean
		@rm -f $(NAME)
		@make fclean -C $(LIBFT)
		@echo "$(CYAN)- Executable files are cleaned -"

re:	fclean all

.PHONY: all clean fclean re