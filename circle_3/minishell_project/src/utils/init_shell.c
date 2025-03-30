/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:36:58 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/28 12:46:10 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Allocates and initializes the shell structure.
 * 
 * @param sh Pointer to the shell structure pointer.
 * @param envp The environment variables.
 */
void	init_shell(t_shell **sh, char **envp)
{
	*sh = malloc(sizeof(t_shell));
	if (!*sh)
	{
		perror("minishell: malloc failed");
		exit(EXIT_FAILURE);
	}
	(*sh)->env_list = NULL;
	(*sh)->tokens = NULL;
	(*sh)->root = NULL;
	(*sh)->line_input = NULL;
	(*sh)->exit_code = 0;
	// (Mai târziu: convertești envp[] în listă t_env *)
	(void)envp;
}

/**
 * @brief Frees memory used by the shell structure.
 * 
 * @param sh The shell structure to free.
 */
void	free_shell(t_shell *sh)
{
	if (!sh)
		return ;
	// (Mai târziu: eliberare tokens, env_list etc.)
	free(sh);
}
