/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takhayas <hayatakucat@icloud.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 22:06:30 by takhayas          #+#    #+#             */
/*   Updated: 2026/06/07 00:56:22 by takhayas         ###   ########.fr       */
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

static void	frag_dead(t_rules *rules)
{
	pthread_mutex_lock(&rules->death_mutex);
	rules->is_dead = 1;
	pthread_mutex_unlock(&rules->death_mutex);
	return ;
}

static void	dead_print(t_rules *rules, t_philo *philo)
{
	pthread_mutex_lock(&rules->print_mutex);
	printf("%lld %d died\n", get_time_ms() - rules->start_time,
		philo->id);
	pthread_mutex_unlock(&rules->print_mutex);
	return ;
}

static int	m_check(t_rules *rules, t_philo *phi, int *m_num)
{
	long long	current_time;
	int			is_dead;

	current_time = get_time_ms();
	pthread_mutex_lock(&phi->meal_mutex);
	is_dead = (current_time - phi->last_meal_time > rules->t_to_die);
	if (rules->must_eat_count != -1
		&& phi->meal_count >= rules->must_eat_count)
		(*m_num)++;
	pthread_mutex_unlock(&phi->meal_mutex);
	return (is_dead);
}

void	*monitor_routine(void *arg)
{
	t_philo		*philos;
	t_rules		*rules;
	int			i;
	int			meal_complete_num;

	philos = (t_philo *)arg;
	rules = philos[0].rules;
	while (1)
	{
		i = 0;
		meal_complete_num = 0;
		while (i < rules->n_philo)
		{
			if (m_check(rules, &philos[i], &meal_complete_num))
				return (frag_dead(rules), dead_print(rules, &philos[i]), NULL);
			if (meal_complete_num == rules->n_philo)
				return (frag_dead(rules), NULL);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
