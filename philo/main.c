/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takhayas <hayatakucat@icloud.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:34:05 by takhayas          #+#    #+#             */
/*   Updated: 2026/06/04 01:33:05 by takhayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	main(int argc, char **argv)
{
	t_rules	rules;
	t_philo	*philos;
	int		i;

	if (parse_input(argc, argv, &rules))
		return (1);
	if (prepare_rules(&rules))
		return (printf("fail to init rules mutex\n"), 1);
	if (fork_prepare(&rules))
	{
		pthread_mutex_destroy(&rules.print_mutex);
		pthread_mutex_destroy(&rules.death_mutex);
		return (printf("fail to create fork_mutex"), 1);
	}
	if (prepare_philos(&philos, &rules))
	{
		destroy_all_fork(&rules);
		pthread_mutex_destroy(&rules.print_mutex);
		pthread_mutex_destroy(&rules.death_mutex);
		return (printf("fail to malloc philos"), 1);
	}
	rules.start_time = get_time_ms();
	start_simulation(&rules, philos);
	i = 0;
	while (i < rules.n_philo)
	{
		pthread_mutex_destroy(&philos[i].meal_mutex);
		i++;
	}
	if (philos)
		free(philos);
	destroy_all_fork(&rules);
	pthread_mutex_destroy(&rules.print_mutex);
	pthread_mutex_destroy(&rules.death_mutex);
	return (0);
}
