/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 06:33:11 by jareste-          #+#    #+#             */
/*   Updated: 2023/07/27 09:17:14 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/philo.h"

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
			return (ft_error("Please enter valid parameters.", NULL));
		i++;
	}
	return (0);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].eat_cont = 0;
		data->philos[i].eating = 0;
		data->philos[i].finished = 0;
		data->philos[i].time_to_die = data->death_time + ft_get_time();
		i++;
	}
}

int	start_arrays(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		return (ft_error("Malloc error.", data));
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	sem_unlink("/write");
	sem_unlink("/forks");
	// sem_unlink("/dead");
	data->write = sem_open("/lock", O_CREAT, 600, 1);
	data->forks = sem_open("/write", O_CREAT, 600, data->philo_num);
	data->philo_num = ft_atoi(argv[1]);
	data->meals_nb = -1;
	if (argv[5])
		data->meals_nb = ft_atoi(argv[5]);
	data->dead = 0;
	data->finish_all = 0;
	data->death_time = (long int)ft_atoi(argv[2]);
	data->eat_time = (long int)ft_atoi(argv[3]);
	data->sleep_time = (long int)ft_atoi(argv[4]);
	data->start_time = ft_get_time();
	if (start_arrays(data))
		return (1);
	return (0);
}
