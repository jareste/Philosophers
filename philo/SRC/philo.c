/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 05:57:24 by jareste-          #+#    #+#             */
/*   Updated: 2023/07/28 08:22:42 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/philo.h"

static void	check_finish(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_num && data->dead == 0)
		{
			usleep(1000);
			if (data->philos[i].finished == 1)
				i++;
		}
		printf("Simulation ended after %i eats\n", data->philos[0].eat_cont);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (1);
	if (check_args(argc, argv))
		return (1);
	if (init_data(&data, argv))
		return (1);
	init_philos(&data);
	init_forks(&data);
	if (thread_start(&data))
		return (ft_error("Fatal error ocurred", &data));
	if (data.philos[0].finished == 1 && data.dead == 0)
		check_finish(&data);
	ft_exit(&data);
	return (0);
}
