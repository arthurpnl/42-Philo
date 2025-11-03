#include "../includes/philosopher.h"

int	print_state(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%zu %d %s\n", now_ms() - philo->data->start_time, philo->id, state);
	pthread_mutex_unlock(&philo->data->print_lock);
	return (0);
}

void	handle_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_state(philo, "has taken a fork");
	usleep(philo->data->time_die * 1000);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philo == 1)
	{
		handle_one_philo(philo);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->data->dead_lock);
		if (philo->data->dead_flag == 1)
		{
			pthread_mutex_unlock(&philo->data->dead_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->dead_lock);
	}
	return (NULL);
}