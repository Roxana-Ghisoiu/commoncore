/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:19:44 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/11 01:30:42 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_UTILS_H
# define STRING_UTILS_H

# include <stddef.h>

char	*ft_strtrim(const char *s1, const char *set);
int		ends_with(const char *str, const char *suffix);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	**ft_split(const char *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);

#endif
