/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 06:33:11 by jareste-          #+#    #+#             */
/*   Updated: 2023/07/29 11:04:21 by jareste-         ###   ########.fr       */
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

void	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].l_fork = &data->forks[i];
		if (i == 0)
			data->philos[i].r_fork = &data->forks[data->philo_num - 1]; 
		else if (i > 0)
			data->philos[i].r_fork = &data->forks[i - 1];
		i++;
	}
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
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
}

static int	start_arrays(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->philo_num);
	if (!data->tid)
		return (ft_error("Malloc error.", data));
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		return (ft_error("Malloc error.", data));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
		return (ft_error("Malloc error.", data));
	return (0);
}

int	init_data(t_data *data, char **argv)
{
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
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->write, NULL);
	if (start_arrays(data))
		return (1);
	return (0);
}
