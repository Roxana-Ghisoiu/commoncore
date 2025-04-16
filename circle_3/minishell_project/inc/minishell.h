/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:13:03 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/16 19:10:09 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <termios.h>
# include <dirent.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <termcap.h>
# include <unistd.h>
# include <stdint.h>
# include <limits.h>
# include <errno.h>
# include "../libft/libft.h"
# include <stdbool.h>
# include <stddef.h>

# define RED "\033[0;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[1;34m"
# define END "\033[0m"
# define CYAN "\033[1;36m"

typedef enum e_token_type
{
	TOK_WORD = 1,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_APPEND,
	TOK_HEREDOC
}	t_token_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_node
{
	t_token_type	type;
	char			*value;
	char			**args;
	int				heredoc_fd;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_token
{
	t_token_type	type;
	char			*content;
	bool			was_quoted;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_shell
{
	t_node		*root;
	t_token		*tokens;
	t_env		*env_list;
	int			exit_code;
	char		*line_input;
}	t_shell;

typedef struct s_arg_info
{
	char	*arg;
	bool	was_quoted;
}	t_arg_info;

/* Structuri bonus goale, le completăm ulterior */
typedef struct s_heredoc_file		t_hdoc_file;
typedef struct s_heredoc_data		t_hdoc_data;
typedef struct s_quote_flags		t_quote_flags;
typedef struct s_exec_params		t_exec_params;
typedef struct s_pipe_data			t_pipe_data;
typedef struct s_input_copy_state	t_input_copy_state;
typedef struct s_cmd_finder			t_cmd_finder;
typedef struct s_tokenizer_state	t_tokenizer_state;

/*Prototypes function minishel/main.c */
int		main(int argc, char **argv, char **envp);
void	minishell_banner(void);
char	**create_env_copy(void);

/* Prototypes for minishell/input_processing.c */
t_token	*tokenize_input(const char *input);
void	create_and_add_token(t_token **tokens, char *content, bool quoted);

/*Prototypes function for minishel/minishell_loop.c */
void	process_and_execute_line(t_shell *sh, const char *input);
void	run_shell_loop(t_shell *sh);

/*Prototypes function for minishel/cleanup_readline.c */
void	cleanup_readline(void);

/*Prototypes function for parse/resolve_command.c */
char	*find_command_path(t_shell *sh, char *cmd);

/*Prototypes function for lexer/check_input_errors.c */
bool	has_unclosed_double_quotes(const char *input);
bool	has_forbidden_chars(const char *input);

/* Prototypes for lexer/handle_quotes.c */
char	*remove_single_quotes(const char *input);
bool	has_unclosed_single_quotes(const char *input);

/*Prototypes function for expander/expand_quotes_dollar.c */
char	*remove_double_quotes_preserve_dollar(const char *input);

/*Prototypes function for expander/expand_dollar.c */
char	*expand_line(t_shell *sh, const char *input);
char	*expand_env_variables(t_shell *sh, const char *input);

/*Prototypes function for expander/expand_asterisk.c */
char	**expand_asterisk(void);
char	**add_entry_to_array(char **result, int count, const char *name);

/*Prototypes function for expander/expanding_utils.c */
char	*extract_var_name(const char *str);
char	*ft_strjoin_free(char *s1, const char *s2);
char	*ft_strjoin_char(char *s1, char c);
void	ft_sort_str_array(char **arr);

/*Prototypes function for expander/expand_globbing_utils.c */
bool	has_unquoted_asterisk(const char *str);
char	*replace_asterisk_with_files(const char *input);

/* Prototypes for expander/expand_args_utils.c */
int		ft_arrlen(char **arr);
char	**expand_args_globbing_from_tokens(t_token *tokens);

/* Prototypes for expander/expand_protect_single_quotes.c */
char	*protect_dollar_in_single_quotes(const char *input);

/*Prototypes function for utils/utils_env_strjoin.c */
char	*get_env_value(t_env *env, char *key);
char	*ft_strjoin_three(char *s1, char *s2, char *s3);
void	ft_free_split(char **arr);

/*Prototypes function for utils/token_utils.c */
void	handle_special_token(t_token **tokens, const char *input, int *i);
void	set_token_type(t_token *token);

/*Prototypes function for execute/execute_word.c */
int		execute_word(t_shell *sh, t_node *node);

/*Prototypes function for execute/execute_word_utils.c */
int		fork_and_execute(t_shell *sh, char *path, char **args);
char	**convert_env_to_array(t_env *env);
int		execute_with_redir(t_shell *sh, char *path, char **args, t_node *node);

/*Prototypes function for execute/execute_redir_input.c */
int		execute_open_input_file(t_node *node);

/*Prototypes function for execute/execute_redir_output.c */
int		execute_open_output_file(t_node *node);

/*Prototypes function for execute/execute_redir_heredoc.c */
int		execute_handle_heredoc(const char *limiter);
int		execute_process_heredocs(t_node *node);

/*Prototypes function for execute/execute_redirections.c */
int		prepare_redirections(t_node *node);

/*Prototypes function for execute/execute_redir_errors.c */
int		check_redirection_syntax(t_token *tokens);

/* Prototypes for execute/execute.c */
int		execute_command(t_shell *sh, t_node *node);

/* Prototypes for execute/execute_utils.c */
void	inherit_heredoc_fd(t_node *node);
void	execute_parsed_tree(t_shell *sh);

/* Prototypes for utils/init_shell.c */
void	init_shell(t_shell **sh, char **envp);
void	free_shell(t_shell *sh);
t_env	*create_env_list(char **envp);
void	free_env_list(t_env *env);

/* Prototypes for utils/signal.c */
void	handle_signals(void);

/* Prototypes for utils/free_str_array.c */
void	free_str_array(char **arr);

/* Prototypes for utils/utils_tokens_asterisk.c */
void	add_token_back(t_token **lst, t_token *new);
int		tokens_len(t_token *tokens);
char	**extract_args_from_tokens(t_token *tokens);

/* Prototypes for utils/utils_tokens_free.c */
void	free_tokens(t_token *head);

/* Prototypes for utils /split_args_preserving_quotes.c */
char	**split_args_preserving_quotes(const char *input);
bool	is_quoted(const char *str);

/*Prototypes for treenodes/parse_command.c */
t_node	*parse_command(t_token **tokens);

/* Prototypes for treenodes/free_tree.c */
void	free_tree(t_node *node);

/* Prototypes for treenodes/tree_parse_args.c */
int		parse_args(t_node *cmd_node, t_token *tokens);

/* Prototypes for utils/debug_print_tokens.c */
void	debug_print_tokens(t_token *tokens);

#endif