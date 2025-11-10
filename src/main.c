/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:31:17 by arpenel           #+#    #+#             */
/*   Updated: 2025/11/10 15:37:46 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	main(int argc, char **argv)
{
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	t_data			data;

	if (check_argc(argc) != 0)
		return (ft_putstr_fd("Error: wrong number of arguments\n", 2), 1);
	if (validate_args(argv, &data) != 0)
		return (ft_putstr_fd("Error: invalid arguments\n", 2), 1);
	if (init_data(&data, philos, forks) != 0)
		return (ft_putstr_fd("Error: initialization failed\n", 2), 1);
	simulation(&data);
	return (0);
}
