/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 00:49:47 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/08 19:39:47 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	is_map_line(char *line)
{
	while (*line == ' ')
		line++;
	if (*line == '\0')
		return (false);
	while (*line)
	{
		if (*line != ' ' && *line != '0' && *line != '1'
			&& *line != 'N' && *line != 'S'
			&& *line != 'E' && *line != 'W'
			&& *line != 'D' && *line != 'O' && *line != 'M')
			return (false);
		line++;
	}
	return (true);
}
