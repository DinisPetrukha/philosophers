/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:17:14 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/11/11 11:16:38 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_PHILO 200

typedef struct s_philo
{
	pthread_t		t;
	int				n_philos;
	int				id;
	int				*dead;
	int				philo_dead_flag;
	bool			eating;
	bool			eaten_enough;
	int				eaten;
	int				n_times_to_eat;
	size_t			last_meal;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	size_t			start;
	pthread_mutex_t	philo_meal_lock;
	pthread_mutex_t	philo_dead_lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*meal_count_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*write_lock;
}	t_philo;

typedef struct s_data
{
	int				dead_flag;
	int				n_philos;
	int				main_n_philos;
	int				main_n_times_to_eat;
	int				everybody_eaten;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	meal_count_lock;
	pthread_mutex_t	thread_initializer;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
	pthread_t		monitor;
	pthread_t		waiter;
	t_philo			*philos;
}	t_data;

size_t	get_time(void);
int		ft_usleep(size_t milliseconds, t_philo *philo);
long	ft_atoi(const char *str);
int		check_error(int argc, char *argv[]);
int		init_data(t_data *data, int argc, char *argv[]);
void	*r(void *ptr);
int		is_not_dead(t_philo *philo);
int		create_threads(t_data *data);
void	clean_mutex(t_data *data);
void	printf_lock(t_philo *philo, char *condition);
int		dead_getter(t_data *data);
int		is_not_dead(t_philo *philo);
void	drop_forks(t_philo *philo);
void	print_dead(t_data *data, t_philo *philo);
int		philo_dead_getter(t_data *data);
void	finish_the_game(t_data *data);
void	times_eaten_cheker(t_philo *philo);
void	eating_flag_false_changer(t_philo *philo);
void	set_all_to_dead(t_data *data);