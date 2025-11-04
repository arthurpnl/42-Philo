#include "../includes/philosopher.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philo == 1)
		return (handle_one_philo(philo), NULL);
	if (philo->id % 2 == 0)
		smart_sleep(1, philo);
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