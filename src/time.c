#include "../includes/philosopher.h"

size_t	now_ms(void)
{
    struct timeval	time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}