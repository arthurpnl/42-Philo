#include "../includes/philosopher.h"

size_t	now_ms(void)
{
    struct timeval	v;

    gettimeofday(&v, NULL);
    return (v.tv_sec * 1000ULL + v.tv_usec / 1000ULL);
}


