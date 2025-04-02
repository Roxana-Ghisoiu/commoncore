/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:17:51 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/02 14:36:28 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*get_prompt(void);
static void		process_and_execute_line(t_shell *sh, char *line);
static void		execute_args(t_shell *sh, char **args);
static bool		has_input_errors(const char *line);

/**
 * @brief Main execution loop: displays prompt, reads input, and processes it.
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
		process_and_execute_line(sh, line);
		free(line);
	}
}

/**
 * @brief Generates the shell prompt string.
 */
static char	*get_prompt(void)
{
	return (ft_strdup("minishell$ "));
}

/**
 * @brief Checks for unclosed quotes or forbidden characters.
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
/**
 * @brief Expands the input line, splits it into args, and executes it.
 */

static void	process_and_execute_line(t_shell *sh, char *line)
{
	char	*expanded;
	char	**args;

	if (has_input_errors(line))
		return ;
	expanded = expand_line(sh, line);
	if (!expanded || !*expanded)
	{
		free(expanded);
		return ;
	}
	args = ft_split(expanded, ' ');
	free(expanded);
	execute_args(sh, args);
}

/**
 * @brief Resolves and executes the command from args.
 */
static void	execute_args(t_shell *sh, char **args)
{
	char	*cmd_path;

	if (!args || !args[0])
	{
		ft_free_split(args);
		return ;
	}
	cmd_path = find_command_path(sh, args[0]);
	if (cmd_path)
	{
		fork_and_execute(sh, cmd_path, args);
		free(cmd_path);
	}
	else
		printf("minishell: command not found: %s\n", args[0]);
	ft_free_split(args);
}
