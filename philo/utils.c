/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takhayas <hayatakucat@icloud.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:27:51 by takhayas          #+#    #+#             */
/*   Updated: 2026/06/03 22:27:06 by takhayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;

	if (check_dead_status(philo->rules))
		return ;
	pthread_mutex_lock(&philo->rules->print_mutex);
	timestamp = get_time_ms() - philo->rules->start_time;
	printf("%lld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->rules->print_mutex);
}

void	ft_usleep(long long milliseconds)
{
	long long	start_time;

	start_time = get_time_ms();
	while ((get_time_ms() - start_time) < milliseconds)
		usleep(500);
}
