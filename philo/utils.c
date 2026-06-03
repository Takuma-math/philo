/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takhayas <hayatakucat@icloud.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:27:51 by takhayas          #+#    #+#             */
/*   Updated: 2026/06/03 17:48:13 by takhayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->rules->print_mutex);
	if (!philo->rules->is_dead)
	{
		timestamp = get_time_ms() - philo->rules->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&philo->rules->print_mutex);
}

void	ft_usleep(long long milliseconds)
{
	long long	start_time;

	start_time = get_time_ms();
	while ((get_time_ms() - start_time) < milliseconds)
		usleep(500);
}
