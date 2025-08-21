/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:22:43 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/10 14:22:55 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_door(char tile)
{
	return (tile == 'D' || tile == 'O');
}

int	is_closed_door(char tile)
{
	return (tile == 'D');
}

int	is_open_door(char tile)
{
	return (tile == 'O');
}
