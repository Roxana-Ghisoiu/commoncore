/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:35:16 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/02/16 17:50:14 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>

char    **ft_split(char *str)
{
	int	i = 0;
	int	j = 0;
	int	start;
	int	word_count = 0;
	char	**result;

	while (str[i])
	{
		while (str[i] == ' ' || str[i] =='\t' || str[i] == '\n')
			i++;
		if(str[i])
			word_count++;
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			i++;
	}

	result = malloc(sizeof(char*)*(word_count + 1));
	if(!result)
		return (NULL);

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] =='\t' || str[i] == '\n')
                        i++;
		start = i;
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
                        i++;
		if (i > start)
		{
			result[j] = malloc(i- start + 1);
			if (!result[j])
			{
				while (j > 0)
					free(result[--j]);
				free (result);
				return (NULL);
			}
			int k = -1;
			while(++k < i - start)
				result[j][k] = str[start + k];
			result[j][k] = '\0';
			j++;
		}
	}
	result[j] = NULL;
	return (result);
}

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
}
