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

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	size_t			last_meal;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_data			*data;
}					t_philo;

typedef struct s_data
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_meal_required;
	int				dead_flag;
	size_t			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	t_philo			*philos;
}					t_data;

// parse.c
int					check_argc(int argc);
int					validate_args(char **argv, t_data *data);

// utils.c
void				ft_putstr_fd(char *s, int fd);

// init.c
size_t				now_ms(void);
int					init_data(t_data *data, t_philo *philos, pthread_mutex_t *forks);

// thread.c
int					create_threads(t_data *data);
int					join_threads(t_data *data);
void				simulation(t_data *data);

// routine.c
void				*routine(void *arg);
int					print_state(t_philo *philo, char *state);
void				handle_one_philo(t_philo *philo);

#endif