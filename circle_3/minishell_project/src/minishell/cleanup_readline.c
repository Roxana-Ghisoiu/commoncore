/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:11:40 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/23 20:36:55 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Cleans up readline memory/history.
 */
void	cleanup_readline(void)
{
	clear_history(); 
	rl_clear_history();
	rl_free_line_state();
	rl_deprep_terminal();
}
