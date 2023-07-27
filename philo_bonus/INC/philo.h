/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:48:06 by jareste-          #+#    #+#             */
/*   Updated: 2023/07/27 14:14:55 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <semaphore.h>

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	int				eat_cont;
	int				eating;
	int				finished;
	long int		time_to_die;
	pid_t			pid;
}					t_philo;

typedef struct s_data
{
	// pthread_t		*tid;
	// pthread_t		t1;
	pthread_t		t0;
	pthread_mutex_t	d_check;

	int				philo_num;
	int				meals_nb;
	int				dead;
	int				finish_all;
	t_philo			*philos;
	long int		death_time;
	long int		eat_time;
	long int		sleep_time;
	long int		start_time;
	sem_t			*write;
	sem_t			*forks;
	// sem_t			*dead;


	// pthread_mutex_t	lock;
	// pthread_mutex_t	write;
}					t_data;

//init.c doc
int			init_data(t_data *data, char **argv);
int			start_arrays(t_data *data);
void		init_philos(t_data *data);
int			check_args(int argc, char **argv);
void		init_forks(t_data *data);

//utils.c doc
int			ft_error(char *str, t_data *data);
int			ft_usleep(useconds_t time);
void		ft_exit(t_data *data);
long int	ft_get_time(void);
void		ft_clear(t_data	*data);

//print_utils.c
int			print_state(char *str, t_philo *philo, int aux);
int			ft_atoi(const char *str);

//threads.c
void		take_fork(t_philo *philo);
void		eat_cycle(t_philo *philo);
void		thread_start(t_data *data);

#endif
