/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takhayas <hayatakucat@icloud.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 12:43:34 by takhayas          #+#    #+#             */
/*   Updated: 2026/06/04 01:46:20 by takhayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	prepare_rules(t_rules *rules)
{
	rules->is_dead = 0;
	if (pthread_mutex_init(&(rules->print_mutex), NULL))
		return (1);
	if (pthread_mutex_init(&((rules->death_mutex)), NULL))
	{
		pthread_mutex_destroy(&(rules->print_mutex));
		return (1);
	}
	return (0);
}

int	prepare_philos(t_philo **philos, t_rules *rules)
{
	int	i;

	*philos = (t_philo *) malloc(sizeof(t_philo) * rules->n_philo);
	if (!(*philos))
		return (1);
	i = 0;
	while (i < rules->n_philo)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].left_fork = &rules->forks[i % rules->n_philo];
		(*philos)[i].right_fork = &rules->forks[(i + 1) % rules->n_philo];
		(*philos)[i].rules = rules;
		(*philos)[i].meal_count = 0;
		if (pthread_mutex_init(&((*philos)[i].meal_mutex), NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&((*philos)[i].meal_mutex));
			free(*philos);
			*philos = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	start_philo_thread(t_rules *rules, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < rules->n_philo)
	{
		philos[i].last_meal_time = rules->start_time;
		if (pthread_create(&philos[i].thread, NULL, &philo_routine, &philos[i]))
		{
			pthread_mutex_lock(&rules->death_mutex);
			rules->is_dead = 1;
			pthread_mutex_unlock(&rules->death_mutex);
			while (--i >= 0)
				pthread_join(philos[i].thread, NULL);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	start_monitor_thread(t_rules *rules, t_philo *philos)
{
	int	i;

	if (pthread_create(&rules->monitor_thread, NULL, &monitor_routine, philos))
	{
		pthread_mutex_lock(&rules->death_mutex);
		rules->is_dead = 1;
		pthread_mutex_unlock(&rules->death_mutex);
		i = rules->n_philo;
		while (--i >= 0)
			pthread_join(philos[i].thread, NULL);
		return (1);
	}
	return (0);
}

int	start_simulation (t_rules *rules, t_philo *philos)
{
	int	i;

	if (start_philo_thread(rules, philos))
		return (printf ("fail to create philos thread"), 1);
	if (start_monitor_thread(rules, philos))
		return (printf ("fail to create monitor thread"), 1);
	i = 0;
	while (i < rules->n_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(rules->monitor_thread, NULL);
	return (0);
}
