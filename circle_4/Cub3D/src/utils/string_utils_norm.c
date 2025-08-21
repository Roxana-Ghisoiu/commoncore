/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_norm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:36:15 by vberegoi          #+#    #+#             */
/*   Updated: 2025/05/22 19:58:31 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_utils.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dup;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	dup = malloc(i + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}
