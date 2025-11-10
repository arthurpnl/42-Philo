/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:31:10 by arpenel           #+#    #+#             */
/*   Updated: 2025/11/10 15:31:12 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
		return (1);
	return (0);
}

static int	init_forks_mutexes(pthread_mutex_t *forks, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

static void	init_philosophers(t_data *data, t_philo *philos,
		pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = data->start_time;
		philos[i].data = data;
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + 1) % data->num_philo];
		i++;
	}
}

int	init_data(t_data *data, t_philo *philos, pthread_mutex_t *forks)
{
	data->dead_flag = 0;
	data->start_time = now_ms();
	data->philos = philos;
	data->forks = forks;
	if (init_mutexes(data) != 0)
		return (1);
	if (init_forks_mutexes(forks, data->num_philo) != 0)
		return (1);
	init_philosophers(data, philos, forks);
	return (0);
}
