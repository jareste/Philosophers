/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 01:09:29 by jareste-          #+#    #+#             */
/*   Updated: 2023/07/29 11:06:30 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/philo.h"

int	print_state(char *str, t_philo *philo)
{
	t_data		*data;

	data = philo->data;
	if (data->dead == 0 && ft_get_time() - data->start_time >= 0)
	{
		pthread_mutex_lock(&data->write);
		if (data->dead == 0 && ft_get_time() - data->start_time >= 0)
			printf("%ld philo %i %s\n", ft_get_time() - \
			data->start_time, philo->id, str);
		pthread_mutex_unlock(&data->write);
	}
	return (0);
}

int	print_state_dead(char *str, t_philo *philo)
{
	long int	actual_time;
	t_data		*data;

	data = philo->data;
	actual_time = ft_get_time();
	actual_time = actual_time - data->start_time;
	pthread_mutex_lock(&data->write);
	if (data->dead == 0 && actual_time >= 0)
		printf("%ld philo %i %s\n", actual_time, philo->id, str);
	philo->data->dead = 1;
	ft_usleep(300);
	pthread_mutex_unlock(&data->write);
	return (0);
}

static void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_state("took a fork", philo);
	pthread_mutex_lock(philo->l_fork);
	print_state("took a fork", philo);
}

void	eat_cycle(t_philo *philo)
{
	take_fork(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	print_state("is eating", philo);
	philo->time_to_die = ft_get_time() + philo->data->death_time;
	ft_usleep(philo->data->eat_time);
	philo->eat_cont++;
	pthread_mutex_unlock(&philo->lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	print_state("is sleeping", philo);
	ft_usleep(philo->data->sleep_time);
	print_state("is thinking", philo);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				neg;
	long long int	result;

	i = 0;
	result = 0;
	neg = 0;
	if (str[i] == '-')
		neg = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	if (neg == 1)
		return (-result);
	return (result);
}
