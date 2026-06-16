/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takhayas <hayatakucat@icloud.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 01:40:37 by takhayas          #+#    #+#             */
/*   Updated: 2026/06/17 00:03:43 by takhayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_us(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return (((long long)tv.tv_sec * 1000000L) + tv.tv_usec);
}

void	one_philo_process(t_philo *philo, t_rules *rules)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	ft_usleep(philo->rules->t_to_die, rules);
	pthread_mutex_unlock(philo->left_fork);
}

void	meal_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time_us = get_time_us();
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, "is eating");
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->id % 2 == 0)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	else
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	pthread_mutex_lock(first);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(second);
	print_status(philo, "has taken a fork");
}

void	think_pause(t_philo *philo)
{
	long long	think_time;
	long long	since_meal;

	pthread_mutex_lock(&philo->meal_mutex);
	since_meal = get_time_us() - philo->last_meal_time_us;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (philo->rules->n_philo % 2 == 1)
		think_time = philo->rules->t_to_eat * 2
			- philo->rules->t_to_sleep - 10000;
	else
		think_time = (philo->rules->t_to_die
				- since_meal - philo->rules->t_to_eat) / 2;
	if (think_time > philo->rules->t_to_die - since_meal - 10000)
		think_time = philo->rules->t_to_die - since_meal - 10000;
	if (think_time > 0)
		ft_usleep(think_time, philo->rules);
}
