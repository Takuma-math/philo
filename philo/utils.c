/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takhayas <hayatakucat@icloud.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:27:51 by takhayas          #+#    #+#             */
/*   Updated: 2026/06/06 01:51:56 by takhayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	atoi_philo(char *input)
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
	if (num > 2147483647 || num < 0)
		return (-1);
	return ((int)num);
}

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->rules->print_mutex);
	if (check_dead_status(philo->rules))
	{
		pthread_mutex_unlock(&philo->rules->print_mutex);
		return ;
	}
	timestamp = get_time_ms() - philo->rules->start_time;
	printf("%lld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->rules->print_mutex);
}

void	ft_usleep(long long milliseconds, t_rules *rules)
{
	long long	start_time;

	start_time = get_time_ms();
	while ((get_time_ms() - start_time) < milliseconds)
	{
		if (check_dead_status(rules))
			break ;
		usleep(100);
	}
}
