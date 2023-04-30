/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:06:08 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/30 01:32:25 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_philos(t_data *philos, char **argv)
{
	if (!init_base (philos, argv))
		return (0);
	philos->forks = sem_open ("forks", O_CREAT, 0666, philos->num_of_philos);
	if (philos->forks == SEM_FAILED)
	{
		printf ("fail\n");
		return (0);
	}
	philos->sem_print = sem_open ("sem_print", O_CREAT, 0666, 1);
	if (philos->sem_print == SEM_FAILED)
	{
		printf ("fail\n");
		return (0);
	}
	sem_unlink ("forks");
	sem_unlink ("sem_print");
	return (1);
}

int	init_base(t_data *philos, char **argv)
{
	philos->num_of_philos = p_atoi (argv[1]);
	philos->philos = (pid_t *)p_calloc (philos->num_of_philos, sizeof (pid_t));
	if (philos->philos == NULL)
		return (0);
	philos->num_of_proc_ended = 0;
	philos->argv = argv;
	philos->flag = -1;
	philos->id = 0;
	return (1);
}

void	init_philo(t_data *philos, t_philo *philo, char **argv)
{
	philo->eaten = 0;
	philo->time_to_die = 0;
	philo->time_to_die_origin = (u_int64_t)p_atoi (argv[2]);
	philo->time_to_eat = (u_int64_t)p_atoi (argv[3]);
	philo->time_to_sleep = (u_int64_t)p_atoi (argv[4]);
	if (argv[5] != NULL)
		philo->num_of_time_to_eat = p_atoi (argv[5]);
	else
		philo->num_of_time_to_eat = -1;
	philo->usec_before = philos->time_to_start;
}

void	init_time(t_data *philos)
{
	philos->time_to_start = get_gtd ();
}
