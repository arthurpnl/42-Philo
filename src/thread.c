#include "../includes/philosopher.h"

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (0);
}

void	simulation(t_data *data)
{
	create_threads(data);
	join_threads(data);
}