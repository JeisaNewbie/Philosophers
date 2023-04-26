/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkiler <ahkiler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:01:40 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/25 15:25:07 by ahkiler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_data *philos, char **argv)
{
	init_base (philos, argv);
	if (!malloc_all (philos))
	{
		printf ("malloc_failure!!!\n");
		return (0);
	}
	return (1);
}

void	init_base(t_data *philos, char **argv)
{
	philos->num_of_philos = p_atoi (argv[1]);
	philos->flag = -1;
	philos->id = 0;
	philos->end = 0;
	philos->argv = argv;
	if (argv[5] != NULL)
		philos->num_of_philos_eaten = philos->num_of_philos;
	else
		philos->num_of_philos_eaten = -1;
	if (philos->num_of_philos % 2)
		philos->target = -1;
	else
		philos->target = 1;
}

void	init_philo(t_data *philos, t_philo *philo, int *id, int *left_id)
{
	if (id != 0 && *id == 0)
		*left_id = philos->num_of_philos - 1;
	else if (id != 0 && *id != 0)
		*left_id = *id - 1;
	philo->time_to_die = 0;
	philo->time_to_die_origin = (u_int64_t)p_atoi (philos->argv[2]);
	philo->time_to_eat = (u_int64_t)p_atoi (philos->argv[3]);
	philo->time_to_sleep = (u_int64_t)p_atoi (philos->argv[4]);
	philo->usec_before = philos->time_to_start;
	philo->eaten = 0;
	if (philos->argv[5] != NULL)
		philo->num_of_time_to_eat = p_atoi (philos->argv[5]);
	else
		philo->num_of_time_to_eat = -1;
}

void	init_time(t_data *philos, t_philo *philo)
{
	philos->time_to_start = get_gtd (philo);
	philos->end = 0;
}
