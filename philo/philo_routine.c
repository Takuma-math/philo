/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takhayas <hayatakucat@icloud.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 01:40:37 by takhayas          #+#    #+#             */
/*   Updated: 2026/06/03 22:42:42 by takhayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return (((long long)tv.tv_sec * 1000) +(tv.tv_usec / 1000));
}

void	*philo_routine(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1500);
	while (check_dead_status(philo->rules) == 0)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			print_status(philo, "has taken a fork");
			pthread_mutex_lock(philo->right_fork);
			print_status(philo, "has taken a fork");
		}
		if (philo->id % 2 != 0)
		{
			pthread_mutex_lock(philo->right_fork);
			print_status(philo, "has taken a fork");
			pthread_mutex_lock(philo->left_fork);
			print_status(philo, "has taken a fork");
		}
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal_time = get_time_ms();
		pthread_mutex_unlock(&philo->meal_mutex);
		print_status(philo, "is eating");
		ft_usleep(philo->rules->t_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_status(philo, "is sleeping");
		ft_usleep(philo->rules->t_to_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
