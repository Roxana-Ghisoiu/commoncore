/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:24:19 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/10 16:47:59 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (parse_arguments(argc, argv, &data))
		return (1);
	initialize_philosophers(&data);
	i = 0;
	while (i < data.num_philosophers)
	{
		pthread_create(&data.philosophers[i].thread, NULL,
			philosopher_life, &data.philosophers[i]);
		i++;
	}
	i = 0;
	while (i < data.num_philosophers)
	{
		pthread_join(data.philosophers[i].thread, NULL);
		i++;
	}
	cleanup_resources(&data);
	return (0);
}
