NAME	= libft.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
OBJ_DIR	= obj/
HEADER = libft.h

SRC_LIBFT = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_toupper.c ft_tolower.c ft_atoi.c ft_strlen.c ft_strchr.c ft_strrchr.c \
	ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c ft_strdup.c ft_bzero.c \
	ft_memset.c ft_memcpy.c ft_memchr.c ft_memcmp.c ft_memmove.c ft_calloc.c \
	ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
	ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c

SRC_PRINTF = ft_printf.c ft_print_char.c ft_print_hex.c ft_print_number.c ft_print_pointer.c ft_print_string.c ft_print_unsigned.c ft_print_percent.c

SRC_GNL = get_next_line.c get_next_line_utils.c


OBJ_LIBFT = $(addprefix $(OBJ_DIR), $(SRC_LIBFT:.c=.o))
OBJ_PRINTF = $(addprefix $(OBJ_DIR), $(SRC_PRINTF:.c=.o))
OBJ_GNL = $(addprefix $(OBJ_DIR), $(SRC_GNL:.c=.o))

OBJF	=	.cache_exists

all: $(NAME)

$(NAME): $(OBJ_LIBFT) $(OBJ_PRINTF) $(OBJ_GNL)
		@ar -rcs $(NAME) $(OBJ_LIBFT) $(OBJ_PRINTF) $(OBJ_GNL)
		@echo "- Libft is compiled -"

$(OBJ_DIR)%.o : %.c $(HEADER)| $(OBJF)
			@$(CC) $(CFLAGS) -c $< -o $@

$(OBJF):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -f *.o
	@rm -rf $(OBJ_DIR)
	@echo "- Object files are cleaned -"


fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@echo "- Executable files are cleaned -"

re: fclean all
	@echo "- cleaned and rebuilt -"

.PHONY: bonus all clean fclean re
