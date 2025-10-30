#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stddef.h>
# include <stdio.h> 
# include <stdlib.h>
# include <string.h>
# include <unistd.h> 
# include <limits.h>

typedef struct s_rules
{
    int num_philo;
    int time_die;
    int time_eat;
    int time_sleep;
    int nb_meal_required;
}   t_rules;

// parse.c
int parse_args(int argc, char **argv, t_rules *rules);

#endif