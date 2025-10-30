#include "philosopher.h" 

int is_all_digits(char **argv)
{
    int i;
    int j;

    i = 1;
    while(argv[i])
    {
        j = 0;
        while(argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

int convert_to_int(char *argv, int *tmp)
{
    int i;
    long res;
    
    i = 0;
    res = 0;
    while (argv[i])
    {
        res = res * 10 + (argv[i] - 48);
        if (res > INT_MAX)
            return (-1);
        i++;
    }
    *tmp = (int)res;
    return (0);
}

int parse_args(int argc, char **argv, t_rules *rules)
{
    int tmp;

    tmp = 0;
    if (argc !=  5 && argc != 6)
        return (1);
    if (is_all_digits(argv) != 0)
        return (1);
    if (convert_to_int(argv[1], &tmp) != 0 || tmp < 1)
        return (1);
    rules->num_philo = tmp;
    if (convert_to_int(argv[2], &tmp) != 0 || tmp < 1)
        return (1);
    rules->time_die = tmp;
    if (convert_to_int(argv[3], &tmp) != 0 || tmp < 1)
        return (1);
    rules->time_eat = tmp;
    if (convert_to_int(argv[4], &tmp) != 0 || tmp < 1)
        return (1);
    rules->time_sleep = tmp;
    rules->nb_meal_required = -1;
    if (argc == 6)
    {
        if (convert_to_int(argv[5], &tmp) != 0 || tmp < 1)
            return (1);
        rules->nb_meal_required = tmp;
    }
    return (0);
}
