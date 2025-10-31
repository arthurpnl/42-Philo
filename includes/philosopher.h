#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <limits.h>
# include <pthread.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_rules
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_meal_required;
}					t_rules;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			start_time;
	t_rules			*rules;
	int				*dead;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	t_philo			*philos;
	t_rules			rules;
}					t_program;

// parse.c
int					parse_args(int argc, char **argv, t_rules *rules);

// utils.c
void				ft_putstr_fd(char *s, int fd);

// init.c
size_t				now_ms(void);
void				init_struct(t_program *program);
void				init_forks(pthread_mutex_t *forks, int n);
void				init_philos(t_program *program, t_philo *philos, pthread_mutex_t *forks, int n);

#endif