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
# define RESET		"\033[0m"
# define CYAN		"\033[36m"
# define GREEN		"\033[32m"
# define MAGENTA	"\033[35m"
# define YELLOW		"\033[33m"
# define RED		"\033[31m"

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	size_t			last_meal;
	t_data			*data;
}					t_philo;

typedef struct s_data
{
	size_t			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_meal_required;
	int				dead_flag;
	t_philo			*philos;
}					t_data;

// parse.c
int					check_argc(int argc);
int					validate_args(char **argv, t_data *data);

// utils.c
void				ft_putstr_fd(char *s, int fd);
int					smart_sleep(size_t ms, t_philo *philo);
int					check_death(t_philo *philo);
int					ft_strcmp(const char *s1, const char *s2);

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
int					get_fork(t_philo *philo);
int					eat(t_philo *philo);
int					philo_sleep(t_philo *philo);
int					think(t_philo *philo);

// routine_utils.c 
int					fork_pair_philo(t_philo *philo);
int					fork_odd_philo(t_philo *philo);

#endif