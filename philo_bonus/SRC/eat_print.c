/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 01:09:29 by jareste-          #+#    #+#             */
/*   Updated: 2023/07/27 12:38:05 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/philo.h"

int	print_state(char *str, t_philo *philo, int aux)
{
	long int	actual_time;

	aux = 0;
	actual_time = ft_get_time();
	actual_time = actual_time - philo->data->start_time;
	if (philo->data->dead == 0 && aux == 1)
	{
		sem_wait(philo->data->write);
		if (philo->data->dead == 0)
			printf("%ld philo %i %s\n", actual_time, philo->id, str);
		philo->data->dead = 1;
	}
	if (philo->data->dead == 0 && aux == 0)
	{
		sem_wait(philo->data->write);
		if (philo->data->dead == 0 && actual_time >= 0)
			printf("%ld philo %i %s\n", actual_time, philo->id, str);
	}
	sem_post(philo->data->write);
	return (0);
}

void	eat_cycle(t_philo *philo)
{
	// take_fork(philo);
	while(!philo->data->dead)
	{
		sem_wait(philo->data->forks);
		print_state("took a fork", philo, 0);
		if (philo->data->philo_num == 1)
		{
			ft_usleep(philo->data->death_time);
			print_state("DIED", philo, 1);
			return ;
		}
		sem_wait(philo->data->forks);
		print_state("took a fork", philo, 0);
		philo->eating = 1;
		print_state("is eating", philo, 0);
		philo->time_to_die = ft_get_time() + philo->data->death_time;
		ft_usleep(philo->data->eat_time);
		philo->eat_cont++;
		philo->eating = 0;
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		if (((philo->eat_cont < philo->data->meals_nb) || \
		philo->data->meals_nb == -1))
		{
			print_state("is sleeping", philo, 0);
			ft_usleep(philo->data->sleep_time);
			print_state("is thinking", philo, 0);
		}
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
