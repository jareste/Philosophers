/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 08:03:56 by jareste-          #+#    #+#             */
/*   Updated: 2023/07/27 09:59:38 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/philo.h"

void	*checker(void *data_ptr)
{
	int		i;
	t_data *data;

	i = 0;
	data = (t_data *)data_ptr;
	while (data->dead == 0 && data->finish_all == 0)
	{
		if (data->philos[i].eating == 0)
		{
			if ((ft_get_time() >= data->philos[i].time_to_die) && \
			data->philos[i].eating == 0 && data->philos[i].finished == 0)
				print_state("DIED", &data->philos[i], 1);
		}
		i++;
		if (i == data->philo_num)
			i = 0;
		// if (data->philos[0].eat_cont == 3)
			// return ;
	}
	return (NULL);
}

void	routine(t_philo *philo)
{
	int		i;

	if (philo->eat_cont && ((philo->data->eat_time * 2 >= \
	philo->data->death_time) || (philo->data->eat_time * 3 >= philo->data->death_time \
	&& philo->data->philo_num % 2)))
		ft_usleep(philo->data->death_time + 200);
		printf("entru\n");
		printf("dead:::%i\n", philo->data->dead);
	philo->time_to_die = philo->data->death_time + ft_get_time();
	while (philo->data->dead == 0 && \
	(philo->eat_cont < philo->data->meals_nb || philo->data->meals_nb == -1))
	{
		eat_cycle(philo);
	}
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
}

void	thread_start(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = ft_get_time();
	pthread_create(&data->t0, NULL, &checker, &data);
	pthread_join(data->t0, NULL);
	while (++i < data->philo_num)
	{
		printf("%i\n", data->philo_num);
		// data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
			routine(&data->philos[i]);
		usleep(100);
	}

	// while (++i < data->philo_num)
	// 	pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]);
	// i = -1;
	// while (++i < data->philo_num && data->dead == 0)
	// {
	// 	if (i == 0)
	// 		pthread_create(&data->t1, NULL, &checker, data);
	// 	pthread_join(data->tid[i], NULL);
	// 	if (i == 1)
	// 		pthread_join(data->t1, NULL);
	// }
}
