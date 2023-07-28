/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 08:03:56 by jareste-          #+#    #+#             */
/*   Updated: 2023/07/28 08:23:07 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/philo.h"

void	*checker(void *data_ptr)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)data_ptr;
	ft_usleep(data->death_time - (data->death_time / 4));
	while (i++ < data->philo_num && data->dead == 0 && data->finish_all == 0)
	{
		if (i == data->philo_num)
			i = 0;
		if (data->philos[i].eating == 0)
		{
			pthread_mutex_lock(&data->philos[i].lock);
			if ((ft_get_time() >= data->philos[i].time_to_die) && \
			data->philos[i].eating == 0 && data->philos[i].finished == 0)
				print_state_dead("DIED", &data->philos[i]);
			pthread_mutex_unlock(&data->philos[i].lock);
		}
		if (data->philos[i].finished == 1)
			break ;
	}
	return (NULL);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->id % 2 != 0)
		ft_usleep(philo->data->eat_time / 10);
	philo->time_to_die = philo->data->death_time + ft_get_time();
	while (philo->data->dead == 0)
	{
		eat_cycle(philo);
		if (philo->eat_cont == philo->data->meals_nb && \
		philo->data->meals_nb != -1)
			break ;
	}
	if (philo->eat_cont == philo->data->meals_nb)
	{
		print_state("FINISHED", philo);
		philo->finished = 1;
	}
	return (NULL);
}

int	thread_start(t_data *data)
{
	int	i;

	if (data->philo_num == 1)
	{
		pthread_mutex_lock(data->philos[0].l_fork);
		print_state("took a fork", &data->philos[0]);
		ft_usleep(data->death_time);
		print_state_dead("DIED", &data->philos[0]);
		pthread_mutex_unlock(data->philos[0].l_fork);
		return (0);
	}
	data->start_time = ft_get_time();
	i = -1;
	while (++i < data->philo_num)
		if (pthread_create(&data->tid[i], NULL, \
		&routine, &data->philos[i]) != 0)
			return (ft_error("Error creating thread.", data));
	if (pthread_create(&data->t1, NULL, &checker, data))
		return (ft_error("Error creating thread.", data));
	i = -1;
	pthread_join(data->t1, NULL);
	while (++i < data->philo_num && data->dead == 0)
		pthread_join(data->tid[i], NULL);
	return (0);
}
