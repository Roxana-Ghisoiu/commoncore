/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberegoi <vberegoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:53:56 by vberegoi          #+#    #+#             */
/*   Updated: 2025/07/11 03:14:14 by vberegoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parse.h"
#include "string_utils.h"
#include <stdlib.h>
#include <string.h>

static int	clamp_color(int value)
{
	if (value < 0)
		return (0);
	if (value > 255)
		return (255);
	return (value);
}

int	parse_rgb(const char *str)
{
	int	r;
	int	g;
	int	b;

	if (sscanf(str, "%d,%d,%d", &r, &g, &b) != 3)
		exit_error("Invalid RGB format. Use: R,G,B");
	r = clamp_color(r);
	g = clamp_color(g);
	b = clamp_color(b);
	return ((r << 16) | (g << 8) | b);
}

static void	parse_floor_line(char *line, t_config *config)
{
	char	*value;

	value = ft_strtrim(line + 2, " \t\n");
	if (ends_with(value, ".xpm"))
	{
		config->floor_texture = ft_strdup(value);
		config->floor_from_texture = 1;
	}
	else
	{
		config->floor_color = parse_rgb(value);
		config->floor_from_texture = 0;
	}
	free(value);
}

static void	parse_ceiling_line(char *line, t_config *config)
{
	char	*value;

	value = ft_strtrim(line + 2, " \t\n");
	if (ends_with(value, ".xpm"))
	{
		config->ceiling_texture = ft_strdup(value);
		config->ceiling_from_texture = 1;
	}
	else
	{
		config->ceiling_color = parse_rgb(value);
		config->ceiling_from_texture = 0;
	}
	free(value);
}

void	parse_color_or_texture(char *line, t_config *config)
{
	if (strncmp(line, "F ", 2) == 0)
		parse_floor_line(line, config);
	else if (strncmp(line, "C ", 2) == 0)
		parse_ceiling_line(line, config);
}
