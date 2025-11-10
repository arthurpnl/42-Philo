#include "../includes/philosopher.h"

// int	print_state(t_philo *philo, char *state)
// {
// 	char	*color;

// 	if (ft_strcmp(state, "has taken a fork") == 0)
// 		color = CYAN;
// 	else if (ft_strcmp(state, "is eating") == 0)
// 		color = GREEN;
// 	else if (ft_strcmp(state, "is sleeping") == 0)
// 		color = MAGENTA;
// 	else if (ft_strcmp(state, "is thinking") == 0)
// 		color = YELLOW;
// 	else if (ft_strcmp(state, "died") == 0)
// 		color = RED;
// 	else
// 		color = RESET;
// 	pthread_mutex_lock(&philo->data->dead_lock);
// 	if (philo->data->dead_flag == 1 && ft_strcmp(state, "died") != 0)
// 	{
// 		pthread_mutex_unlock(&philo->data->dead_lock);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&philo->data->dead_lock);
// 	pthread_mutex_lock(&philo->data->print_lock);
// 	printf("%s%zu %d %s\n", color, now_ms() - philo->data->start_time,
// 		philo->id, state);
// 	pthread_mutex_unlock(&philo->data->print_lock);
// 	return (0);
// }

int	print_state(t_philo *philo, char *state)
{
    pthread_mutex_lock(&philo->data->dead_lock);
    if (philo->data->dead_flag == 1 && ft_strcmp(state, "died") != 0)
    {
        pthread_mutex_unlock(&philo->data->dead_lock);
        return (1);
    }
    pthread_mutex_unlock(&philo->data->dead_lock);
    pthread_mutex_lock(&philo->data->print_lock);
    printf("%zu %d %s\n", now_ms() - philo->data->start_time,
        philo->id, state);
    pthread_mutex_unlock(&philo->data->print_lock);
    return (0);
}

// int	eat(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->data->meal_lock);
// 	philo->meals_eaten++;
// 	pthread_mutex_unlock(&philo->data->meal_lock);
// 	if (print_state(philo, "is eating") == 1)
// 	{
// 		pthread_mutex_unlock(philo->l_fork);
// 		pthread_mutex_unlock(philo->r_fork);
// 		return (1);
// 	}
// 	if (smart_sleep(philo->data->time_eat, philo) == 1)
// 	{
// 		pthread_mutex_unlock(philo->l_fork);
// 		pthread_mutex_unlock(philo->r_fork);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(philo->l_fork);
// 	pthread_mutex_unlock(philo->r_fork);
// 	return (0);
// }

int	eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->meal_lock);
    philo->last_meal = now_ms();
    pthread_mutex_unlock(&philo->data->meal_lock);

    if (print_state(philo, "is eating") == 1)
    {
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);
        return (1);
    }
    if (smart_sleep(philo->data->time_eat, philo) == 1)
    {
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);
        return (1);
    }
    pthread_mutex_lock(&philo->data->meal_lock);
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->data->meal_lock);
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
    return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (print_state(philo, "is sleeping") == 1)
		return (1);
	if (smart_sleep(philo->data->time_sleep, philo) == 1)
		return (1);
	return (0);
}

int	think(t_philo *philo)
{
	if (print_state(philo, "is thinking") == 1)
		return (1);
	if (philo->data->num_philo % 2 == 1)
		smart_sleep(1, philo);
	return (0);
}


