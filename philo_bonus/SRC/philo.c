/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 05:57:24 by jareste-          #+#    #+#             */
/*   Updated: 2023/07/27 09:00:43 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/philo.h"

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
	thread_start(&data);
	if (data.finish_all == 1)
	 	printf("Simulation ended after %i eats\n", data.philos[0].eat_cont);
	ft_exit(&data);
	return (0);
}
