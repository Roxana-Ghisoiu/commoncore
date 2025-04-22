/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:17:51 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/22 19:51:10 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_exit_command(t_shell *sh, char *line);
static char	*get_prompt(void);
static bool	has_input_errors(const char *line);
/*static void	execute_args(t_shell *sh, char **args);*/

/**
 * @brief Processes the input line, expands arguments, and executes the command.
 *
 * Tokenizes the input, expands any variables or globbing, builds the AST,
 * processes heredoc if necessary, and executes the command.
 *
 * @param sh The shell structure.
 * @param input The raw input line.
 */

void	process_and_execute_line(t_shell *sh, const char *input)
{
	char		*expanded;
	t_token		*tokens;

	if (!input || !*input)
		return ;
	expanded = expand_line(sh, input);
	if (!expanded)
		return ;
	tokens = tokenize_input(expanded);
	if (!tokens)
	{
		free(expanded);
		return ;
	}
	expand_args_globbing(&tokens);
	sh->tokens = tokens;
	sh->root = build_parse_tree(&sh->tokens);
	free(expanded);
	execute_parsed_tree(sh);
}
/*void	process_and_execute_line(t_shell *sh, const char *input)
{
	char		*expanded;
	t_token		*tokens;

	if (!input || !*input)
		return ;
	expanded = expand_line(sh, input);
	if (!expanded)
		return ;
	tokens = tokenize_input(expanded);
	if (!tokens)
	{
		free(expanded);
		return ;
	}
	sh->tokens = tokens;
	sh->root = build_parse_tree(&sh->tokens);
	free(expanded);
	execute_parsed_tree(sh);
}
*/
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
 * @brief Checks if the user entered 'exit' and handles shell exit.
 * 
 * Frees resources and exits the shell if the input is 'exit'.
 * 
 * @param sh The shell structure.
 * @param line The input line to check.
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

/* Executes a parsed command if valid.

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
*/