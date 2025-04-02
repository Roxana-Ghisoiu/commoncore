/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:11:40 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/02 14:43:08 by rghisoiu         ###   ########.fr       */
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
	rl_deprep_terminal();
}
