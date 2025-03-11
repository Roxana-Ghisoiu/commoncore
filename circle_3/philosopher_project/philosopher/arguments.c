#include "philosopher.h"

static int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	parse_arguments(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
	{
		ft_printf("Error: Incorrect number of arguments.\n");
		return (1);
	}
	if (!is_valid_number(argv[1]) || !is_valid_number(argv[2]) ||
		!is_valid_number(argv[3]) || !is_valid_number(argv[4]) ||
		(argc == 6 && !is_valid_number(argv[5])))
	{
		ft_printf("Error: Arguments must be positive numbers.\n");
		return (1);
	}
	data->num_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->num_times_to_eat = (argc == 6) ? ft_atoi(argv[5]) : -1;
	if (data->num_philosophers <= 0 || data->time_to_die <= 0 ||
		data->time_to_eat <= 0 || data->time_to_sleep <= 0 ||
		(argc == 6 && data->num_times_to_eat <= 0))
	{
		ft_printf("Error: Arguments must be greater than zero.\n");
		return (1);
	}
	return (0);
}
