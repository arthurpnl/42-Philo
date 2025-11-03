#include "philosopher.h"

int	init_data(t_data *data, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	data->dead_flag = 0;
	data->start_time = now_ms();
	data->philos = philos;
	data->forks = forks;
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
		return (1);
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (1);
		i++;
	}
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
	return (0);
}

