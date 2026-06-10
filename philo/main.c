/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takhayas <hayatakucat@icloud.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:34:05 by takhayas          #+#    #+#             */
/*   Updated: 2026/06/10 01:40:00 by takhayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		return (printf("fail to init rules mutex\n"), 1);
	if (fork_prepare(&rules))
	{
		mutex_destroyer(&rules, NULL);
		return (printf("fail to create fork_mutex"), 1);
	}
	if (prepare_philos(&philos, &rules))
	{
		mutex_destroyer(&rules, NULL);
		return (printf("fail to malloc philos"), 1);
	}
	rules.start_time = get_time_ms();
	if (start_simulation(&rules, philos))
		return (mutex_destroyer(&rules, philos), 1);
	mutex_destroyer(&rules, philos);
	return (0);
}
