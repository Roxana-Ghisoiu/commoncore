/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:06:54 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/26 17:28:01 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Libft - Biblioteca de funcții utile, inclusiv ft_printf */

#ifndef LIBFT_H
# define LIBFT_H

# include <ctype.h> /* pentru funcțiile de testare a caracterelor */
# include <stdarg.h>
# include <stddef.h> /* pentru tipul size_t */
# include <stdio.h>  /* pentru funcțiile de intrare/ieșire standard */
# include <stdlib.h> /* pentru malloc, calloc, free */
# include <string.h> /* pentru funcțiile de manipulare a șirurilor */
# include <unistd.h> /* pentru write */

int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_isalnum(int i);
int					ft_isalpha(int c);
int					ft_isascii(int i);
int					ft_isdigit(int i);
int					ft_isprint(int i);
char				*ft_itoa(int n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char const *s, int fd);
char				**ft_split(char const *s, char c);
char				*ft_strchr(const char *s, int i);
char				*ft_strdup(const char *s);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlen(const char *str);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t n);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_tolower(int i);
int					ft_toupper(int i);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

/* Funcții din ft_printf */

int					ft_printf(const char *format, ...);

int					ft_print_char(char c);
int					ft_print_str(char *str);
int					ft_print_num(int n);
int					ft_print_num_unsigned(unsigned int n);
int					ft_print_num_base(unsigned long num, char specifier);
int					ft_print_ptr(void *ptr, int *i);

#endif
