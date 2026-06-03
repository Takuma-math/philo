/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takhayas <hayatakucat@icloud.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:34:05 by takhayas          #+#    #+#             */
/*   Updated: 2026/06/03 23:49:44 by takhayas         ###   ########.fr       */
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
	prepare_rules(&rules);
	if (fork_prepare(&rules))
		return (printf("fail to create fork_mutex"), 1);
	if (prepare_philos(&philos, &rules))
		return (printf("fail to malloc philos"), 1);
	rules.start_time = get_time_ms();
	start_simulation(&rules, philos);
	i = 0;
	while (i < rules.n_philo)
	{
		pthread_mutex_destroy(&philos[i].meal_mutex);
		i++;
	}
	free(philos);
	destroy_all_fork(&rules);
	pthread_mutex_destroy(&rules.print_mutex);
	pthread_mutex_destroy(&rules.death_mutex);
	return (0);
}
