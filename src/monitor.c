/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:30:54 by arpenel           #+#    #+#             */
/*   Updated: 2025/11/10 15:47:15 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	all_philos_full(t_data *data)
{
	int	full;
	int	i;

	if (data->nb_meal_required <= 0)
		return (0);
	full = 1;
	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_lock(&data->meal_lock);
		if (data->philos[i].meals_eaten < data->nb_meal_required)
			full = 0;
		pthread_mutex_unlock(&data->meal_lock);
		if (full == 0)
			break ;
		i++;
	}
	if (full == 1)
	{
		pthread_mutex_lock(&data->dead_lock);
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->dead_lock);
	}
	return (full);
}

static int	check_philo_death(t_data *data, int i)
{
	size_t	elapsed;

	pthread_mutex_lock(&data->meal_lock);
	elapsed = now_ms() - data->philos[i].last_meal;
	pthread_mutex_unlock(&data->meal_lock);
	if (elapsed >= (size_t)data->time_die)
	{
		pthread_mutex_lock(&data->dead_lock);
		if (data->dead_flag == 0)
			data->dead_flag = 1;
		pthread_mutex_unlock(&data->dead_lock);
		print_state(&data->philos[i], "died");
		return (1);
	}
	return (0);
}

int	monitoring(t_data *data)
{
	int	i;

	while (!data_is_dead(data))
	{
		i = 0;
		while (i < data->num_philo)
			if (check_philo_death(data, i++) == 1)
				return (1);
		if (all_philos_full(data))
			return (1);
		usleep(1000);
	}
	return (0);
}
