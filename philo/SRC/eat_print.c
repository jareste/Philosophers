/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 01:09:29 by jareste-          #+#    #+#             */
/*   Updated: 2023/07/27 12:51:42 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/philo.h"

int	print_state(char *str, t_philo *philo, int aux)
{
	long int	actual_time;
	t_data		*data;

	data = philo->data;
	actual_time = ft_get_time();
	actual_time = actual_time - data->start_time;
	pthread_mutex_lock(&data->write);
	if (data->dead == 0 && actual_time >= 0)
		printf("%ld philo %i %s\n", actual_time, philo->id, str);
	if (aux == 1)
		data->dead = 1;
	pthread_mutex_unlock(&data->write);
	return (0);
}

void	take_fork(t_philo *philo)
{
	// if (philo->data->philo_num == 1)
	// {
	// 	pthread_mutex_lock(philo->l_fork);
	// 	print_state("took a fork", philo, 0);
	// 	ft_usleep(philo->data->death_time);
	// 	print_state("DIED", philo, 1);
	// }
	// else
	// {
		pthread_mutex_lock(philo->r_fork);
		print_state("took a fork", philo, 0);
		pthread_mutex_lock(philo->l_fork);
		print_state("took a fork", philo, 0);
	// }
}

void	eat_cycle(t_philo *philo)
{
	take_fork(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	print_state("is eating", philo, 0);
	philo->time_to_die = ft_get_time() + philo->data->death_time;
	ft_usleep(philo->data->eat_time);
	philo->eat_cont++;
	pthread_mutex_unlock(&philo->lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	if (!philo->finished)
	{
		print_state("is sleeping", philo, 0);
		ft_usleep(philo->data->sleep_time);
		print_state("is thinking", philo, 0);
	}
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
