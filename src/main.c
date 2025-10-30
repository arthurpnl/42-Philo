#include "philosopher.h"

int main(int argc, char **argv) 
{
    t_rules rules;

    if (parse_args(argc, argv, &rules) != 0)
        return (printf("Error: wrong arguments\nExample: ./philo 5 800 200 200 7"),  1);
    printf("num_philo: %d\n", rules.num_philo);
    printf("time_die: %d\n", rules.time_die);
    printf("time_eat: %d\n", rules.time_eat);
    printf("time_sleep: %d\n", rules.time_sleep);
    printf("nb_meal_required: %d\n", rules.nb_meal_required);
    printf("Valid arguments\n");
    
    return 0;
}