/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:04:56 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/11/11 11:16:04 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	printf_lock(t_philo *philo, char *condition)
{
	size_t	cur_time;

	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead != 0)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return ;
	}
	pthread_mutex_unlock(philo->dead_lock);
	pthread_mutex_lock(philo->write_lock);
	cur_time = get_time() - philo->start;
	printf("%li %i %s\n", cur_time, philo->id, condition);
	pthread_mutex_unlock(philo->write_lock);
}

static void	eat(t_philo *philo)
{
	if (philo->id % 2 != 0)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
	printf_lock(philo, "has taken a fork");
	if (philo->n_philos == 1)
	{
		ft_usleep(philo->t_die, philo);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	if (philo->id % 2 != 0)
		pthread_mutex_lock(philo->l_fork);
	else
		pthread_mutex_lock(philo->r_fork);
	printf_lock(philo, "has taken a fork");
	printf_lock(philo, "is eating");
	pthread_mutex_lock(&philo->philo_meal_lock);
	philo->eating = true;
	philo->last_meal = get_time() + philo->t_die;
	pthread_mutex_unlock(&philo->philo_meal_lock);
	times_eaten_cheker(philo);
	ft_usleep(philo->t_eat, philo);
	eating_flag_false_changer(philo);
	drop_forks(philo);
}

static void	zzz(t_philo *philo)
{
	if (is_not_dead(philo) == 0)
	{
		printf_lock(philo, "is sleeping");
		ft_usleep(philo->t_sleep, philo);
	}
}

static void	think(t_philo *philo)
{
	if (is_not_dead(philo) == 0)
		printf_lock(philo, "is thinking");
}

void	*r(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(philo->t_eat / 2, philo);
	while (is_not_dead(philo) == 0)
	{
		eat(philo);
		zzz(philo);
		think(philo);
	}
	return (NULL);
}
