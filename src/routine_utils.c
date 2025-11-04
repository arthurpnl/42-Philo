#include "../includes/philosopher.h"

int    fork_pair_philo(t_philo *philo)
{
    usleep(1000);
    pthread_mutex_lock(philo->r_fork);
    print_state(philo, "has taken a fork");
    pthread_mutex_lock(philo->l_fork);
    print_state(philo, "has taken a fork");
    return (0);
}

int    fork_odd_philo(t_philo *philo)
{
    pthread_mutex_lock(philo->l_fork);
    print_state(philo, "has taken a fork");
    pthread_mutex_lock(philo->r_fork);
    print_state(philo, "has taken a fork");
    return (0);
}