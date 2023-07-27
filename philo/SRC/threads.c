/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 08:03:56 by jareste-          #+#    #+#             */
/*   Updated: 2023/07/27 06:28:24 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/philo.h"

void	*checker(void *data_ptr)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)data_ptr;
	while (data->dead == 0 && data->finish_all == 0)
	{
		if (data->philos[i].eating == 0)
		{
			pthread_mutex_lock(&data->philos[i].lock);
			if ((ft_get_time() >= data->philos[i].time_to_die) && \
			data->philos[i].eating == 0 && data->philos[i].finished == 0)
				print_state("DIED", &data->philos[i], 1);
			pthread_mutex_unlock(&data->philos[i].lock);
		}
		i++;
		if (i == data->philo_num)
			i = 0;
		if (data->philos[0].eat_cont == 3)
			return (0);
	}
	return (NULL);
}

void	*routine(void *philo_ptr)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->eat_time / 10);
	philo->time_to_die = philo->data->death_time + ft_get_time();
	while (philo->data->dead == 0 && \
	(philo->eat_cont < philo->data->meals_nb || philo->data->meals_nb == -1))
		eat_cycle(philo);
	if (philo->eat_cont == philo->data->meals_nb)
	{
		print_state("FINISHED", philo, 0);
		philo->finished = 1;
		i = 0;
		while (i < philo->data->philo_num && philo->data->dead == 0)
			if (philo->data->philos[i].finished == 1 && philo->data->dead == 0)
				i++;
		if (i == philo->data->philo_num && philo->data->dead == 0)
			philo->data->finish_all = 1;
	}
	return (NULL);
}

void	thread_start(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = ft_get_time();
	while (++i < data->philo_num)
		pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]);
	i = -1;
	while (++i < data->philo_num && data->dead == 0)
	{
		if (i == 0)
			pthread_create(&data->t1, NULL, &checker, data);
		pthread_join(data->tid[i], NULL);
		if (i == 1)
			pthread_join(data->t1, NULL);
	}
}
