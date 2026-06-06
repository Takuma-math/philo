/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takhayas <hayatakucat@icloud.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:34:05 by takhayas          #+#    #+#             */
/*   Updated: 2026/06/06 01:53:31 by takhayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	mutex_destroyer(t_rules *rules, t_philo *philos, int i)
{
	int	j;

	pthread_mutex_destroy(&rules->print_mutex);
	pthread_mutex_destroy(&rules->death_mutex);
	if (i == 2 || i == 3)
		destroy_all_fork(rules);
	if (i == 3)
	{
		if (!philos)
			return ;
		j = 0;
		while (j < rules->n_philo)
		{
			pthread_mutex_destroy(&philos[j].meal_mutex);
			j++;
		}
		if (philos)
			free(philos);
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_rules	rules;
	t_philo	*philos;

	if (parse_input(argc, argv, &rules))
		return (1);
	if (prepare_rules(&rules))
		return (printf("fail to init rules mutex\n"), 1);
	if (fork_prepare(&rules))
	{
		mutex_destroyer(&rules, NULL, 1);
		return (printf("fail to create fork_mutex"), 1);
	}
	if (prepare_philos(&philos, &rules))
	{
		mutex_destroyer(&rules, NULL, 2);
		return (printf("fail to malloc philos"), 1);
	}
	rules.start_time = get_time_ms();
	start_simulation(&rules, philos);
	mutex_destroyer(&rules, philos, 3);
	return (0);
}
