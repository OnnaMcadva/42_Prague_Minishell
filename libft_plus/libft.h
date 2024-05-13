/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:01:31 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/13 14:57:04 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

// # include <stdio.h>
// # include <string.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

int			ft_atoi(const char *str);

void		ft_bzero(void *s, size_t n);

void		*ft_calloc(size_t nmemb, size_t size);

char		*get_next_line(int fd, int with_n_or_not);
char		*gnl_next(char *buffer);
char		*gnl_line(char *buffer, int with_n_or_not);
char		*gnl_join_n_free(char *src, char *buffer, size_t b);
char		*gnl_read_file(int fd, char *src);

int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);

char		*ft_itoa(int n);

void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*));
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);

void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, void *src, size_t n);
void		*ft_memset(void *str, int c, size_t n);

int			ft_printf(const char *fmt, ...);
size_t		pf_format_specifier( char fmt, va_list args, size_t printlen);
int			pf_print_char(va_list args);
int			pf_print_integer(va_list args);
int			pf_print_string(va_list args);
int			pf_print_ptr(va_list args);
void		pf_put_ptr(uintptr_t num);
int			pf_ptr_len(uintptr_t num);
int			pf_print_unsigned(va_list args);
char		*pf_unsigned_itoa(unsigned int n);
int			pf_print_hex(va_list args, const char format);

void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);

char		**ft_split(char const *s, char c);

char		*ft_strcat(char *dest, const char *src);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strdup(const char *str);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t siz);
size_t		ft_strlcpy(char *dst, const char *src, size_t siz);
size_t		ft_strlen(const char *str);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(char *s1, char *s2, unsigned int n);
char		*ft_strnstr(const char *str, const char *to_find, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);

int			ft_tolower(int ch);
int			ft_toupper(int ch);

#endif
