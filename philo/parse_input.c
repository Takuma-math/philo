/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takhayas <hayatakucat@icloud.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:37:19 by takhayas          #+#    #+#             */
/*   Updated: 2026/05/13 11:49:32 by takhayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(char c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	atoi_philo(char *input)
{
	long	num;
	int		i;

	if (input == NULL || ft_strlen(input) > 11)
		return (-1);
	i = 0;
	while (input[i])
	{
		if (is_digit(input[i]) != 1)
			return (-1);
		i++;
	}
	num = 0;
	while (*input)
	{
		num *= 10;
		num += (long)(*input - '0');
		input++;
	}
	if (num > 2147483647 || num < 1)
		return (-1);
	return ((int)num);
}

int	parse_input(int argc, char **argv, t_rules *rules)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (printf("too many or few inputs\n"), 1);

	while (i < 5)
	{
		if (atoi_philo(argv[i]) < 0)
			return (printf("inputs must be positive ints\n"), 1);
		i++;
	}
	if (argc == 6)
	{
		if (atoi_philo(argv[i]) < 0)
			return (printf("inputs must be positive ints\n"), 1);
		rules->must_eat_count = atoi_philo(argv[5]);
	}
	else
		rules->must_eat_count = -1;
	rules->n_philo = atoi_philo(argv[1]);
	rules->t_to_die = atoi_philo(argv[2]);
	rules->t_to_eat = atoi_philo(argv[3]);
	rules->t_to_sleep = atoi_philo(argv[4]);
	return (0);
}
