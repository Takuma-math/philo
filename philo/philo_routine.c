/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takhayas <hayatakucat@icloud.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 00:02:25 by takhayas          #+#    #+#             */
/*   Updated: 2026/06/17 00:12:12 by takhayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_eat(t_philo *philo, t_rules *rules)
{
	take_forks(philo);
	if (check_dead_status(rules))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	meal_routine(philo);
	ft_usleep(rules->t_to_eat, rules);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

static void	philo_sleep_think(t_philo *philo, t_rules *rules)
{
	print_status(philo, "is sleeping");
	ft_usleep(rules->t_to_sleep, rules);
	print_status(philo, "is thinking");
	think_pause(philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)arg;
	rules = philo->rules;
	if (rules->n_philo == 1)
		return (one_philo_process(philo, rules), NULL);
	if (philo->id % 2 == 0)
		ft_usleep(rules->t_to_eat / 2, rules);
	while (check_dead_status(rules) == 0)
	{
		if (philo_eat(philo, rules))
			break ;
		if (check_dead_status(rules))
			break ;
		philo_sleep_think(philo, rules);
	}
	return (NULL);
}
