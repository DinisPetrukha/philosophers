/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:15:33 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/11/11 11:17:13 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	times_eaten_cheker(t_philo *philo)
{
	philo->eaten++;
	if (philo->eaten == philo->n_times_to_eat)
	{
		pthread_mutex_lock(philo->meal_count_lock);
		philo->eaten_enough = 1;
		pthread_mutex_unlock(philo->meal_count_lock);
	}
}

void	eating_flag_false_changer(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_meal_lock);
	philo->eating = false;
	pthread_mutex_unlock(&philo->philo_meal_lock);
}
