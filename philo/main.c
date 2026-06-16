/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takhayas <hayatakucat@icloud.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:34:05 by takhayas          #+#    #+#             */
/*   Updated: 2026/06/17 00:22:36 by takhayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
		i++;
	write(2, msg, i);
}

static void	mutex_destroyer(t_rules *rules, t_philo *philos)
{
	int	j;

	pthread_mutex_destroy(&rules->print_mutex);
	pthread_mutex_destroy(&rules->death_mutex);
	destroy_all_fork(rules);
	if (philos)
	{
		j = 0;
		while (j < rules->n_philo)
		{
			pthread_mutex_destroy(&philos[j].meal_mutex);
			j++;
		}
		free(philos);
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_rules	rules;
	t_philo	*philos;

	philos = NULL;
	rules.forks = NULL;
	if (parse_input(argc, argv, &rules))
		return (1);
	if (prepare_rules(&rules))
		return (print_error("fail to init rules mutex\n"), 1);
	if (fork_prepare(&rules))
	{
		mutex_destroyer(&rules, NULL);
		return (print_error("fail to create fork_mutex"), 1);
	}
	if (prepare_philos(&philos, &rules))
	{
		mutex_destroyer(&rules, NULL);
		return (print_error("fail to malloc philos"), 1);
	}
	rules.start_time_us = get_time_us();
	if (start_simulation(&rules, philos))
		return (mutex_destroyer(&rules, philos), 1);
	mutex_destroyer(&rules, philos);
	return (0);
}
