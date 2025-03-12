/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:24:19 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/12 19:20:40 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (parse_arguments(argc, argv, &data))
		return (1);
	if (initialize_philosophers(&data))
		return (1);
	i = 0;
	while (i < data.num_philosophers)
	{
		if (pthread_create(&data.philosophers[i].thread, NULL,
				philosopher_life, &data.philosophers[i]) != 0)
			return (ft_printf("Error: Thread creation failed.\n"), 1);
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
