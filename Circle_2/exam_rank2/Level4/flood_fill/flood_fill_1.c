/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:09:07 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/01/21 18:37:57 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "flood_fill.h"

void	fill(char **tab, t_point size, t_point pos, char target)
{
	if(pos.x < 0 || pos.x >= size.x || pos.y < 0 || pos.y >= size.y)
		return;
	if(tab[pos.y][pos.x] != target)
		return;
	tab[pos.y][pos.x] = 'F';

	t_point up = {pos.x, pos.y - 1};
	t_point down = {pos.x, pos.y + 1};
	t_point	left = {pos.x - 1, pos.y};
	t_point right = {pos.x + 1, pos.y};

	fill(tab, size, up, target);
	fill(tab, size, down, target);
	fill(tab, size, left, target);
	fill(tab, size, right, target);
}

void	flood_fill(char **tab, t_point size, t_point begin)
{
	char target = tab[begin.y][begin.x];
	if(target != 'F')
		fill(tab, size, begin, target);
}
/*
char** make_area(char** zone, t_point size)
{
	char** new;

	new = malloc(sizeof(char*) * size.y);
	for (int i = 0; i < size.y; ++i)
	{
		new[i] = malloc(size.x + 1);
		for (int j = 0; j < size.x; ++j)
			new[i][j] = zone[i][j];
		new[i][size.x] = '\0';
	}

	return new;
}

int main(void)
{
	t_point size = {8, 5};
	char *zone[] = {
		"11111111",
		"10001001",
		"10010001",
		"10110001",
		"11100001",
	};

	char**  area = make_area(zone, size);
	for (int i = 0; i < size.y; ++i)
		printf("%s\n", area[i]);
	printf("\n");

	t_point begin = {7, 4};
	flood_fill(area, size, begin);
	for (int i = 0; i < size.y; ++i)
		printf("%s\n", area[i]);
	return (0);
}*/
