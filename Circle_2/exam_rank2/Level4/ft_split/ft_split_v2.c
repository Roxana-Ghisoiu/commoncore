/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:38:57 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/27 17:26:50 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

char	*ft_strncpy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	while(i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return(dest);
}

char	**ft_split(char *str)
{
	int	i = 0;
	int	word_count = 0;
	int	start = 0;
	int	j = 0;
	char	**result;

	while(str[i])
	{
		while(str[i] &&(str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
				i++;
		if(str[i] != '\0')
			word_count++;
		while(str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
			i++;
	}

	result = malloc(sizeof(char *) * (word_count +1));
	if (result == NULL)
		return (NULL);

	i = 0;
	while(str[i])
	{
		while(str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		start = i;
		while(str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
			i++;
		if(i > start)
		{
			result[j] = malloc(sizeof (char) * (i -start + 1));
			if (result[j] == NULL)
			{
				while(j > 0)
				{
					free(result [--j]);
					j--;
				}
				free(result);
				return(NULL);
			}
			ft_strncpy(result[j], &str[start], i-start);
			j++;	
		}	
	}
	result[j] = NULL;
	return(result);
}
/*
int	main(void)
{
	char *str = "   This is  a  test string  with  multiple spaces ";
	char **result;
	int i = 0;

	result = ft_split(str);

	if (result != NULL)
	{
		while (result[i] != NULL)
		{
			printf("Cuvantul %d: %s\n", i + 1, result[i]);
			free(result[i]);
			i++;
		}
		free(result);
	}
	else
	{
		printf("Eroare la alocarea memoriei!\n");
	}

	return (0);
}*/
