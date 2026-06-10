/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takhayas <hayatakucat@icloud.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 11:40:55 by takhayas          #+#    #+#             */
/*   Updated: 2026/06/10 09:22:08 by takhayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fork_prepare(t_rules *rules)
{
	int	i;

	rules->forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * rules->n_philo);
	if (!rules->forks)
		return (1);
	i = 0;
	while (i < rules->n_philo)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL))
		{
			i--;
			while (i >= 0)
			{
				pthread_mutex_destroy(&rules->forks[i]);
				i--;
			}
			free(rules->forks);
			rules->forks = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

void	destroy_all_fork(t_rules *rules)
{
	int	i;

	if (!rules->forks)
		return ;
	i = 0;
	while (i < rules->n_philo)
	{
		pthread_mutex_destroy(&(rules->forks)[i]);
		i++;
	}
	free(rules->forks);
	rules->forks = NULL;
	return ;
}
