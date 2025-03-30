/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:17:51 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/27 17:54:14 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Generates the shell prompt string.
 * @return A dynamically allocated prompt string.
 */
static char	*get_prompt(void)
{
	return (ft_strdup("minishell$ "));
}

/**
 * @brief Main execution loop of the shell.
 * @param sh The main shell structure.
 */
void	run_shell_loop(t_shell *sh)
{
	char	*line;
	char	*prompt;

	(void)sh;
	while (1)
	{
		prompt = get_prompt();
		line = readline(prompt);
		free(prompt);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		printf("You entered: %s\n", line);
		free(line);
	}
}
