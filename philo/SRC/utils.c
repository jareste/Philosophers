/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 05:53:18 by jareste-          #+#    #+#             */
/*   Updated: 2023/07/28 08:13:11 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/philo.h"

long int	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long time)
{
	time += ft_get_time();
	while (ft_get_time() <= time)
		usleep(200);
}

int	ft_error(char *str, t_data *data)
{
	printf("%s\n", str);
	if (data)
		ft_exit(data);
	return (1);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	ft_clear(data);
}

void	ft_clear(t_data	*data)
{
	if (data->tid)
		free(data->tid);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}
