/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:21:41 by rghisoiu          #+#    #+#             */
/*   Updated: 2024/10/22 16:23:24 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*DESCRIPTION
The	strdup(void) function returns a pointer to a new string
which is a duplicate of the string s.
Memory for the new string is obtained with malloc(3),
and can be freed with	free(3).
RETURN VALUE
On success,the strdup() function returns a pointer to the duplicated string.
It returns  NULL  if  insufficient memory was available,
with err no set to indicate the cause of the error.*/

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*str;

	len = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
