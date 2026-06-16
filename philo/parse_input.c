/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takhayas <hayatakucat@icloud.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:37:19 by takhayas          #+#    #+#             */
/*   Updated: 2026/06/17 00:22:02 by takhayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	die_eat_sleep_input(t_rules *rules, char **argv)
{
	rules->t_to_die = atoi_philo(argv[2]) * 1000;
	rules->t_to_eat = atoi_philo(argv[3]) * 1000;
	rules->t_to_sleep = atoi_philo(argv[4]) * 1000;
}

int	parse_input(int argc, char **argv, t_rules *rules)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (print_error("too many or few inputs\n"), 1);
	while (i < 5)
	{
		if (atoi_philo(argv[i]) < 0)
			return (print_error("inputs must be positive ints\n"), 1);
		i++;
	}
	if (argc == 6)
	{
		if (atoi_philo(argv[i]) < 0)
			return (print_error("inputs must be positive ints\n"), 1);
		rules->must_eat_count = atoi_philo(argv[5]);
	}
	else
		rules->must_eat_count = -1;
	rules->n_philo = atoi_philo(argv[1]);
	if (rules->n_philo < 1)
		return (print_error("number of philosophers must be at least 1\n"), 1);
	die_eat_sleep_input(rules, argv);
	return (0);
}
