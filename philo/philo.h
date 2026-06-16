/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takhayas <hayatakucat@icloud.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:35:49 by takhayas          #+#    #+#             */
/*   Updated: 2026/06/17 00:22:21 by takhayas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_rules
{
	int				n_philo;
	long long		t_to_die;
	long long		t_to_eat;
	long long		t_to_sleep;
	int				must_eat_count;
	pthread_mutex_t	*forks;
	long long		start_time_us;
	pthread_mutex_t	print_mutex;
	int				is_dead;
	pthread_mutex_t	death_mutex;
	pthread_t		monitor_thread;
}	t_rules;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_rules			*rules;
	long long		last_meal_time_us;
	pthread_mutex_t	meal_mutex;
	pthread_t		thread;
	int				meal_count;
}	t_philo;

//main.c
void		print_error(char *msg);

// parse_input.c
int			parse_input(int argc, char **argv, t_rules *rules);

// fork.c
int			fork_prepare(t_rules *rules);
void		destroy_all_fork(t_rules *rules);

// prepare.c
int			prepare_philos(t_philo **philos, t_rules *rules);
int			prepare_rules(t_rules *rules);
int			start_simulation(t_rules *rules, t_philo *philos);
// philo_routine_utils.c
long long	get_time_us(void);
void		think_pause(t_philo *philo);
void		one_philo_process(t_philo *philo, t_rules *rules);
void		meal_routine(t_philo *philo);
void		take_forks(t_philo *philo);

// philo_routine_utils.c
void		*philo_routine(void	*arg);

//utils.c
void		print_status(t_philo *philo, char *status);
void		ft_usleep(long long milliseconds, t_rules *rules);
int			is_digit(char c);
int			ft_strlen(char *str);
int			atoi_philo(char *input);

// monitor.c
int			check_dead_status(t_rules *rules);
void		*monitor_routine(void *arg);
#endif
