#include "../includes/philosopher.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s && fd >= 0)
	{
		write(fd, &*s, 1);
		s++;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	smart_sleep(size_t ms, t_philo *philo)
{
	size_t	start_time;
	size_t	elapsed_time;

	start_time = now_ms();
	elapsed_time = 0;
	while (elapsed_time < ms)
	{
		usleep(1000);
		pthread_mutex_lock(&philo->data->dead_lock);
		if (philo->data->dead_flag == 1)
		{
			pthread_mutex_unlock(&philo->data->dead_lock);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->dead_lock);
		elapsed_time = now_ms() - start_time;
	}
	return (0);
}