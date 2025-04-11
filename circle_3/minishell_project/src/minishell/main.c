/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:14:26 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/11 18:18:25 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_child_pid = 0;

/**
 * @brief Entry point for the minishell program
 */
int	main(int argc, char **argv, char **envp)
{
	t_shell	*sh;
	char	**env_copy;

	(void)envp;
	(void)argc;
	(void)argv;
	sh = NULL;
	env_copy = NULL;
	minishell_banner();
	if (!envp || !*envp)
		env_copy = create_env_copy();
	else
		env_copy = envp;
	init_shell(&sh, env_copy);
	handle_signals();
	rl_bind_key('\t', rl_insert);
	run_shell_loop(sh);
	if (!envp || !*envp)
		free_str_array(env_copy);
	free_shell(sh);
	cleanup_readline();
	return (0);
}

/**
 * @brief Creates a default environment if envp is empty.
 */

char	**create_env_copy(void)
{
	char	**envp;
	char	*cwd;

	envp = malloc(sizeof(char *) * 4);
	if (!envp)
		exit(1);
	envp[0] = ft_strdup("SHLVL=1");
	envp[1] = ft_strdup("PATH=/bin/");
	cwd = getcwd(NULL, 0);
	if (cwd)
		envp[2] = ft_strjoin("PWD=", cwd);
	else
	{
		ft_putstr_fd("getcwd() error\n", 2);
		free_str_array(envp);
		exit(1);
	}
	free(cwd);
	envp[3] = NULL;
	return (envp);
}

/**
 * @brief Prints the startup banner for minishell.
 */
void	minishell_banner(void)
{
	printf("\n\t%s", CYAN);
	printf("███╗   ███╗██╗███╗   ██╗██╗ ██████╗██╗   ╔██╗");
	printf("╔████████╗██╗%s\n", END);
	printf("\t%s", BLUE);
	printf("██╔████╔██║██║██╔██╗ ██║██║██╔════╝██╝   ╚██╝");
	printf("║██══════╝██║%s\n", END);
	printf("\t%s", GREEN);
	printf("██║╚██╔╝██║██║██║╚██╗██║██║╚█████╗ █████████╗");
	printf("║████████╗██║%s\n", END);
	printf("\t%s", BLUE);
	printf("██║ ╚═╝ ██║██║██║  ╚███║██║ ╚═══██╗██╔═══╗██║");
	printf("║██╔═════╝██║%s\n", END);
	printf("\t%s", CYAN);
	printf("██║     ██║██║██║   ╚██╝██║██████╔╝██║   ║██║");
	printf("║████████╗████████╗%s\n", END);
	printf("\t%s", CYAN);
	printf("╚═╝     ╚═╝╚═╝╚═╝    ╚═╝═╝╚══════╝ ╚═╝   ╚══╝");
	printf("╚═══════╝╚═══════╝%s\n", END);
	printf("%s\n\t\t\tBy: rghisoiu%s", BLUE, END);
	printf("\t\t\t   %sBy: vberegoi%s\n", GREEN, END);
	printf("\t\t  ───────── {.⋅ ✯&&✯ ⋅.} ───────────\n");
}
