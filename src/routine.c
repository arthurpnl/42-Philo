#include "../includes/philosopher.h"

int	print_state(t_philo *philo, char *state)
{
	char	*color;

	if (ft_strcmp(state, "has taken a fork") == 0)
		color = CYAN;
	else if (ft_strcmp(state, "is eating") == 0)
		color = GREEN;
	else if (ft_strcmp(state, "is sleeping") == 0)
		color = MAGENTA;
	else if (ft_strcmp(state, "is thinking") == 0)
		color = YELLOW;
	else if (ft_strcmp(state, "died") == 0)
		color = RED;
	else
		color = RESET;

	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead_flag == 1)
		return (pthread_mutex_unlock(&philo->data->dead_lock), 1);
	pthread_mutex_unlock(&philo->data->dead_lock);
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%s%zu %d %s\033[0m\n", color, now_ms() - philo->data->start_time, philo->id, state);
	pthread_mutex_unlock(&philo->data->print_lock);
	return (0);
}

void	handle_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_state(philo, "has taken a fork");
	smart_sleep(philo->data->time_die, philo);
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
	else
		return (fork_odd_philo(philo));
}

int	eat(t_philo *philo)
{
	(void)philo;
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	(void)philo;
	return (0);
}

int	think(t_philo *philo)
{
	(void)philo;
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philo == 1)
		return (handle_one_philo(philo), NULL);
	while (1)
	{
		if (check_death(philo) == 1)
			return (NULL);
		if (get_fork(philo) == 1)
			return (NULL);
		if (eat(philo) == 1)
			return (NULL);
		if (philo_sleep(philo) == 1)
			return (NULL);
		if (think(philo) == 1)
			return (NULL);
	}
	return (NULL);
}