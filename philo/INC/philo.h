/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:48:06 by jareste-          #+#    #+#             */
/*   Updated: 2023/07/28 08:11:40 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t0;
	int				id;
	int				eat_cont;
	int				eating;
	int				finished;
	long int		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_philo;

typedef struct s_data
{
	pthread_t		*tid;
	pthread_t		t1;

	int				philo_num;
	int				meals_nb;
	int				dead;
	int				finish_all;
	t_philo			*philos;
	long int		death_time;
	long int		eat_time;
	long int		sleep_time;
	long int		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}					t_data;

//init.c doc
int			init_data(t_data *data, char **argv);
int			start_arrays(t_data *data);
void		init_philos(t_data *data);
int			check_args(int argc, char **argv);
void		init_forks(t_data *data);

//utils.c doc
int			ft_error(char *str, t_data *data);
void		ft_usleep(long long time);
void		ft_exit(t_data *data);
long int	ft_get_time(void);
void		ft_clear(t_data	*data);

//print_utils.c
int			print_state(char *str, t_philo *philo);
int			print_state_dead(char *str, t_philo *philo);
int			ft_atoi(const char *str);

//threads.c
void		take_fork(t_philo *philo);
void		eat_cycle(t_philo *philo);
int			thread_start(t_data *data);

#endif
