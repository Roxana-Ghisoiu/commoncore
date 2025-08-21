/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:32:31 by vberegoi          #+#    #+#             */
/*   Updated: 2025/05/22 19:53:53 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw_utils.h"

int	get_pixel_color(t_img *img, int x, int y)
{
	char	*pixel;
	int		color;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

void	set_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}
