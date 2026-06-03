/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takhayas <hayatakucat@icloud.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 22:06:30 by takhayas          #+#    #+#             */
/*   Updated: 2026/06/04 01:48:49 by takhayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead_status(t_rules *rules)
{
	int	status;

	pthread_mutex_lock(&rules->death_mutex);
	status = rules->is_dead;
	pthread_mutex_unlock(&rules->death_mutex);
	return (status);
}

void	*monitor_routine(void *arg)
{
	t_philo		*philos;
	t_rules		*rules;
	int			i;
	int			meal_complete_num;
	long long	last_meal;

	philos = (t_philo *)arg;
	rules = philos[0].rules;
	while (1)
	{
		i = 0;
		meal_complete_num = 0;
		while (i < rules->n_philo)
		{
			pthread_mutex_lock(&philos[i].meal_mutex);
			last_meal = philos[i].last_meal_time;
			if (rules->must_eat_count != -1
				&& philos[i].meal_count >= rules->must_eat_count)
				meal_complete_num++;
			pthread_mutex_unlock(&philos[i].meal_mutex);
			if (get_time_ms() - last_meal > rules->t_to_die)
			{
				pthread_mutex_lock(&rules->death_mutex);
				rules->is_dead = 1;
				pthread_mutex_unlock(&rules->death_mutex);
				pthread_mutex_lock(&rules->print_mutex);
				printf("%lld %d died\n", get_time_ms() - rules->start_time,
					philos[i].id);
				pthread_mutex_unlock(&rules->print_mutex);
				return (NULL);
			}
			if (meal_complete_num == rules->n_philo)
			{
				pthread_mutex_lock(&rules->death_mutex);
				rules->is_dead = 1;
				pthread_mutex_unlock(&rules->death_mutex);
				return (NULL);
			}
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
