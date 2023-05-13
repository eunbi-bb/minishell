/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: eucho <eucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:01:27 by eucho         #+#    #+#                 */
/*   Updated: 2023/02/25 11:57:08 by eucho         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdarg.h> /*for va_list*/
# include <inttypes.h> /*uintptr_t*/
# include <unistd.h> /*read*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

//is
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
//to
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi(const char *str);
//string
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s1);
//memory
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_calloc(size_t count, size_t size);
//part2
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
//bonus part
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
//printf
int		ft_printf(const char *format, ...);
int		ft_formats(va_list args, const char format);

int		ft_print_char(int c);
int		ft_print_string(char *str);
int		ft_print_pointer(uintptr_t ptr);
int		ft_print_number(int n);
int		ft_print_unsigned(unsigned int n);
int		ft_print_hex(unsigned int num, const char format);
int		ft_print_percent(void);

void	ft_putchar(char c);

void	ft_put_pointer(uintptr_t num);
int		ft_pointer_len(uintptr_t num);

void	ft_put_hex(unsigned int num, const char format);
int		ft_hex_len(unsigned int num);

char	*ft_unsigned_itoa(unsigned int n);
int		ft_num_len(unsigned int num);
//get_next_line
char	*get_next_line(int fd);
size_t	gnl_strlen(char *s);
void	gnl_strlcpy(char *dst, char *src, size_t size);
char	*gnl_strchr(char *s, int c);
void	*gnl_memcpy(void *dst, const void *src, size_t n);
char	*gnl_strjoin(char *s1, char *s2);

char	*read_line(int fd, char *content);
char	*copy_line(char *content);
char	*next_content(char *content);
#endif
