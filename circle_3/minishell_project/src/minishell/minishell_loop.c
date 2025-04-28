/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:17:51 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/28 17:44:26 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_exit_command(t_shell *sh, char *line);
static char	*get_prompt(void);
static bool	has_input_errors(const char *line);

/**
 * @brief Processes the input line and decides whether it's export or not.
 */
void	process_and_execute_line(t_shell *sh, const char *input)
{
	if (!input || !*input)
		return ;
	if (is_export_command(input))
	{
		process_export_directly(sh, input);
		return ;
	}
	process_non_export(sh, input);
}

/**
 * @brief Main input loop: prompt → readline → process.
 */
void	run_shell_loop(t_shell *sh)
{
	char	*line;
	char	*prompt;

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
		add_history(line);
		check_exit_command(sh, line);
		if (!has_input_errors(line))
			process_and_execute_line(sh, line);
		free(line);
	}
}

/**
 * @brief Checks if the user entered 'exit' and exits properly.
 */
static void	check_exit_command(t_shell *sh, char *line)
{
	if (ft_strncmp(line, "exit", 5) == 0)
	{
		free(line);
		printf("exit\n");
		free_shell(sh);
		cleanup_readline();
		exit(0);
	}
}

/**
 * @brief Creates prompt string.
 */
static char	*get_prompt(void)
{
	return (ft_strdup("minishell$ "));
}

/**
 * @brief Validates input for forbidden chars or unclosed quotes.
 */
static bool	has_input_errors(const char *line)
{
	if (has_unclosed_single_quotes(line))
	{
		printf("minishell: unclosed single quote\n");
		return (true);
	}
	if (has_unclosed_double_quotes(line))
	{
		printf("minishell: unclosed double quote\n");
		return (true);
	}
	if (has_forbidden_chars(line))
	{
		printf("minishell: forbidden characters (; or \\) not allowed\n");
		return (true);
	}
	return (false);
}
