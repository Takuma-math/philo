/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_prepare.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takhayas <hayatakucat@icloud.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 12:43:34 by takhayas          #+#    #+#             */
/*   Updated: 2026/06/03 21:53:44 by takhayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		pthread_mutex_init(&((*philos)[i].meal_mutex), NULL);
		i++;
	}
	return (0);
}
