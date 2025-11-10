#include "../includes/philosopher.h"

void	handle_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_state(philo, "has taken a fork");
	smart_sleep(philo->data->time_die, philo);
	print_state(philo, "died");
	pthread_mutex_unlock(philo->l_fork);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (0);
}

int	fork_pair_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (print_state(philo, "has taken a fork") == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	pthread_mutex_lock(philo->l_fork);
	if (print_state(philo, "has taken a fork") == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = now_ms();
	pthread_mutex_unlock(&philo->data->meal_lock);
	return (0);
}

int	fork_odd_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (print_state(philo, "has taken a fork") == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	pthread_mutex_lock(philo->r_fork);
	if (print_state(philo, "has taken a fork") == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = now_ms();
	pthread_mutex_unlock(&philo->data->meal_lock);
	return (0);
}

int	get_fork(t_philo *philo)
{
	if (philo->data->num_philo == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_state(philo, "has taken a fork");
		while (check_death(philo) == 0)
			smart_sleep(1000, philo);
		pthread_mutex_unlock(philo->l_fork);
		return (0);
	}
	if (philo->id % 2 == 0)
		return (fork_pair_philo(philo));
	return (fork_odd_philo(philo));
}