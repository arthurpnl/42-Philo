#include "../includes/philosopher.h"

int	main(int argc, char **argv)
{
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	t_data			data;

	if (check_argc(argc) != 0)
		return (ft_putstr_fd("Error: wrong number of arguments\n", 2), 1);
	if (validate_args(argv, &data) != 0)
		return (ft_putstr_fd("Error: invalid arguments\nExample: ./philo 5 800 200 200 7", 2), 1);
	if (init_data(&data, philos, forks) != 0)
		return (ft_putstr_fd("Error: initialization failed\n", 2), 1);
	simulation(&data);
	return (0);
}

