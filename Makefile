NAME		= minishell
CC			= gcc
ifdef DEBUG
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -g
else
CFLAGS		= -Wall -Wextra -Werror
endif

ifdef LINUX
READLINE_FLAGS = -lreadline -lhistory -lncurses
OBJ_FLAGS		= -I${HOME}/.brew/opt/readline/include
else
READLINE_FLAGS	= -lreadline -L${HOME}/.brew/opt/readline/lib
OBJ_FLAGS		= -I${HOME}/.brew/opt/readline/include
endif

LIBFT		= libft
OBJ_DIR		= obj/
SRC_DIR		= src/

HEADER_DIR	= includes/
HEADER_SRC	= minishell.h lexer.h parser.h executor.h error.h
HEADERS		= $(addprefix $(HEADER_DIR), $(HEADER_SRC))

INCLUDES	= -I$(HEADER_DIR)

SRC_DIR		= src/
SRC_FILE	= main.c free_llist.c error.c expand.c signals.c \
				lexer/lexer.c \
				lexer/node_utils.c \
				lexer/lexer_utils.c \
				parser/parser.c \
				parser/cmd_node_utils.c \
				parser/redir_node_utils.c \
				executor/executor.c \
				executor/executor_utils.c \
				executor/redirection.c \
				executor/pipe_utils.c \
				executor/heredoc.c \
				executor/execute_builtins.c \
				builtins/cmd_cd.c \
				builtins/cmd_echo.c \
				builtins/cmd_exit.c \
				builtins/cmd_export.c \
				builtins/cmd_pwd.c \
				builtins/cmd_unset.c \
				builtins/env.c \

OBJ			=	$(addprefix $(OBJ_DIR), $(SRC_FILE:.c=.o))

OBJF =	.cache_exists

CYAN_B		=	\033[1;96m
CYAN		=	\033[0;96m

all: $(NAME)

$(NAME): $(OBJ) $(OBJF)
		@make -C $(LIBFT)
		@$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME) $(READLINE_FLAGS)
		@echo "$(CYAN_B)- Minishell is compiled -"

$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(HEADER)| $(OBJF)
			@mkdir -p $(@D)
			@$(CC) $(CFLAGS) $(OBJ_FLAGS) $(INCLUDES) -c $< -o $@

$(OBJF):
		@mkdir -p $(OBJ_DIR)
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