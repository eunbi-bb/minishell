NAME		= minishell
CC			= gcc
ifdef DEBUG
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -g
READLINE	= -lreadline
else
CFLAGS		= -Wall -Wextra -Werror
READLINE	= -lreadline
endif
LIBFT		= libft
OBJ_DIR		= obj/
SRC_DIR		= src/

HEADER_DIR	= includes/
HEADER_SRC	= minishell.h lexer.h parser.h executor.h error.h
HEADERS		= $(addprefix $(HEADER_DIR), $(HEADER_SRC))

SRC_DIR		= src/
LEXER_DIR	= lexer/
PARSER_DIR	= parser/
EXECUTOR_DIR	= executor/ 

LEXER		= lexer node_utils
PARSER		= parser cmd_node_utils redir_node_utils
EXECUTOR	= redirection executor heredoc executor_utils redirection

SRC_FILE	= main.c \
			env.c \
			free_llist.c error.c free_llist.c

SRC			= 	$(addsuffix .c, $(addprefix src/lexer/, $(LEXER))) \
				$(addsuffix .c, $(addprefix src/parser/, $(PARSER))) \
				$(addsuffix .c, $(addprefix src/executor/, $(EXECUTOR))) \

OBJ			=	$(addprefix $(OBJ_DIR), $(SRC_FILE:.c=.o)) \
				$(SRC:c=o) \

OBJF =	.cache_exists

CYAN_B		=	\033[1;96m
CYAN		=	\033[0;96m

all: $(NAME)

$(NAME):	$(OBJ) $(OBJF)
			@make -C $(LIBFT)
			@$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME) $(READLINE)
			@echo "$(CYAN_B)- Lexer is compiled -"

$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(HEADER)| $(OBJF)
			@$(CC) $(CFLAGS) -c $< -o $@

$(OBJF):
		@mkdir -p $(OBJ_DIR)
		@mkdir -p $(OBJ_DIR)$(SRC_DIR)
		@mkdir -p $(OBJ_DIR)$(SRC_DIR)$(LEXER_DIR)
		@mkdir -p $(OBJ_DIR)$(SRC_DIR)$(PARSER_DIR)
		@mkdir -p $(OBJ_DIR)$(SRC_DIR)$(EXECUTOR_DIR)
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