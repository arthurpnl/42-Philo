#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	t_program		program;

    if (parse_args(argc, argv, &program.rules) != 0)
        return (ft_putstr_fd("Error: wrong arguments\nExample: ./philo 5 800 200 200 7", 2), 1);
    init_struct(&program);
    program.philos = philos;
    init_forks(forks, program.rules.num_philo);
    init_philos(&program, philos, forks, program.rules.num_philo);
	return (0);
}

