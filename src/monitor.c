#include "../includes/philosopher.h"

static int	all_philos_full(t_data *data)
{
	int		full;
	int		i;

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

int	monitoring(t_data *data)
{
	int			 i;
	size_t		elapsed;

	while (1)
	{
		pthread_mutex_lock(&data->dead_lock);
		if (data->dead_flag == 1)
		{
			pthread_mutex_unlock(&data->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&data->dead_lock);
		i = 0;
		fprintf(stderr, "DEBUG: start_time=%zu time_die=%d num_philo=%d\n",
    		data->start_time, data->time_die, data->num_philo);
		while (i < data->num_philo)
		{
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
			i++;
		}
		if (all_philos_full(data))
			return (1);
		usleep(1000);
	}
	return (0);
}
