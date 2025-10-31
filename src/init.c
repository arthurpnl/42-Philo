#include "../includes/philosopher.h"

void	init_struct(t_program *program)
{
    program->dead_flag = 0;
    pthread_mutex_init(&program->print_lock, NULL);
    pthread_mutex_init(&program->dead_lock, NULL);
    pthread_mutex_init(&program->meal_lock, NULL);
}



void	init_forks(pthread_mutex_t *forks, int n)
{
    int	i;

    i = 0;
    while (i < n)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
}

void	init_philos(t_program *program, t_philo *philos, pthread_mutex_t *forks, int n)
{
    int		i;
    size_t	start;

    start = now_ms();
    i = 0;
    while (i < n)
    {
        philos[i].id = i + 1;
        philos[i].eating = 0;
        philos[i].meals_eaten = 0;
        philos[i].start_time = start;
        philos[i].last_meal = start;

        philos[i].rules = &program->rules;
        philos[i].dead = &program->dead_flag;

        philos[i].print_lock = &program->print_lock;
        philos[i].dead_lock = &program->dead_lock;
        philos[i].meal_lock = &program->meal_lock;

        philos[i].l_fork = &forks[i];
        philos[i].r_fork = &forks[(i + 1) % n];
        i++;
    }
}
